/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   InRefrigerator.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 07.08.2020

	Source file for the state when Player is in refrigerator.
		Wait until get any input and play some animation and change to Idle state
******************************************************************************/
#include <States/PlayerStates/InRefrigerator.hpp>
#include <Component/StateMachine.hpp>
#include <Systems/Input.hpp>
#include <States/PlayerStates/Move.hpp>
#include <States/PlayerStates/Idle.hpp>
#include <Component/Sprite/Sprite.hpp>

InRefrigerator* InRefrigerator::Get()
{
	static InRefrigerator* state = new InRefrigerator();
	return state;
}

InRefrigerator::InRefrigerator()
	: ptrString(nullptr), wasInputDetected(false), timer(0.f)
{
}

void InRefrigerator::SetColor(float scaler, Player* player)
{
	switch (player->GetID())
	{
	case Player::Identifier::Player1:
		player->GetComponentByTemplate<Sprite>()->SetColor(p1Color * scaler);
		break;
	case Player::Identifier::Player2:
		player->GetComponentByTemplate<Sprite>()->SetColor(p2Color * scaler);
		break;
	}
}

void InRefrigerator::StoreColor(Player* player)
{
	switch (player->GetID())
	{
	case Player::Identifier::Player1:
		p1Color = player->GetComponentByTemplate<Sprite>()->GetColor();
		break;
	case Player::Identifier::Player2:
		p2Color = player->GetComponentByTemplate<Sprite>()->GetColor();
		break;
	}
}

void InRefrigerator::SetStringColor(float scaler)
{
	if (ptrString == nullptr)
	{
		return;
	}

	ptrString->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ scaler, scaler });
}

void InRefrigerator::Enter(Player* obj)
{
	wasInputDetected = false;
	timer = 0.f;

	StoreColor(obj);
	obj->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 0.f, 0.f });
	SetStringColor(0.f);
}

void InRefrigerator::Execute(Player* obj, float dt)
{
	if (wasInputDetected == false)
	{
		// Set True when input detected
		if (input.IsAnyKeyTriggered())
		{
			wasInputDetected = true;
		}
	}
	else
	{
		timer += dt;
		// Update
		if (timer <= EndTime)
		{
			SetColor(timer / EndTime, obj);
			SetStringColor(timer / EndTime);
			obj->GetComponentByTemplate<Physics>()->SetVelocity(vector2{ 0.f, -1.5f });
		}
		else
		{
			// When update is done,
			obj->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Idle::Get());
		}
	}
}

void InRefrigerator::Exit(Player* obj)
{
	obj->GetComponentByTemplate<Physics>()->SetVelocity(vector2{ 0.f, 0.f });
	SetColor(1.f, obj);
	SetStringColor(1.f);
}
