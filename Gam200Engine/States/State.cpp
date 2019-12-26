/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   State.cpp
Author
		rtd99062@gmail.com
Creation Date: 12.10.2019

	Source file for the abstract class for all of state
******************************************************************************/
#include <States/State.hpp>

#include <Object/ObjectManager.hpp>
#include <Graphics/GL.hpp>
// Include Components
#include <Component/Sprite.hpp>
#include <Component/StringSprite.hpp>
#include <Component/TextComponent.hpp>

// Include Special objects
#include <Object/DEBUGObject/LevelChangeButton.hpp>
#include <Object/DEBUGObject/WallSpawner.hpp>

void State::GameRestartState() noexcept
{
    GameRestart();
    cameraManager.InitializeCurrentCameraSetting();
}

void State::LoadState() noexcept
{
	InstanceDEBUGObjects();
	Load();
}

void State::UnloadState() noexcept
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

void State::Draw() const noexcept
{
	Graphics::GL::begin_drawing();

	for (const auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
	{
		element->SortingDepth();
		for (const auto& obj : element->GetObjContainer())
		{
			if (const auto & stringSprite = obj.get()->GetComponentByTemplate<StringSprite>())
			{
				// Incomplete one
				const auto matrix = cameraManager.GetWorldToNDCTransform();
				stringSprite->UpdateUniforms(matrix,
					obj.get()->GetTransform().CalculateWorldDepth());
				Graphics::GL::draw(*stringSprite->GetVertices(), *stringSprite->GetMaterial());
			}
			else if (const auto & sprite = obj.get()->GetComponentByTemplate<Sprite>())
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

const Graphics::CameraManager& State::GetCameraManager() const noexcept
{
	// TODO: insert return statement here
	return cameraManager;
}

void State::LevelChangeTo(std::string name)
{
	is_next = true;
	next_level = name;
}

std::string State::GetChangedLevelName()
{
	return next_level;
}

bool State::isNextLevel()
{
	return is_next;
}

GameStates State::GetStateInfo()
{
	return current_state_info;

}



void State::InstanceDEBUGObjects()
{
#ifdef _DEBUG
	ObjectManager* objManager = ObjectManager::GetObjectManager();


	LevelChangeButton* tmp = new LevelChangeButton();
	objManager->FindLayer(HUD)->AddObject(tmp);
	WallSpawner* wallSpawner = new WallSpawner();
	objManager->FindLayer(HUD)->AddObject(wallSpawner);
	
#endif
}