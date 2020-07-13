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
#include <Vector2.hpp>
#include <Sounds/SoundManager.hpp>

#include <Systems/MessageSystem/MessageDispatcher.hpp>

GoalComponent::GoalComponent(Object* obj, Player* targetPlayer1, Player* targetPlayer2)
    : Component(obj), targetPlayer1(targetPlayer1), targetPlayer2(targetPlayer2), isPlayerOnGoal1(false), isPlayerOnGoal2(false), doorSoundTriggerd(false)
{
}

GoalComponent::~GoalComponent()
{
}

void GoalComponent::Init()
{
}

void GoalComponent::Update(float /*dt*/)
{
    CheckPlayerIsInGoal(Player::Identifier::Player1);
    CheckPlayerIsInGoal(Player::Identifier::Player2);

    if (isPlayerOnGoal1 == false && isPlayerOnGoal2 == false)
    {
        doorSoundTriggerd = false;
        owner->GetComponentByTemplate<Animation>()->SetState(0);
    }
    else if (isPlayerOnGoal1 == true && isPlayerOnGoal2 == true)
    {
        owner->GetComponentByTemplate<Animation>()->SetState(2);
        if (doorSoundTriggerd == false) {
            SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(GOAL_DOORTRIGGER_SOUND);
            doorSoundTriggerd = true;
        }
    }
    else
    {
        owner->GetComponentByTemplate<Animation>()->SetState(1);
        if (doorSoundTriggerd == false) {
            SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(GOAL_DOORTRIGGER_SOUND);
            doorSoundTriggerd = true;
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

void GoalComponent::CheckPlayerIsInGoal(Player::Identifier id)
{
    Player* player;
    bool& isPlayerOnGoal = (id == Player::Identifier::Player1) ? isPlayerOnGoal1 : isPlayerOnGoal2;
    switch (id)
    {
    case Player::Identifier::Player1:
        player = targetPlayer1;
        break;
    case Player::Identifier::Player2:
        player = targetPlayer2;
        break;
    case Player::Identifier::UNDEFINED:
        break;
    default:
        break;
    }


    vector2 playerMin{ player->GetTranslation() - (player->GetScale() / 2.f) };
    vector2 playerMax{ player->GetTranslation() + (player->GetScale() / 2.f) };
    vector2 ownerMin{ owner->GetTranslation() - (owner->GetScale() / 2.f) };
    vector2 ownerMax{ owner->GetTranslation() + (owner->GetScale() / 2.f) };

    if (isPlayerOnGoal)
    {
        // Check isNotPlayerOnGoal
        if (IsAInsideB(playerMin, playerMax, ownerMin, ownerMax) == false)
        {
            DispatchMessage(id, MessageTypes::PlayerExitedFromGoal);
            isPlayerOnGoal = false;
        }
    }
    else
    {
        // Check isPlayerInsideGoal
        if (IsAInsideB(playerMin, playerMax, ownerMin, ownerMax))
        {
            DispatchMessage(id, MessageTypes::PlayerReachedGoal);
            isPlayerOnGoal = true;
        }
    }
}

bool GoalComponent::IsAInsideB(const vector2& minOfA, const vector2& maxOfA, const vector2& minOfB, const vector2& maxOfB) const noexcept
{
    return minOfA.x > minOfB.x && minOfA.y > minOfB.y &&
        maxOfA.x < maxOfB.x&& maxOfA.y < maxOfB.y;
}

void GoalComponent::DispatchMessage(Player::Identifier id, MessageTypes msg)
{
    switch (id)
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
