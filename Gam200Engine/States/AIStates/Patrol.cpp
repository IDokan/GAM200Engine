/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Patrol.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.31.2020

	Source file for Idle State
		When AI is in this state, AI patrol determined two position.
		AI
******************************************************************************/
#include <States/AIStates/Patrol.hpp>
#include <Object/Mouse/Mouse.hpp>
#include <Object/Players/Player.h>

#include <Component/Physics.hpp>
#include <Component/StateMachine.hpp>
#include <Component/Sprite/Animation.hpp>

#include <States/AIStates/MouseIdle.hpp>
#include <Vector2.hpp>

#include <Systems/MessageSystem/MessageDispatcher.hpp>

void Patrol::Enter(Mouse* mouse)
{
	mouse->GetComponentByTemplate<Animation>()->SetState(1);
}

void Patrol::Execute(Mouse* mouse)
{
	Mouse::Patrol_Info& patrol_info = mouse->GetPatrolInfo();
	if (patrol_info.isGoingTOA == true)
	{
		MoveMouse(mouse, patrol_info.positionA);
	}
	else
	{
		MoveMouse(mouse, patrol_info.positionB);
	}

	AttackPlayers(mouse);
}

void Patrol::Exit(Mouse* mouse)
{
	mouse->GetPatrolInfo().isGoingTOA = !mouse->GetPatrolInfo().isGoingTOA;
}

Patrol* Patrol::Get()
{
	static Patrol* state = new Patrol();
	return state;
}

void Patrol::MoveMouse(Mouse* mouse, vector2 position)
{
	vector2 mousePosition = mouse->GetTranslation();
	Physics* physics = mouse->GetComponentByTemplate<Physics>();
	mouse->SetTranslation(physics->GetPosition());

	vector2 targetVector = position - mousePosition;

	if (magnitude_squared(targetVector) < 6.f)
	{
		mouse->GetComponentByTemplate<StateMachine<Mouse>>()->ChangeState(MouseIdle::Get());
		return;
	}

	targetVector = normalize(targetVector);


	targetVector *= 3.f;

	physics->SetVelocity(targetVector);

	if (canMouseSeePlayer(mouse) == true)
	{
		physics->SetVelocity(targetVector * 2.f);
	}
}

bool Patrol::canMouseSeePlayer(Mouse* mouse)
{
	vector2 velocity = mouse->GetComponentByTemplate<Physics>()->GetVelocity();
	velocity = normalize(velocity);

	vector2 mouseEye = mouse->GetPlayers().player1->GetTranslation() - mouse->GetTranslation();
	mouseEye = normalize(mouseEye);

	if (dot(velocity, mouseEye) > 0.f
		&& magnitude_squared(mouseEye) < 50.f)
	{
		return true;
	}

	mouseEye = mouse->GetPlayers().player2->GetTranslation() - mouse->GetTranslation();
	mouseEye = normalize(mouseEye);

	if (dot(velocity, mouseEye) > 0.f
		&& magnitude_squared(mouseEye) < 50.f)
	{
		return true;
	}

	return false;
}

void Patrol::AttackPlayers(Mouse* mouse)
{
	Physics* physics = mouse->GetComponentByTemplate<Physics>();
	const Mouse::PlayerContainer& players = mouse->GetPlayers();
	if (physics->IsCollideWith(players.player1) == true ||
		physics->IsCollideWith(players.player2) == true)
	{
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Mouse, MessageObjects::SceneStateManager, MessageTypes::PlayerIsDead);
		mouse->GetComponentByTemplate<StateMachine<Mouse>>()->ChangeState(MouseIdle::Get());
		mouse->GetComponentByTemplate<Animation>()->SetState(2);
	}
	else
	{
		mouse->GetComponentByTemplate<Animation>()->SetState(1);
	}
}