/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Scene.cpp
Author
		rtd99062@gmail.com
Creation Date: 12.10.2019

	Source file for the abstract class for all of Scene
******************************************************************************/
#include <thread>
#include <Scenes/Scene.hpp>

#include <Object/ObjectManager.hpp>

// Include Components
#include <Component/Sprite/Sprite.hpp>
#include <Component/Sprite/StringSprite.hpp>
#include <Component/Sprite/TextComponent.hpp>

// Include Special objects
#include <Object/DEBUGObject/LevelChangeButton.hpp>
#include <Object/DEBUGObject/WallSpawner.hpp>


#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Graphics/GL.hpp>
#include <Scenes/SceneManager.hpp>

void Scene::GameRestartScene() noexcept
{
	GameRestart();
	cameraManager.InitializeCurrentCameraSetting();
}

//Init LoadingSceneImage
void Scene::InitLoadingScene()
{
	cameraManager.Init();
	loadingScene = new Object();
	loadingScene->SetObjectName("loadingScene");
	loadingScene->SetTranslation(vector2{ 1.f });
	loadingScene->SetScale(vector2{ 2000.f });
	loadingScene->AddComponent(new Sprite(loadingScene));
	loadingScene->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(0));
	loadingScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");
	loadingScene->SetDepth(-0.f);

	loadingText = new Object();
	loadingText->SetObjectName("Loading Text");
	loadingText->SetTranslation(vector2{ -100.f ,-20.f});
	loadingText->AddComponent(new TextComponent(loadingText));
	loadingText->GetComponentByTemplate<TextComponent>()->SetString(L"Loading");
	loadingText->SetDepth(-0.9f);
}


void Scene::LoadScene() noexcept
{
	InstanceDEBUGObjects();

	///////////////////////Init Loading Scene image & text data...

	//Test��...
	//std::thread performanceTest(&InitLoadingScene);
	InitLoadingScene();

	//////////////////////Worker Thread here...
	GLFWwindow* main_context = glfwGetCurrentContext();
	HDC hdc = GetDC(glfwGetWin32Window(main_context));
	HGLRC thread_context = wglCreateContext(hdc);

	BOOL error = wglShareLists(glfwGetWGLContext(main_context), thread_context);

	if (error == FALSE)
	{
		printf("Something is wrong!");

	}
	glfwMakeContextCurrent(NULL);


	std::thread loading_Thread([&]()
		{
			wglMakeCurrent(hdc, thread_context);

			unsigned int loadingCount = 0;

			while(isLoadingDone == false)
			{
				// Update loading data
				++loadingCount;

				if (loadingCount % 1500 == 0)
				{
					loadingText->GetComponentByTemplate<TextComponent>()->SetString(L"Loading");
				}
				if (loadingCount % 500 == 0)
				{
					std::wstring string = loadingText->GetComponentByTemplate<TextComponent>()->GetString();
					loadingText->GetComponentByTemplate<TextComponent>()->SetString(string + L"...");
				}

				Graphics::GL::begin_drawing();

				// LoadingScene
				const auto matrix = cameraManager.GetWorldToNDCTransform() * loadingScene->GetTransform().GetModelToWorld();
				Sprite* sprite = loadingScene->GetComponentByTemplate<Sprite>();
				sprite->UpdateUniforms(matrix,
					loadingScene->GetTransform().CalculateWorldDepth());
				Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());

				// Loading Text
				const auto matrix2 = cameraManager.GetWorldToNDCTransform() * loadingText->GetTransform().GetModelToWorld();
				loadingText->GetComponentByTemplate<TextComponent>()->Draw(matrix2,
					loadingText->GetTransform().CalculateWorldDepth());


				Graphics::GL::end_drawing();

				SwapBuffers(hdc);
			}

			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(thread_context);
		});

	glfwMakeContextCurrent(main_context);

	///////////////////////Init(huge work) Working here..
	Load(); 

	isLoadingDone = true;

	if (loading_Thread.joinable()) {
		loading_Thread.join();
	}
}

void Scene::UnloadScene() noexcept
{
	is_next = false;

	ObjectManager* objManager = ObjectManager::GetObjectManager();
	for (const auto& layers : objManager->GetLayerContainer())
	{
		for (const auto& obj : layers->GetObjContainer())
		{
			obj->SetDead(true);
		}
	}

	Unload();
}

void Scene::Draw() const noexcept
{
	Graphics::GL::begin_drawing();

	for (const auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
	{
		// Before draw it, sort every object in each layer.
		// TODO: Improve it. Do this when only need
		element->SortingDepth();

		// Start drawing iteration whole object container.
		// There are a bunch of case that need different task
		// 1. A sort of Sprite object
		// 1-a. Sprite which instancing mode is on.
		// 2. A sort of Text object
		for (const auto& obj : element->GetObjContainer())
		{
			if (const auto& sprite = obj.get()->GetComponentByTemplate<Sprite>())
			{
				if (sprite->isInstancingMode() == false)
				{
					// 1.
					// Update model to NDC matrix as Uniform 
					const auto matrix = cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld();
					sprite->UpdateUniforms(matrix,
						obj.get()->GetTransform().CalculateWorldDepth());
					Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());
				}
				else
				{
					// 1-a.
					// Update model to NDC matrix as instanced array ( Change Mesh )
					const auto matrix = cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld();
					std::vector<matrix3> matrices;
					matrices.push_back(matrix);
					sprite->UpdateInstancingValues(&matrices, obj->GetTransform().CalculateWorldDepth());
					Graphics::GL::drawInstanced(*sprite->GetVertices(), *sprite->GetMaterial());
				}
			}
			else if (const auto& text = obj.get()->GetComponentByTemplate<TextComponent>())
			{
				// 2.
				// Update model to NDC matrix as Uniform value and Call different draw function.
				const auto matrix = cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld();
				text->Draw(matrix,
					obj.get()->GetTransform().CalculateWorldDepth());
			}
		}
	}
	Graphics::GL::end_drawing();
}

const Graphics::CameraManager& Scene::GetCameraManager() const noexcept
{
	// TODO: insert return Scenement here
	return cameraManager;
}

void Scene::LevelChangeTo(std::string name)
{
	is_next = true;
	next_level = name;
}

std::string Scene::GetChangedLevelName()
{
	return next_level;
}

bool Scene::isNextLevel()
{
	return is_next;
}

GameScenes Scene::GetSceneInfo()
{
	return current_scene_info;

}




void Scene::InstanceDEBUGObjects()
{
#ifdef _DEBUG
	ObjectManager* objManager = ObjectManager::GetObjectManager();


	LevelChangeButton* tmp = new LevelChangeButton();
	objManager->FindLayer(HUD)->AddObject(tmp);
	WallSpawner* wallSpawner = new WallSpawner();
	objManager->FindLayer(HUD)->AddObject(wallSpawner);

#endif
}