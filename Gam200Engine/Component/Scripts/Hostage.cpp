/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Hostage.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 05.04.2020

	Header file for hostage.
	When it collides let scene state know hostage is rescued.
******************************************************************************/
#include <Component/Scripts/Hostage.hpp>

#include <Component/Physics.hpp>
#include <Object/Players/Player.h>
#include <Systems/MessageSystem/MessageDispatcher.hpp>
#include <Component/Sprite/Sprite.hpp>

Hostage::Hostage(Object* obj, Player* player1, Player* player2)
	: Component(obj), player1(player1), player2(player2), isRescued(false)
{
}

Hostage::~Hostage()
{
}

void Hostage::Init()
{
}

void Hostage::Update(float dt)
{
	if (isRescued == false)
	{
		if (
			owner->GetComponentByTemplate<Physics>()->IsCollideWith(player1) ||
			owner->GetComponentByTemplate<Physics>()->IsCollideWith(player2)
			)
		{
			isRescued = true;
			DispatchMessage(MessageTypes::HostageRescued);
		}
	}
	else
	{
		Sprite* sprite = owner->GetComponentByTemplate<Sprite>();
		Graphics::Color4f currentColor = sprite->GetColor();
		sprite->SetColor(Graphics::Color4f(currentColor.red, currentColor.green, currentColor.blue, currentColor.alpha - ((currentColor.alpha) * 2.5f * dt)));
		if (sprite->GetColor().alpha <= 0.f)
		{
			DispatchMessage(MessageTypes::HostageRescued);
			owner->SetDead(true);
		}
	}
}

void Hostage::Clear()
{
}

void Hostage::DispatchMessage(MessageTypes msg)
{
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Hostage, MessageObjects::SceneStateManager, msg);
}
