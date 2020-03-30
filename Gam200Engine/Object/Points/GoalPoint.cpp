/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   GoalPoint.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 03.20.2020

	Source file for goal object
		When player is on this (Goal Point), send message to SceneStateManager.
******************************************************************************/
#include <Object/Points/GoalPoint.hpp>

#include <cassert>

#include <Object/Players/Player.h>
#include <Object/DepthStandard.hpp>
#include <Component/Scripts/GoalComponent.hpp>

GoalPoint::GoalPoint(const Transform& transform, Player* ptrToPlayer, Graphics::Color4f highlightedColor)
	: player(ptrToPlayer)
{
	assert(ptrToPlayer != nullptr);

	SetTranslation(transform.GetTranslation());
	SetScale(transform.GetScale());
	SetDepth(Depth_Standard::GoalPoints);

	AddComponent(new GoalComponent(this, player, highlightedColor));

	AddComponent(new Sprite(this));

	switch (ptrToPlayer->GetID())
	{
	case Player::Identifier::Player1:
		LoadGoalPoint1Layout();
		break;
	case Player::Identifier::Player2:
		LoadGoalPoint2Layout();
		break;
	default:
		break;
	}
}

void GoalPoint::LoadGoalPoint1Layout() noexcept
{
	SetObjectName("GoalPoint - Player1");
	// Set appropriate image
	GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p1.png");
}

void GoalPoint::LoadGoalPoint2Layout() noexcept
{
	SetObjectName("GoalPoint - Player2");
	// Set appropriate image
	GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");
}
