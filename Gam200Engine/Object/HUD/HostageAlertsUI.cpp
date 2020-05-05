/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   HostageAlertsUI.cpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 05.05.2020

    Header file for an actual objects of HostageAlertsUI
******************************************************************************/
#include <Object/HUD/HostageAlertsUI.hpp>

#include <Object/ObjectManager.hpp>

#include <Object/DepthStandard.hpp>
// components
#include <Component/Sprite/Sprite.hpp>
#include <Component/UI/HostageAlertsUIHandler.hpp>
HostageAlertsUI::HostageAlertsUI()
{
    SetObjectType(ObjectType::UI);
    SetObjectName("HostageAlertsUI");

    SetScale(vector2{0.9f, 1.6f});
    SetDepth(Depth_Standard::HUDImage);

    Sprite* sprite = new Sprite(this);
    AddComponent(sprite);
    sprite->SetImage("../assets/textures/HostageAlerts.png");

    AddComponent(new HostageAlertsUIHandler(this));
}

HostageAlertsUI::~HostageAlertsUI()
{
}