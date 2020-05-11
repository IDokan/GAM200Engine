/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   UpdateAnimation.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.08.2020

	Source file for UpdateAnimation State
		This state is global state which update animation with object's velocity.
******************************************************************************/
#include <States/PlayerStates/UpdateAnimation.hpp>
#include <Component/StateMachine.hpp>

UpdateAnimation* UpdateAnimation::Get()
{
	static UpdateAnimation* state = new UpdateAnimation();
	return state;
}

UpdateAnimation::UpdateAnimation()
{
}

void UpdateAnimation::Enter(Player* /*obj*/)
{
}

void UpdateAnimation::Execute(Player* obj, float /*dt*/)
{
	// TODO: Change Mechs with Co-developer's feedbacks.
	vector2 playerDistance = obj->GetComponentByTemplate<Physics>()->GetVelocity();
	static constexpr int RIGHT = 0;
	static constexpr int LEFT = 1;
	static constexpr int UP = 2;
	if (playerDistance.x > 0)
	{
		obj->GetComponentByTemplate<Animation>()->SetState(RIGHT);
	}
	else if (playerDistance.x < 0)
	{
		obj->GetComponentByTemplate<Animation>()->SetState(LEFT);
	}
	else
	{
		// Do nothing
	}
}

void UpdateAnimation::Exit(Player* /*obj*/)
{
}
