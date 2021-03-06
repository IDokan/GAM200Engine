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
#include <Component/StateMachine.hpp>

// Include Special objects
#include <Object/DEBUGObject/LevelChangeButton.hpp>
#include <Object/DEBUGObject/WallSpawner.hpp>
#include <Object/Particles/ParticleEmitter.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>
#include <Systems/ObstaclesDrawingHelper.hpp>
#include <Object/HUD/StringLengthUI.hpp>
#include <Object/HUD/HostageAlertsUI.hpp>
#include <Object/HUD/StatusUI.hpp>

#include <States/PlayerStates/UpdateAnimation.hpp>
// Include Scene States
#include <States/SceneStates/PlayerIsDead.hpp>
#include <States/SceneStates/SceneComplete.hpp>
#include <States/SceneStates/GamsIsRunning.hpp>
#include <States/SceneStates/PauseAndMenu.hpp>
#include <States/PlayerStates/InRefrigerator.hpp>

#include <Systems/Input.hpp>
#include <Systems/FileIO.hpp>


#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Graphics/GL.hpp>
#include <Scenes/SceneManager.hpp>
#include <Object/Points/CheckPoint.hpp>


void Scene::GameRestartScene() noexcept
{
	input.TriggeredReset();

	vector2 checkPosition = lastCheckPoint->GetTranslation();

    vector2 player1SpawnPosition = checkPosition - vector2{ UpdateAnimation::initial_scaling / 2.f, 0.f };

    player1->SetScale(UpdateAnimation::initial_scaling);
    player1->GetComponentByTemplate<Physics>()->SetPosition(player1SpawnPosition);
    player1->GetComponentByTemplate<Physics>()->SetOldPosition(player1SpawnPosition);
    player1->SetTranslation(player1SpawnPosition);
    player1->GetComponentByTemplate<Physics>()->SetVelocity(vector2{ 0.f });

    vector2 player2SpawnPosition = checkPosition + vector2{ UpdateAnimation::initial_scaling / 2.f, 0.f };

    player2->SetScale(UpdateAnimation::initial_scaling);
    player2->GetComponentByTemplate<Physics>()->SetPosition(player2SpawnPosition);
    player2->GetComponentByTemplate<Physics>()->SetOldPosition(player2SpawnPosition);
    player2->SetTranslation(player2SpawnPosition);
    player2->GetComponentByTemplate<Physics>()->SetVelocity(vector2{ 0.f });

    string->InitString();

    player1->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(InRefrigerator::Get());
    player2->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(InRefrigerator::Get());

    GameRestart();
    cameraManager.InitializeCurrentCameraSetting();
}

//Init LoadingSceneImage
void Scene::InitLoadingScene()
{
	cameraManager.Init();

	loadingCheeseBG = new Object();
	loadingCheeseBG->SetObjectName("Loading Cheese Background");
	loadingCheeseBG->SetScale(vector2{ 150.f });
	loadingCheeseBG->SetTranslation(vector2{ 0.f, 100.f });
	Sprite* cheeseBgSprite = new Sprite(loadingCheeseBG);
	cheeseBgSprite->SetImage("../assets/textures/UI/StatusUIBackground.png");
	loadingCheeseBG->AddComponent(cheeseBgSprite);
	loadingCheeseBG->SetDepth(-0.5f);

	loadingCheese = new Object();
	loadingCheese->SetObjectName("loadingCheese");
	loadingCheese->SetTranslation(vector2{ 0.f, 100.f });
	loadingCheese->SetScale(vector2{ 100.f });
	Animation* cheeseAni = new Animation(loadingCheese);
	loadingCheese->AddComponent(cheeseAni);
	cheeseAni->SetFrame(6);
	cheeseAni->SetSpeed(1.f);
	loadingCheese->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/Hostage.png");
	loadingCheese->SetDepth(-0.9f);

	loadingText = new Object();
	loadingText->SetObjectName("Loading Text");
	loadingText->SetTranslation(vector2{ -70.f ,-20.f });
	loadingText->AddComponent(new TextComponent(loadingText));
	loadingText->GetComponentByTemplate<TextComponent>()->SetString(L"Loading");
	loadingText->SetDepth(-0.9f);

	loadingAnimation = new Object();
	loadingAnimation->SetObjectName("Loading Animation");
	loadingAnimation->SetTranslation(vector2{ 0.f });
	loadingAnimation->SetScale(vector2{ 2.f, 4.f });
	Sprite* ani = new Sprite(loadingAnimation);
	loadingAnimation->AddComponent(ani);
	loadingAnimation->SetDepth(0.f);
	ani->SetImage("../assets/textures/UI/TransitionCheese.png");
}

