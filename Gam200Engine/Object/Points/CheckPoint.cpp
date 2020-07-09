/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   CheckPoint.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 06.29.2020

	Source file for Check Point
		When player is on this (Check Point), save progress
******************************************************************************/
#include <Object/Points/CheckPoint.hpp>
#include <Object/DepthStandard.hpp>

#include <Component/Sprite/Animation.hpp>
#include <Component/Scripts/CheckPointComponent.hpp>

CheckPoint::CheckPoint(const vector2& translation, Player* ptrToPlayer1, Player* ptrToPlayer2)
{
	SetTranslation(translation);
	SetScale(vector2{ 300.f, 270.f });
	SetDepth(Depth_Standard::Points);

	AddComponent(new CheckPointComponent(this, ptrToPlayer1, ptrToPlayer2));

	// TODO: Have to add Refrigerator image
	Animation* checkAnimation = new Animation(this);
	checkAnimation->SetImage("../assets/textures/Refrigerator.png");
	checkAnimation->SetNumOfState(2);
	checkAnimation->SetState(0);
	checkAnimation->SetSpeed(0.f);
	AddComponent(checkAnimation);

	SetObjectName("CheckPoint");
}