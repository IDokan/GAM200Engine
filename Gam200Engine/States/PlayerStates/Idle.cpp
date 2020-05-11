/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Idle.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.13.2020

	Source file for Idle State
		This state wait for input to move.
******************************************************************************/
#include <States/PlayerStates/Idle.hpp>
#include <Component/StateMachine.hpp>
#include <Systems/Input.hpp>
#include <States/PlayerStates/Move.hpp>
#include <Systems/Input.hpp>

bool IsPlayer1InputDetected()
{
	return input.IsKeyTriggered(GLFW_KEY_W) ||
		input.IsKeyTriggered(GLFW_KEY_A) ||
		input.IsKeyTriggered(GLFW_KEY_S) ||
		input.IsKeyTriggered(GLFW_KEY_D);
}

bool IsPlayer2InputDetected()
{
	return input.IsKeyTriggered(GLFW_KEY_UP) ||
		input.IsKeyTriggered(GLFW_KEY_RIGHT) ||
		input.IsKeyTriggered(GLFW_KEY_LEFT) ||
		input.IsKeyTriggered(GLFW_KEY_DOWN);
}

Idle* Idle::Get()
{
	static Idle* state = new Idle();
	return state;
}

Idle::Idle()
{
}

void Idle::Enter(Player* /*obj*/)
{
	// Set appropriate sprite
	printf("Player enter Idle State\n");
}

void Idle::Execute(Player* obj, float /*dt*/)
{
	if (obj->GetID() == Player::Identifier::Player1)
	{
		if (IsPlayer1InputDetected())
		{
			obj->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Move::Get());
		}
	}
	else if (obj->GetID() == Player::Identifier::Player2)
	{
		if (IsPlayer2InputDetected())
		{
			obj->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Move::Get());
		}
	}
}

void Idle::Exit(Player* /*obj*/)
{
	printf("Player exit Idle State\n");
}
