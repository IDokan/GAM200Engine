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
#include <iostream>

GoalComponent::GoalComponent(Object* obj, const std::string& targetStage_)
	: Component(obj), targetStage(targetStage_)
{
}

GoalComponent::~GoalComponent()
{
}

void GoalComponent::Init()
{
}

void GoalComponent::Update(float dt)
{
	if (owner->GetComponentByTemplate<Physics>()->GetIsCollide())
	{
		StateManager::GetStateManager()->SetNextLevel(targetStage);
	}
}

void GoalComponent::Clear()
{
}