bool Scene::IsMenu()
{
    return isMenu;
}


void Scene::LoadScene() noexcept
{

    ///////////////////////Init Loading Scene image & text data...

    //std::thread performanceTest(&InitLoadingScene);
    input.TriggeredReset();

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

			loadingCheeseBG->GetComponentByTemplate<Sprite>()->DeleteVertices();
			loadingCheese->GetComponentByTemplate<Sprite>()->DeleteVertices();
			loadingAnimation->GetComponentByTemplate<Sprite>()->DeleteVertices();

			loadingCheeseBG->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/UI/StatusUIBackground.png");
			loadingCheese->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/Hostage.png");
			loadingAnimation->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/UI/TransitionCheese.png");

			loadingCheeseBG->GetComponentByTemplate<Sprite>()->GenerateVertices();
			loadingCheese->GetComponentByTemplate<Sprite>()->GenerateVertices();
			loadingAnimation->GetComponentByTemplate<Sprite>()->GenerateVertices();

			while (isLoadingDone == false)
			{

            // Update loading data
            ++loadingCount;

				if (loadingCount % 45 == 0)
				{
					loadingText->GetComponentByTemplate<TextComponent>()->SetString(L"Loading");
				}
				if (loadingCount % 15 == 0)
				{
					std::wstring string = loadingText->GetComponentByTemplate<TextComponent>()->GetString();
					loadingText->GetComponentByTemplate<TextComponent>()->SetString(string + L"...");
				}

				loadingCheese->GetComponentByTemplate<Animation>()->Update(0.1f);

				Graphics::GL::begin_drawing();

				// Loading Animation
				const auto matrix3 = loadingAnimation->GetTransform().GetModelToWorld();
				Sprite* ani = loadingAnimation->GetComponentByTemplate<Sprite>();
				ani->UpdateUniforms(matrix3, loadingAnimation->GetTransform().CalculateWorldDepth());
				Graphics::GL::draw(*ani->GetVertices(), *ani->GetMaterial());

				// LoadingScene
				const auto matrix4 = cameraManager.GetWorldToNDCTransform() * loadingCheeseBG->GetTransform().GetModelToWorld();
				Sprite* BGsprite = loadingCheeseBG->GetComponentByTemplate<Sprite>();
				BGsprite->UpdateUniforms(matrix4,
					loadingCheeseBG->GetTransform().CalculateWorldDepth());
				Graphics::GL::draw(*BGsprite->GetVertices(), *BGsprite->GetMaterial());

				// LoadingScene
				const auto matrix = cameraManager.GetWorldToNDCTransform() * loadingCheese->GetTransform().GetModelToWorld();
				Sprite* sprite = loadingCheese->GetComponentByTemplate<Sprite>();
				sprite->UpdateUniforms(matrix,
					loadingCheese->GetTransform().CalculateWorldDepth());
				Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());

            // Loading Text
            const auto matrix2 = cameraManager.GetWorldToNDCTransform() * loadingText->GetTransform().GetModelToWorld();
            loadingText->GetComponentByTemplate<TextComponent>()->Draw(matrix2,
                loadingText->GetTransform().CalculateWorldDepth());

            Graphics::GL::end_drawing();

            SwapBuffers(hdc);
        }

			loadingCheeseBG->GetComponentByTemplate<Sprite>()->DeleteVertices();
			loadingCheese->GetComponentByTemplate<Sprite>()->DeleteVertices();
			loadingAnimation->GetComponentByTemplate<Sprite>()->DeleteVertices();

			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(thread_context);
		});

    glfwMakeContextCurrent(main_context);

    ///////////////////////Init(huge work) Working here..
    SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Load_Sound();

    InitRequiredObjects();
    InitDEBUGObjects();
    Load();
    InRefrigerator::Get()->ptrString = string;
    if (string != nullptr)
    {
        string->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 0.f, 0.f });
    }
    if (lastCheckPoint != nullptr)
    {
        lastCheckPoint->GetComponentByTemplate<Animation>()->SetState(1);
        lastCheckPoint->SetEmitterOn(true);
    }

    isLoadingDone = true;

    if (loading_Thread.joinable()) {
        loading_Thread.join();
    }

}

