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
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Scenes/SceneManager.hpp>
#include <iostream>


#include "Sounds/SoundManager.hpp"

SoundManager testSoundforGoalPoint;
GoalComponent::GoalComponent(Object* obj, const std::string& targetStage_)
	: Component(obj), targetStage(targetStage_)
{
}

GoalComponent::~GoalComponent()
{
}

void GoalComponent::Init()
{
    testSoundforGoalPoint.Load_Sound();
}

void GoalComponent::Update(float /*dt*/)
{
	if (owner->GetComponentByTemplate<Physics>()->GetIsCollide())
	{
        testSoundforGoalPoint.Play_Sound(SOUNDS::GOAL_SOUND);
        testSoundforGoalPoint.SetVolume(GOAL_SOUND, 0.5);

        
        // TODO: Add Music
		SceneManager::GetSceneManager()->SetNextScene(targetStage);
	}
}

void GoalComponent::Clear()
{
}
