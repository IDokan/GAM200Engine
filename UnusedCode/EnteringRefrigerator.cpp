/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   EnteringRefrigerator.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 07.08.2020

	Source file for the state when Player is in refrigerator.
		Wait until get any input and play some animation and change to Idle state
******************************************************************************/
#include <States/PlayerStates/EnteringRefrigerator.hpp>
#include <States/PlayerStates/InRefrigerator.hpp>
#include <Component/StateMachine.hpp>
#include <Systems/Input.hpp>
#include <States/PlayerStates/Move.hpp>
#include <States/PlayerStates/Idle.hpp>

EnteringRefrigerator* EnteringRefrigerator::Get()
{
	static EnteringRefrigerator* state = new EnteringRefrigerator();
	return state;
}

EnteringRefrigerator::EnteringRefrigerator()
	: timer(0.f)
{
}

void EnteringRefrigerator::SetColor(float scaler, Player* player)
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

void EnteringRefrigerator::StoreVariables(Player* player)
{
	switch (player->GetID())
	{
	case Player::Identifier::Player1:
		p1Color = player->GetComponentByTemplate<Sprite>()->GetColor();
		p1Position = player->GetTranslation();
		break;
	case Player::Identifier::Player2:
		p2Color = player->GetComponentByTemplate<Sprite>()->GetColor();
		p2Position = player->GetTranslation();
		break;
	}
}

vector2 EnteringRefrigerator::LerpPosition(float scaler, Player* player)
{
	switch (player->GetID())
	{
	case Player::Identifier::Player1:
		return p1Position + (scaler) * (TargetPosition - p1Position);
		break;
	case Player::Identifier::Player2:
		return p2Position + (scaler) * (TargetPosition - p2Position);
		break;
	default:
		break;
	}
}

void EnteringRefrigerator::Enter(Player* obj)
{
	timer = 0.f;

	StoreVariables(obj);
}

void EnteringRefrigerator::Execute(Player* obj, float dt)
{
	timer += dt;
	if (timer < EndTime)
	{
		SetColor(1.f - (timer / EndTime), obj);
		obj->SetTranslation(LerpPosition(timer / EndTime, obj));
	}
	else
	{
		obj->GetComponentByTemplate<Physics>()->SetVelocity(vector2{ 0.f });
		obj->SetTranslation(LerpPosition(1.f, obj));
		obj->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(InRefrigerator::Get());
	}
}

void EnteringRefrigerator::Exit(Player* obj)
{
	SetColor(1.f, obj);
}
