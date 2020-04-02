/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   VolumeSettingUIHandler.cpp
Author
		sinil.gang -rtd99062@gmail.com
Creation Date: 03.30.2020

	Source file for a component that manage VolumeSetting UI
******************************************************************************/

#include <Component/UI/VolumeSettingUIHandler.hpp>
#include <Object/HUD/VolumeSettingBarUI.hpp>
#include <Systems/Input.hpp>
#include <Vector2.hpp>

#include <Component/Sprite/Sprite.hpp>

#include <Scenes/SceneManager.hpp>
#include <Sounds/SoundManager.hpp>

VolumeSettingUIHandler::VolumeSettingUIHandler(VolumeSettingBar* owner)
	: Component(reinterpret_cast<Object*>(owner)), ui(owner)
{
}

VolumeSettingUIHandler::~VolumeSettingUIHandler()
{
}

void VolumeSettingUIHandler::Init()
{
}

void VolumeSettingUIHandler::Update(float dt)
{
	Sprite* increaseSprite = ui->increaseButton->GetComponentByTemplate<Sprite>();
	Sprite* decreaseSprite = ui->decreaseButton->GetComponentByTemplate<Sprite>();
	if (ui->isSelected == true)
	{
		if (input.IsKeyTriggered(GLFW_KEY_RIGHT) == true)
		{
			SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().MASTER_VOLUME_UP();
		}
		if (input.IsKeyPressed(GLFW_KEY_RIGHT) == true)
		{
			increaseSprite->SetColor(Graphics::Color4f{0.2f});
		}
		if (input.IsKeyReleased(GLFW_KEY_RIGHT) == true)
		{
			increaseSprite->SetColor(Graphics::Color4f{ 1.f });
		}


		if (input.IsKeyTriggered(GLFW_KEY_LEFT) == true)
		{
			SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().MASTER_VOLUME_DOWN();
		}
		if (input.IsKeyPressed(GLFW_KEY_LEFT) == true)
		{
			decreaseSprite->SetColor(Graphics::Color4f{ 0.2f });
		}
		if (input.IsKeyReleased(GLFW_KEY_LEFT) == true)
		{
			decreaseSprite->SetColor(Graphics::Color4f{ 1.f });
		}
	}
	
}

void VolumeSettingUIHandler::Clear()
{
}

void VolumeSettingUIHandler::ButtonHandle(int key, Object* button) noexcept
{
	Sprite* sprite = button->GetComponentByTemplate<Sprite>();
}
