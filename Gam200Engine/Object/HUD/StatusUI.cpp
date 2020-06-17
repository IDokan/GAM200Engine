/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StatusUI.cpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 05.05.2020

    Header file for StatusUI
******************************************************************************/
#include <Object/HUD/StatusUI.hpp>

#include <Object/DepthStandard.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Component/Sprite/Animation.hpp>

#include <Component/UI/StatusUIHandler.hpp>

#include <Object/ObjectManager.hpp>

StatusUI::StatusUI()
{
    SetObjectType(ObjectType::UI);
    SetObjectName("Status UI");

	SetTranslation(vector2{ 0.88, 0.85 });
    SetScale(vector2{ 0.175f, 0.3f});
    SetDepth(Depth_Standard::HUDBackground);

    Sprite* sprite = new Sprite(this);
    AddComponent(sprite);
    sprite->SetImage("../assets/textures/UI/StatusUIBackground.png");

    AddComponent(new StatusUIHandler(this));

	animation = new Object();
	animation->SetObjectName("Status Animation");
	animation->SetTranslation(vector2{ 0.88f, 0.85f });
	animation->SetScale(vector2{ 0.1f, 0.18f });
	animation->SetDepth(Depth_Standard::HUDImage);
	Animation* animationComp = new Animation(animation);
	animation->AddComponent(animationComp);
	animationComp->SetFrame(6);
	animationComp->SetSpeed(0.f);
	animationComp->SetColor(Graphics::Color4f{ 1.f, 0.5f });
	animationComp->SetImage("../assets/textures/SavedCheese.png");
	ObjectManager::GetObjectManager()->FindLayer(HUD)->AddObject(animation);
}

StatusUI::~StatusUI()
{
}