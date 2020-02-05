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
#include <Scenes/Scene.hpp>

#include <Object/ObjectManager.hpp>
#include <Graphics/GL.hpp>
// Include Components
#include <Component/Sprite/Sprite.hpp>
#include <Component/Sprite/StringSprite.hpp>
#include <Component/Sprite/TextComponent.hpp>

// Include Special objects
#include <Object/DEBUGObject/LevelChangeButton.hpp>
#include <Object/DEBUGObject/WallSpawner.hpp>

void Scene::GameRestartScene() noexcept
{
    GameRestart();
    cameraManager.InitializeCurrentCameraSetting();
}

void Scene::LoadScene() noexcept
{
	InstanceDEBUGObjects();
	Load();
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
			if (const auto & sprite = obj.get()->GetComponentByTemplate<Sprite>())
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
					sprite->UpdateInstancingValues(nullptr);
					Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());
				}
			}
			else if (const auto & text = obj.get()->GetComponentByTemplate<TextComponent>())
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