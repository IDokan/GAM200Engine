/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringLengthUIHandler.cpp
Author
		sinil.gang -rtd99062@gmail.com
Creation Date: 03.30.2020

	Source file for a component that manage StringLength UI
******************************************************************************/

#include <iostream>

#include <Component/UI/StringLengthUIHandler.hpp>

// Objects
#include <Object/Object.hpp>
#include <Object/HUD/StringLengthUI.hpp>
#include <Object/Strings/String.hpp>

// Components
#include <Component/MessageCapable.hpp>
#include <Systems/MessageSystem/Message.hpp>

StringLengthUIHandler::StringLengthUIHandler(StringLengthUI* owner)
	:Component(dynamic_cast<Object*>(owner)), ui(owner)
{
}

StringLengthUIHandler::~StringLengthUIHandler()
{
}

void StringLengthUIHandler::Init()
{
	owner->AddComponent(new MessageCapable(owner, MessageObjects::StringLengthUI, [&](const Message& msg)
		{
			float currentStringLength = 0.f;
			vector2 uiTranslation;
			switch (msg.Msg)
			{
			case MessageTypes::StringIsStreching:
				currentStringLength = *reinterpret_cast<float*>(msg.ExtraInfo);

				ui->SetBarScale((currentStringLength - String::String_Stretching_Length) / (String::String_Max_Length - String::String_Stretching_Length));

				// Show UI
				uiTranslation = ui->GetTranslation();
				ui->SetTranslation(vector2{ uiTranslation.x, uiTranslation.y + (0.1f * (StringLengthUI::SHOW_Y - uiTranslation.y)) });

				shouldShowing = true;
				return true;
			default:
				break;
			}

			return false;
		}
		)
		);
}

void StringLengthUIHandler::Update(float /*dt*/)
{
	if (shouldShowing == true)
	{
		shouldShowing = false;
		return;
	}

	// Hide UI
	vector2 uiTranslation = ui->GetTranslation();
	ui->SetTranslation(vector2{ uiTranslation.x, uiTranslation.y + (0.1f * (StringLengthUI::HIDE_Y - uiTranslation.y)) });

}

void StringLengthUIHandler::Clear()
{
}