void Scene::UnloadScene() noexcept
{
    is_next = false;

    if (IsMenu() == false)
    {
        fileIO* fileio = new fileIO;
        fileio->SaveLevel();

        delete fileio;
    }

    CleanRequiredObjects();
    Unload();

    ObjectManager* objManager = ObjectManager::GetObjectManager();
    for (const auto& layers : objManager->GetLayerContainer())
    {
        for (const auto& obj : layers->GetObjContainer())
        {
            obj->SetDead(true);
        }
    }
}

void Scene::Draw() noexcept
{
    // Clear obstacle matrices buffer for instancing.
    obstacleTextureCoordinateScaler.clear();
    obstacleColors.clear();
    obstacleMatrices.clear();


    // Check is there possible to cause bug?
    bool localFlag = false;
    for (auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
    {
        localFlag = localFlag || element->GetSortingDirtyFlag();
    }
    // Do handle with it
    if (localFlag)
    {

        for (auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
        {
            if (element->GetSortingDirtyFlag())
            {
                // Before draw it, sort every object in each layer.
                element->SortingDepth();
            }
        }
        for (auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
        {
            if (element->GetSortingDirtyFlag())
            {
                // Delete all vertices
                element->DeleteAllVertices();
                // Restore all vertices
                element->GenerateAllVertices();
                element->SetSortingDirtyFlag(false);
            }
        }
    }

    if (input.IsKeyTriggered(GLFW_KEY_9))    {
        for (auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
        {
            if (element->GetSortingDirtyFlag())
            {
                // Delete all vertices
                element->DeleteAllVertices();
                // Restore all vertices
                element->GenerateAllVertices();
                element->SetSortingDirtyFlag(false);
            }
        }
    }


    // Start drawing
    Graphics::GL::begin_drawing();

    for (auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
    {

        obstacleTextureCoordinateScaler.clear();
        obstacleColors.clear();
        obstacleMatrices.clear();

        if (element->GetName() == LayerNames::HUD)
        {
            for (const auto& obj : element->GetObjContainer())
            {
                DrawObject(obj.get());
            }

        }
        else
        {
            for (const auto& obj : element->GetObjContainer())
            {
                DrawObject(obj.get(), cameraManager.GetWorldToNDCTransform());
            }
        }

        if (obstacleMatrices.empty() == false)
        {
            // Obstacle Instancing draw
            ObstaclesDrawingHelper::Get()->Draw(&obstacleTextureCoordinateScaler, &obstacleColors, &obstacleMatrices);
        }
    }

    Graphics::GL::end_drawing();
}

Graphics::CameraManager& Scene::GetCameraManager() noexcept
{
    return cameraManager;
}

SoundManager& Scene::GetSoundManager() noexcept
{
    return soundManager;
}

SceneStateManager* Scene::GetSceneStateManager() noexcept
{
    return sceneStateManager;
}

void Scene::LevelChangeTo(std::string name)
{
    SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().StopCurrentBGM();
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




// Start drawing iteration whole object container.
// There are a bunch of case that need different task
// 0. Obstacle objects
// 1. Particle Object
// 2. A sort of Sprite object
// 2-a. Sprite which instancing mode is on. (incomplete)
// 3. A sort of Text object
void Scene::DrawObject(Object* obj, matrix3 offset) noexcept
{
    if (obj->GetObjectType() == Object::ObjectType::OBSTACLE)
    {
        const auto matrix = offset * obj->GetTransform().GetModelToWorld();
        static constexpr float TextureCoordinateScalerAdjustValue = 75.f;
        obstacleTextureCoordinateScaler.push_back(obj->GetScale() / TextureCoordinateScalerAdjustValue);
        obstacleColors.push_back(Graphics::to_color4ub(obj->GetComponentByTemplate<Sprite>()->GetColor()));
        obstacleMatrices.push_back(matrix);
        return;
    }

    // 1. Particle Object
    if (ParticleEmitter* particleEmitter = dynamic_cast<ParticleEmitter*>(obj))
    {
        const std::vector<Particle::ParticleObject>& particleObjects = particleEmitter->GetParticleObjectsContainer();
        Particle* particle = particleEmitter->GetComponentByTemplate<Particle>();

        std::vector<matrix3> matrices;
        std::vector<Graphics::Color4ub> colors;
        std::vector<vector2> textureCoordinateScalar;
        size_t sizeOfParticle = particleObjects.size();
        matrices.reserve(sizeOfParticle);
        for (size_t i = 0; i < sizeOfParticle; ++i)
        {
            matrices.emplace_back(offset * particleObjects[i].transform.GetModelToWorld());
            colors.emplace_back(Graphics::to_color4ub(particleObjects[i].color));
            textureCoordinateScalar.emplace_back(particleObjects[i].textureCoordinateScalar);
        }
        particle->UpdateInstancingValues(&textureCoordinateScalar, &colors, &matrices, particleEmitter->GetDepth());
        Graphics::GL::drawInstanced(*particle->GetVertices(), *particle->GetMaterial());
    }

    else if (const auto& sprite = obj->GetComponentByTemplate<Sprite>())
    {
        if (sprite->isInstancingMode() == false)
        {
            // 2. (Incomplete, need to be improved)
            // Update model to NDC matrix as Uniform 
            const auto matrix = offset * obj->GetTransform().GetModelToWorld();
            sprite->UpdateUniforms(matrix,
                obj->GetTransform().CalculateWorldDepth());
            Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());
        }
        else
        {
            // 2-a.
            // Update model to NDC matrix as instanced array ( Change Mesh )
            const auto matrix = offset * obj->GetTransform().GetModelToWorld();
            std::vector<matrix3> matrices;
            matrices.push_back(matrix);
            sprite->UpdateInstancingValues(&matrices, obj->GetTransform().CalculateWorldDepth());
            Graphics::GL::drawInstanced(*sprite->GetVertices(), *sprite->GetMaterial());
        }
    }
    else if (const auto& text = obj->GetComponentByTemplate<TextComponent>())
    {
        // 4.
        // Update model to NDC matrix as Uniform value and Call different draw function.
        const auto matrix = offset * obj->GetTransform().GetModelToWorld();
        text->Draw(matrix,
            obj->GetTransform().CalculateWorldDepth());
    }
}

void Scene::InitDEBUGObjects()
{
#ifdef _DEBUG
    ObjectManager* objManager = ObjectManager::GetObjectManager();


    LevelChangeButton* tmp = new LevelChangeButton();
    objManager->FindLayer(HUD)->AddObject(tmp);
    WallSpawner* wallSpawner = new WallSpawner();
    objManager->FindLayer(HUD)->AddObject(wallSpawner);

#endif
}

void Scene::InitRequiredObjects()
{

    Layer* hud = ObjectManager::GetObjectManager()->FindLayer(HUD);
    sceneStateManager = new SceneStateManager();
    hud->AddObject(sceneStateManager);

    PlayerIsDead::Get()->PrepareAssets();
    SceneComplete::Get()->PrepareAssets();
    PauseAndMenu::Get()->PrepareAssets();

    if (isMenu == true)
    {
        return;
    }

    StringLengthUI* slUI = new StringLengthUI();
    hud->AddObject(slUI);

    HostageAlertsUI* haUI = new HostageAlertsUI();
    hud->AddObject(haUI);

    StatusUI* sUI = new StatusUI();
    hud->AddObject(sUI);
}

void Scene::CleanRequiredObjects()
{
    GameIsRunning::Get()->CleanAssets();
    SceneComplete::Get()->CleanAssets();
    PlayerIsDead::Get()->CleanAssets();
    PauseAndMenu::Get()->CleanAssets();
}
