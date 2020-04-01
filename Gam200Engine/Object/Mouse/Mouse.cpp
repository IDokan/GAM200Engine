/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Mouse.cpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 03.31.2020

    Source file for an AI.
        This object derived from mouse who attacks cheese (Player).
******************************************************************************/
#include <Object/Mouse/Mouse.hpp>

// Component
#include <Component/StateMachine.hpp>
#include <Component/Physics.hpp>
#include <Component/Sprite/Animation.hpp>

// States
#include <States/AIStates/MouseIdle.hpp>

#include <Object/Players/Player.h>
#include <Object/DepthStandard.hpp>

Mouse::Mouse(vector2 translation, vector2 patrol1, vector2 patrol2, Player* player1, Player* player2, double waitTime)
    : waitTime(waitTime), localTimer(0.0), patrol_info(patrol1, patrol2), players(player1, player2)
{
    SetObjectType(ObjectType::NUM_OF_OBJECT_TYPE);
    SetTranslation(translation);
    SetScale(vector2{ 150 });
    SetDepth(Depth_Standard::MouseAI);

    SetMouseName();

    Animation* animation = new Animation(this);
    AddComponent(animation);
    animation->SetNumOfState(3);

    Physics* physics = new Physics(this);
    AddComponent(physics);
    physics->SetCollisionBoxAndObjectType(this, Physics::ObjectType::RECTANGLE);
    physics->ActiveGhostCollision(true);

    StateMachine<Mouse>* stateMachine = new StateMachine<Mouse>(this);
    AddComponent(stateMachine);
    stateMachine->SetCurrentState(MouseIdle::Get());
}

Mouse::~Mouse()
{
}

void Mouse::SetMouseName()
{
    static int MouseID = 0;

    std::string mouseName = "Mouse" + (++MouseID);
    SetObjectName(mouseName);
}

double Mouse::GetWaitTime() const noexcept
{
    return waitTime;
}

void Mouse::SetWaitTime(double time) noexcept
{
    waitTime = time;
}

double Mouse::GetLocalTimer() const noexcept
{
    return localTimer;
}

void Mouse::SetLocalTimer(double time) noexcept
{
    localTimer = time;
}

Mouse::Patrol_Info& Mouse::GetPatrolInfo() noexcept
{
    return patrol_info;
}

const Mouse::PlayerContainer& Mouse::GetPlayers() const noexcept
{
    return players;
}
