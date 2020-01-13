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
		element->SortingDepth();
		for (const auto& obj : element->GetObjContainer())
		{
			if (const auto & sprite = obj.get()->GetComponentByTemplate<Sprite>())
			{
				const auto matrix = cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld();
				sprite->UpdateUniforms(matrix,
					obj.get()->GetTransform().CalculateWorldDepth());
				Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());
			}
			if (const auto & text = obj.get()->GetComponentByTemplate<TextComponent>())
			{
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