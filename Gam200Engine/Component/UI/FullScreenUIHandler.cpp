/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   FullScreenUIHandler.cpp
Author
		sinil.gang -rtd99062@gmail.com
Creation Date: 03.30.2020

	Source file for a component that manage FullScreen UI
******************************************************************************/


#include <Component/UI/FullScreenUIHandler.hpp>
#include <Object/HUD/FullScreenSettingUI.hpp>
#include <Systems/Input.hpp>
#include <Vector2.hpp>
#include <Component/Sprite/Animation.hpp>



FullScreenUIHandler::FullScreenUIHandler(FullScreenSettingUI* owner)
	: Component(reinterpret_cast<Object*>(owner)), ui(owner), isFullScreen(false)
{
}

FullScreenUIHandler::~FullScreenUIHandler()
{
}

void FullScreenUIHandler::Init()
{
}

void FullScreenUIHandler::Update(float dt)
{
	if (ui->isSelected == true)
	{
		if (input.IsKeyTriggered(GLFW_KEY_ENTER))
		{
			isFullScreen = !isFullScreen;
			input.SetShouldToggleWindow(true);
			if (isFullScreen == true)
			{
				ui->checkBox->GetComponentByTemplate<Animation>()->SetState(1);
			}
			else
			{
				ui->checkBox->GetComponentByTemplate<Animation>()->SetState(0);
			}
		}
	}
}

void FullScreenUIHandler::Clear()
{
}
