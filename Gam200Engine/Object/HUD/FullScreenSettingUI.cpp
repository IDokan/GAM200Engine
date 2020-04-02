/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   FullScreenSettingUI.cpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 04.02.2020

    Source file for an actual objects of FullScreenSettingUI
******************************************************************************/
#include <Object/HUD/FullScreenSettingUI.hpp>
#include <Object/DepthStandard.hpp>
#include <Object/ObjectManager.hpp>

#include <Component/Sprite/Sprite.hpp>
#include <Component/Sprite/TextComponent.hpp>
#include <Component/Sprite/Animation.hpp>
#include <Component/UI/FullScreenUIHandler.hpp>

FullScreenSettingUI::FullScreenSettingUI(vector2 translation)
{
    SetTranslation(translation);
    SetObjectName("Full Screen Setting UI");

    InitUIObjects();

    AddComponent(new FullScreenUIHandler(this));
}

FullScreenSettingUI::~FullScreenSettingUI()
{
}

void FullScreenSettingUI::InitUIObjects()
{
    ObjectManager* objManager = ObjectManager::GetObjectManager();

    checkBox = new Object();
    checkBox->SetObjectName("Check Box");
    checkBox->SetTranslation(vector2{ 250.f, 0.f });
    checkBox->SetScale(vector2{ 100.f });
    checkBox->SetDepth(Depth_Standard::HUDImage);
    checkBox->SetObjectType(ObjectType::UI);
    checkBox->AddComponent(new Animation(checkBox));
    checkBox->GetComponentByTemplate<Animation>()->SetImage("../assets/textures/CheckBox.png");
    checkBox->GetComponentByTemplate<Animation>()->SetNumOfState(2);
    checkBox->GetTransform().SetParent(&GetTransform());
    objManager->FindLayer(Stage)->AddObject(checkBox);


    text = new Object();
    text->SetTranslation(vector2{ -250.f, 0.f });
    text->SetObjectName("Fullscreen Text");
    text->SetDepth(Depth_Standard::HUDText);
    text->SetObjectType(ObjectType::UI);
    text->GetTransform().SetParent(&GetTransform());
    text->AddComponent(new TextComponent(text));
    text->GetComponentByTemplate<TextComponent>()->SetString(L"Full Screen");
    objManager->FindLayer(Stage)->AddObject(text);
}
