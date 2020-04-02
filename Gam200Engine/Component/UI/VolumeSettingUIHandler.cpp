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
	if (vector2 translation = ui->circle->GetTranslation();
		translation.x < VolumeSettingBar::minX)
	{
		ui->circle->SetTranslation(vector2{ VolumeSettingBar::minX , translation.y });
	}
	else if (translation.x > VolumeSettingBar::maxX)
	{
		ui->circle->SetTranslation(vector2{ VolumeSettingBar::maxX , translation.y });
	}

	vector2 circleTranslation = ui->circle->GetTranslation();
	ui->fillBar->SetTranslation(vector2{ (VolumeSettingBar::minX + circleTranslation.x) / 2.f, circleTranslation.y });
	ui->fillBar->SetScale(vector2{ (circleTranslation.x - VolumeSettingBar::minX), ui->fillBar->GetScale().y });

	if (ui->isSelected == true)
	{
		if (input.IsKeyTriggered(GLFW_KEY_LEFT) == true)
		{
			ui->circle->SetTranslation(vector2{ circleTranslation.x - 50.f, circleTranslation.y });
		}
		if (input.IsKeyPressed(GLFW_KEY_LEFT) == true)
		{
			ui->circle->SetTranslation(vector2{ circleTranslation.x - 10.f, circleTranslation.y });
		}
		if (input.IsKeyTriggered(GLFW_KEY_RIGHT) == true)
		{
			ui->circle->SetTranslation(vector2{ circleTranslation.x + 50.f, circleTranslation.y });
		}
		if (input.IsKeyPressed(GLFW_KEY_RIGHT) == true)
		{
			ui->circle->SetTranslation(vector2{ circleTranslation.x + 10.f, circleTranslation.y });
		}
	}
}

void VolumeSettingUIHandler::Clear()
{
}
