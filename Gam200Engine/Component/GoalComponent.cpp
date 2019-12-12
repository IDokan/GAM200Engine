/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   GoalComponent.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.13.2019

	Source file for goal component that will be attached at goal object
******************************************************************************/
#include <cassert>
#include <Component/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <States/StateManager.hpp>

GoalComponent::GoalComponent(Object* obj, const std::string& targetStage_, Object* targetObject_)
	: Component(obj), targetStage(targetStage_), targetObject(targetObject_)
{
	assert(targetObject_->GetComponentByTemplate<Physics>() != nullptr && "Owner object of Goal Component must have physics component!");
}

GoalComponent::~GoalComponent()
{
}

void GoalComponent::Init()
{
}

void GoalComponent::Update(float /*dt*/)
{
	if (owner->GetComponentByTemplate<Physics>()->IsCollideWith(targetObject))
	{
		StateManager::GetStateManager()->SetNextLevel(targetStage);
	}
}

void GoalComponent::Clear()
{
}
