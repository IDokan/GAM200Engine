/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   CheckPointComponent.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 06.29.2020

	Source file for Check Point logic
******************************************************************************/
#include <Component/Scripts/CheckPointComponent.hpp>

#include <Sounds/SoundManager.hpp>
#include <Scenes/SceneManager.hpp>
#include <Vector2.hpp>
#include <Object/Players/Player.h>

#include <States/PlayerStates/UpdateAnimation.hpp>
#include <Object/Points/CheckPoint.hpp>

SoundManager smInCheckPoint;

CheckPointComponent::CheckPointComponent(Object* obj, Player* targetPlayer1, Player* targetPlayer2)
	: Component(obj), targetPlayer1(targetPlayer1), targetPlayer2(targetPlayer2), delayTimer(-20.f)
{
	smInCheckPoint = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
}

CheckPointComponent::~CheckPointComponent()
{
}

void CheckPointComponent::Init()
{
}

void CheckPointComponent::Update(float dt)
{
	Scene* currentScene = SceneManager::GetSceneManager()->GetCurrentScene();
	if (owner == currentScene->lastCheckPoint)
	{
		return;
	}

	if (delayTimer > -10.f && delayTimer < 2.f)
	{
		delayTimer += dt;
		return;
	}

	if (CheckPlayerIsInGoal())
	{
		vector2 ownerTranslation = owner->GetTranslation();
		
		currentScene->lastCheckPoint->GetComponentByTemplate<Animation>()->SetState(0);
		currentScene->lastCheckPoint->SetEmitterOn(false);
		currentScene->lastCheckPoint = dynamic_cast<CheckPoint*>(owner);
		currentScene->lastCheckPoint->SetEmitterOn(true);
		currentScene->lastCheckPoint->GetComponentByTemplate<Animation>()->SetState(1);

		// TODO: Add Play_Sound(REFRIGERATOR_TRIGGERED_SOUND) here

		delayTimer = 0.f;
	}
}

void CheckPointComponent::Clear()
{
}

bool CheckPointComponent::DoesAIntersectB(const vector2& minOfA, const vector2& maxOfA, const vector2& minOfB, const vector2& maxOfB) const noexcept
{
	return minOfA.x < maxOfB.x && minOfA.y < maxOfB.y &&
		maxOfA.x > minOfB.x && maxOfA.y > minOfB.y;
}

bool CheckPointComponent::CheckPlayerIsInGoal()
{
	vector2 ownerTraslation = owner->GetTranslation();
	vector2 ownerScale = owner->GetScale();
	vector2 ownerMin{ ownerTraslation - (ownerScale / 2.f) };
	vector2 ownerMax{ ownerTraslation + (ownerScale / 2.f) };

	vector2 player1Translation = targetPlayer1->GetTranslation();
	vector2 player1Scale = targetPlayer1->GetScale();
	vector2 player1Min{ player1Translation - (player1Scale / 2.f) };
	vector2 player1Max{ player1Translation + (player1Scale / 2.f) };

	vector2 player2Translation = targetPlayer2->GetTranslation();
	vector2 player2Scale = targetPlayer2->GetScale();
	vector2 player2Min{ player2Translation - (player2Scale / 2.f) };
	vector2 player2Max{ player2Translation + (player2Scale / 2.f) };

	return DoesAIntersectB(ownerMin, ownerMax, player1Min, player1Max) || 
		DoesAIntersectB(ownerMin, ownerMax, player2Min, player2Max);
}
