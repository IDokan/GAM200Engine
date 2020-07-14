/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MouseIdle.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.31.2020

	Source file for Idle State
		This state wait for input to move.
		AI
******************************************************************************/
#include <States/AIStates/MouseIdle.hpp>
#include <States/AIStates/Patrol.hpp>
#include <Component/StateMachine.hpp>
#include <Component/Sprite/Animation.hpp>

#include <Object/Mouse/Mouse.hpp>

#include <Systems/Timer.hpp>

void MouseIdle::Enter(Mouse* mouse)
{
	mouse->SetLocalTimer(0.0);
	Animation* mouseAnimation = mouse->GetComponentByTemplate<Animation>();
	mouseAnimation->SetState(0);
	mouseAnimation->SetSpeed(5.f);
	mouseAnimation->SetIndex(0.f);
}

void MouseIdle::Execute(Mouse* mouse, float dt)
{
	mouse->SetLocalTimer(mouse->GetLocalTimer() + dt);
	
	if (mouse->GetLocalTimer() > mouse->GetWaitTime())
	{
		mouse->GetComponentByTemplate<StateMachine<Mouse>>()->ChangeState(Patrol::Get());
	}
}

void MouseIdle::Exit(Mouse* mouse)
{
}


MouseIdle* MouseIdle::Get()
{
	static MouseIdle* state = new MouseIdle();
	return state;
}