/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringLengthUI.cpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 03.30.2020

    Source file for a StringLengthUI
******************************************************************************/
#include <Object/HUD/StringLengthUI.hpp>

// Components
#include <Component/Sprite/Sprite.hpp>
#include <Component/Sprite/TextComponent.hpp>
#include <Component/MessageCapable.hpp>
#include <Component/UI/StringLengthUIHandler.hpp>

// Depths
#include <Object/DepthStandard.hpp>

// Managers
#include <Object/ObjectManager.hpp>

StringLengthUI::StringLengthUI()
{
    SetObjectName("StringLengthUI");
    SetTranslation(vector2{ 0.f, -1.05f });
    SetScale(vector2{ 1.f });
    // No depth

    AddComponent(new StringLengthUIHandler(this));

    InitUIObjects();
}

StringLengthUI::~StringLengthUI()
{
}

void StringLengthUI::SetBarScale(float x) noexcept
{
    // x cannot be smaller than 0.1f
    if (x < 0.1f)
    {
        x = 0.1f;
    }
    vector2 scale = bar->GetScale();
    bar->SetScale(vector2{ x, scale.y });
}

void StringLengthUI::InitUIObjects()
{
    outline = new Object();
    outline->SetObjectName("Outline of StringUI");
    outline->SetScale(vector2{ 1.02f, 0.095f });
    Sprite* outlineSprite = new Sprite(outline);
    outline->AddComponent(outlineSprite);
    outlineSprite->SetColor(Graphics::Color4f(0.1f));
    outline->SetDepth(Depth_Standard::HUD);
    outline->GetTransform().SetParent(&transform);


    background = new Object();
    background->SetObjectName("Background of StringUI");
    background->SetScale(vector2{ 1.f, 0.075f });
    Sprite* backgroundSprite = new Sprite(background);
    background->AddComponent(backgroundSprite);
    backgroundSprite->SetColor(Graphics::Color4f(1.f, 0.847f, 0.4f));
    background->SetDepth(Depth_Standard::HUDBackground);
    background->GetTransform().SetParent(&transform);


    bar = new Object();
    bar->SetObjectName("bar of StringUI");
    Sprite* barSprite = new Sprite(bar);
    bar->AddComponent(barSprite);
    barSprite->SetColor(Graphics::Color4f(1.f, 0.65f, 0.f));
    bar->SetScale(vector2{ 0.5f, 0.075f });
    bar->SetDepth(Depth_Standard::HUDImage);
    bar->GetTransform().SetParent(&transform);




    ObjectManager* objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::HUD)->AddObject(bar);
    objManager->FindLayer(LayerNames::HUD)->AddObject(outline);
    objManager->FindLayer(LayerNames::HUD)->AddObject(background);
}
