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

    increaseButton = new Object();
    increaseButton->SetObjectName("Volume Up");
    increaseButton->SetTranslation(vector2{ 200.f, -50.f });
    increaseButton->SetScale(vector2{ 200.f });
    increaseButton->SetDepth(Depth_Standard::HUDImage);
    increaseButton->SetObjectType(ObjectType::UI);
    increaseButton->AddComponent(new Sprite(increaseButton));
    increaseButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/IncreaseButton.png");
    increaseButton->GetTransform().SetParent(&GetTransform());
    objManager->FindLayer(Stage)->AddObject(increaseButton);

    decreaseButton = new Object();
    decreaseButton->SetObjectName("Volume Down");
    decreaseButton->SetTranslation(vector2{ -200.f, -50.f });
    decreaseButton->SetScale(vector2{ 200.f });
    decreaseButton->SetDepth(Depth_Standard::HUDImage);
    decreaseButton->SetObjectType(ObjectType::UI);
    decreaseButton->AddComponent(new Sprite(decreaseButton));
    decreaseButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/DecreaseButton.png");
    decreaseButton->GetTransform().SetParent(&GetTransform());
    objManager->FindLayer(Stage)->AddObject(decreaseButton);


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
