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

#include <Component/Sprite/Sprite.hpp>
#include <Component/Scripts/CheckPointComponent.hpp>

CheckPoint::CheckPoint(const Transform& transform, Player* ptrToPlayer1, Player* ptrToPlayer2)
{
	SetTranslation(transform.GetTranslation());
	SetScale(transform.GetScale());
	SetDepth(Depth_Standard::Points);

	AddComponent(new CheckPointComponent(this, ptrToPlayer1, ptrToPlayer2));

	Sprite* placeHolder = new Sprite(this);
	AddComponent(placeHolder);

	SetObjectName("CheckPoint");
}