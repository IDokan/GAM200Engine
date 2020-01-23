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

Idle* Idle::Get()
{
	static Idle* state = new Idle();
}

Idle::Idle()
{
}

void Idle::Enter(Player* obj)
{
	// Set appropriate sprite
}

void Idle::Execute(Player* obj)
{
	if (input.IsKeyTriggered(GLFW_KEY_W) ||
		input.IsKeyTriggered(GLFW_KEY_A) ||
		input.IsKeyTriggered(GLFW_KEY_S) ||
		input.IsKeyTriggered(GLFW_KEY_D))
	{
		obj->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Move::Get());
	}	
}

void Idle::Exit(Player* obj)
{
	
}
