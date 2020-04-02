/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   VolumeSettingBarUI.cpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 04.02.2020

    Source file for an actual objects of VolumeSettingBar
******************************************************************************/
#include <Object/HUD/VolumeSettingBarUI.hpp>
#include <Object/DepthStandard.hpp>
#include <Object/ObjectManager.hpp>

#include <Component/Sprite/Sprite.hpp>
#include <Component/Sprite/TextComponent.hpp>
#include <Component/UI/VolumeSettingUIHandler.hpp>

VolumeSettingBar::VolumeSettingBar(vector2 translation)
{
    SetTranslation(translation);
    SetObjectName("VolumeSettingBar");

    InitUIObjects();

    AddComponent(new VolumeSettingUIHandler(this));
}

VolumeSettingBar::~VolumeSettingBar()
{
}

void VolumeSettingBar::InitUIObjects()
{
    ObjectManager* objManager = ObjectManager::GetObjectManager();

    outline = new Object();
    outline->SetObjectName("Volume Outline");
    outline->SetScale(vector2{ 1037.f, 79.f });
    outline->SetDepth(Depth_Standard::HUDBackground);
    outline->SetObjectType(ObjectType::UI);
    outline->AddComponent(new Sprite(outline));
    outline->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 0.f });
    outline->GetTransform().SetParent(&GetTransform());
    objManager->FindLayer(Stage)->AddObject(outline);



    bar = new Object();
    bar->SetObjectName("Volume Bar");
    bar->SetScale(vector2{ 1000.f, 50.f });
    bar->SetDepth(Depth_Standard::HUDImage);
    bar->SetObjectType(ObjectType::UI);
    bar->AddComponent(new Sprite(bar));
    bar->GetTransform().SetParent(&GetTransform());
    objManager->FindLayer(Stage)->AddObject(bar);

    fillBar = new Object();
    fillBar->SetObjectName("Volume Fill Bar");
    fillBar->SetScale(vector2{ 1000.f, 50.f });
    fillBar->SetDepth(Depth_Standard::HUDImage - 1.f);
    fillBar->SetObjectType(ObjectType::UI);
    fillBar->AddComponent(new Sprite(fillBar));
    fillBar->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 0.65f, 0.f });
    fillBar->GetTransform().SetParent(&GetTransform());
    objManager->FindLayer(Stage)->AddObject(fillBar);


    circle = new Object();
    circle->SetObjectName("Volume Circle");
    circle->SetScale(vector2{ 100.f, 100.f });
    circle->SetDepth(Depth_Standard::HUDImage - 15.f);
    circle->SetObjectType(ObjectType::UI);
    circle->AddComponent(new Sprite(circle));
    circle->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/circle.png");
    circle->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 0.f, 0.f });
    circle->GetTransform().SetParent(&GetTransform());
    objManager->FindLayer(Stage)->AddObject(circle);


    circleOutline = new Object();
    circleOutline->SetObjectName("Volume Circle Outline");
    circleOutline->SetScale(vector2{ 1.25f, 1.25f });
    circleOutline->SetDepth(10.f);
    circleOutline->SetObjectType(ObjectType::UI);
    circleOutline->AddComponent(new Sprite(circleOutline));
    circleOutline->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/circle.png");
    circleOutline->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 0.f });
    circleOutline->GetTransform().SetParent(&circle->GetTransform());
    objManager->FindLayer(Stage)->AddObject(circleOutline);


    text = new Object();
    text->SetTranslation(vector2{ -157.f, 72.f });
    text->SetObjectName("Volume Text");
    text->SetDepth(Depth_Standard::HUDText);
    text->SetObjectType(ObjectType::UI);
    text->GetTransform().SetParent(&GetTransform());
    text->AddComponent(new TextComponent(text));
    text->GetComponentByTemplate<TextComponent>()->SetString(L"Master Volume");
    objManager->FindLayer(Stage)->AddObject(text);
}
