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
#include <string>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Scenes/SceneManager.hpp>
#include <Object/Players/Player.h>
#include <Vector2.hpp>
#include <Sounds/SoundManager.hpp>

#include <Systems/MessageSystem/MessageDispatcher.hpp>

SoundManager smInGoal;
GoalComponent::GoalComponent(Object* obj, Player* targetPlayer, Graphics::Color4f color)
	: Component(obj), targetPlayer(targetPlayer), isPlayerOnGoal(false), highlightedColor(color)
{
	smInGoal = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
}

GoalComponent::~GoalComponent()
{
}

void GoalComponent::Init()
{
    //testSoundforGoalPoint.Load_Sound();
}

void GoalComponent::Update(float /*dt*/)
{
	vector2 playerMin{ targetPlayer->GetTranslation() - (targetPlayer->GetScale() / 2.f)};
	vector2 playerMax{ targetPlayer->GetTranslation() + (targetPlayer->GetScale() / 2.f) };
	vector2 ownerMin{ owner->GetTranslation() - (owner->GetScale() / 2.f) };
	vector2 ownerMax{ owner->GetTranslation() + (owner->GetScale() / 2.f) };

	if (isPlayerOnGoal)
	{
		// Check isNotPlayerOnGoal
		if (IsAInsideB(playerMin, playerMax, ownerMin, ownerMax) == false)
		{
			DispatchMessage(MessageTypes::PlayerExitedFromGoal);
			isPlayerOnGoal = false;
			owner->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f });
		}
	}
	else
	{
		// Check isPlayerInsideGoal
		if (IsAInsideB(playerMin, playerMax, ownerMin, ownerMax))
		{
			DispatchMessage(MessageTypes::PlayerReachedGoal);
			isPlayerOnGoal = true;
			owner->GetComponentByTemplate<Sprite>()->SetColor(highlightedColor);
		}
	}
}

void GoalComponent::Clear()
{
}

std::string GoalComponent::GetTargetStage()
{
	return targetStage;
}

bool GoalComponent::IsAInsideB(const vector2& minOfA, const vector2& maxOfA, const vector2& minOfB, const vector2& maxOfB) const noexcept
{
	return minOfA.x > minOfB.x && minOfA.y > minOfB.y &&
		maxOfA.x < maxOfB.x && maxOfA.y < maxOfB.y;
}

void GoalComponent::DispatchMessage(MessageTypes msg)
{
	switch (Player::Identifier id = targetPlayer->GetID())
	{
	case Player::Identifier::Player1:
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Player1, MessageObjects::SceneStateManager, msg);
		break;
	case Player::Identifier::Player2:
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Player2, MessageObjects::SceneStateManager, msg);
		break;
	default:
		break;
	}
}
