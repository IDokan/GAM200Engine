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

GoalPoint::GoalPoint(const Transform& transform, Player* ptrToPlayer1, Player* ptrToPlayer2)
{
	assert(ptrToPlayer1 != nullptr);

	SetTranslation(transform.GetTranslation());
	SetScale(transform.GetScale());
	SetDepth(Depth_Standard::GoalPoints);

	AddComponent(new GoalComponent(this, ptrToPlayer1, ptrToPlayer2));

	Animation* animation = new Animation(this);
	AddComponent(animation);
	animation->SetNumOfState(3);
	animation->SetSpeed(0.f);
	animation->SetState(0);


	SetObjectName("GoalPoint");
	GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalDoor.png");
}