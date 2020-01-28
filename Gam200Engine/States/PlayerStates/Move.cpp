/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Move.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.13.2020

	Header file for Move State
		This state execute move
******************************************************************************/
#include <States/PlayerStates/Move.hpp>
#include <Systems/Input.hpp>
#include <Object/Object.hpp>
#include <Component/Physics.hpp>
#include <Component/StateMachine.hpp>
#include <States/PlayerStates/Idle.hpp>

Move* Move::Get()
{
	static Move* state = new Move();
	return state;
}

void Move::Enter(Player* /*obj*/)
{
	// Do appropriate setting in here
	printf("Player enter Move State\n");
}

void Move::Execute(Player* obj)
{
	if (obj->GetID() == Player::Identifier::Player1)
	{
		/**********************Moving Object 1*******************************************/
		if (input.IsKeyPressed(GLFW_KEY_W))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
			if (input.IsKeyPressed(GLFW_KEY_D))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
			}
			else if (input.IsKeyPressed(GLFW_KEY_A))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
			}
		}
		if (input.IsKeyPressed(GLFW_KEY_A))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
			if (input.IsKeyPressed(GLFW_KEY_W))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
			}
			else if (input.IsKeyPressed(GLFW_KEY_S))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
			}
		}
		if (input.IsKeyPressed(GLFW_KEY_S))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

			if (input.IsKeyPressed(GLFW_KEY_A))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
			}
			else if (input.IsKeyPressed(GLFW_KEY_D))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
			}
		}
		if (input.IsKeyPressed(GLFW_KEY_D))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
			if (input.IsKeyPressed(GLFW_KEY_W))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
			}
			else if (input.IsKeyPressed(GLFW_KEY_S))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
			}
		}
		if (input.IsKeyReleased(GLFW_KEY_W) && input.IsKeyReleased(GLFW_KEY_A) && input.IsKeyReleased(GLFW_KEY_S) && input.IsKeyReleased(GLFW_KEY_D))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
			obj->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Idle::Get());
		}
	}
	else if (obj->GetID() == Player::Identifier::Player2)
	{

		/**********************Moving Object 2*******************************************/
		if (input.IsKeyPressed(GLFW_KEY_UP))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
			if (input.IsKeyPressed(GLFW_KEY_RIGHT))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
			}
			else if (input.IsKeyPressed(GLFW_KEY_LEFT))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
			}
		}
		if (input.IsKeyPressed(GLFW_KEY_LEFT))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
			if (input.IsKeyPressed(GLFW_KEY_UP))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
			}
			else if (input.IsKeyPressed(GLFW_KEY_DOWN))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
			}
		}
		if (input.IsKeyPressed(GLFW_KEY_DOWN))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

			if (input.IsKeyPressed(GLFW_KEY_LEFT))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
			}
			else if (input.IsKeyPressed(GLFW_KEY_RIGHT))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
			}
		}
		if (input.IsKeyPressed(GLFW_KEY_RIGHT))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
			if (input.IsKeyPressed(GLFW_KEY_UP))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
			}
			else if (input.IsKeyPressed(GLFW_KEY_DOWN))
			{
				obj->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
			}
		}
		if (input.IsKeyReleased(GLFW_KEY_UP) && input.IsKeyReleased(GLFW_KEY_LEFT) && input.IsKeyReleased(GLFW_KEY_DOWN) && input.IsKeyReleased(GLFW_KEY_RIGHT))
		{
			obj->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
			obj->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Idle::Get());
		}
	}
}

void Move::Exit(Player* /*obj*/)
{
	printf("Player exit Move State\n");
}
