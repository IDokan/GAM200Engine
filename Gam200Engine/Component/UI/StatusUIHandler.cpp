/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StatusUIHandler.cpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 06.17.2020

    Header file for a component that manage StatusUI
******************************************************************************/
#include <Component/UI/StatusUIHandler.hpp>
#include <Object/HUD/StatusUI.hpp>

#include <Component/MessageCapable.hpp>
#include <Systems/MessageSystem/Message.hpp>
#include <Systems/MessageSystem/MessageTypes.h>

#include <Component/Sprite/Animation.hpp>

StatusUIHandler::StatusUIHandler(StatusUI * owner)
	:Component(owner), ui(owner)
{
	ui->AddComponent(new MessageCapable(ui, MessageObjects::StatusUI,
		[&](const Message& msg)
		{
			Animation* ani;
			switch (msg.Msg)
			{
			case MessageTypes::HostageRescued:
				ani = ui->animation->GetComponentByTemplate<Animation>();
				ani->SetColor(Graphics::Color4f{ 1.f, 1.f });
				ani->SetSpeed(5.f);
				return true;
			default:
				break;
			}
			return false;
		}
	));
}

StatusUIHandler::~StatusUIHandler()
{
}

void StatusUIHandler::Init()
{
}

void StatusUIHandler::Update(float dt)
{
}

void StatusUIHandler::Clear()
{
}
