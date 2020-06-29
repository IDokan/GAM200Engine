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

SoundManager smInCheckPoint;

CheckPointComponent::CheckPointComponent(Object* obj, Player* targetPlayer1, Player* targetPlayer2)
	: Component(obj), targetPlayer1(targetPlayer1), targetPlayer2(targetPlayer2)
{
	smInCheckPoint = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
}

CheckPointComponent::~CheckPointComponent()
{
}

void CheckPointComponent::Init()
{
}

void CheckPointComponent::Update(float /*dt*/)
{
	if (CheckPlayerIsInGoal())
	{
		vector2 ownerTranslation = owner->GetTranslation();
		SceneManager::GetSceneManager()->GetCurrentScene()->SetPlayerSpawnPosition
		(
			ownerTranslation - vector2{ UpdateAnimation::initial_scaling / 2.f, 0.f }, // player1Spawn
			ownerTranslation + vector2{ UpdateAnimation::initial_scaling / 2.f, 0.f } // player2Spawn
		);
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

	return DoesAIntersectB(ownerMin, ownerMax, player1Min, player2Max) || 
		DoesAIntersectB(ownerMin, ownerMax, player2Min, player2Max);
}
