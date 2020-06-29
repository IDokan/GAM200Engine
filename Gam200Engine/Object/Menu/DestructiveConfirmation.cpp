/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   DestructiveConfirmation.cpp
Author
        rtd99062@gmail.com
Creation Date: 06.19.2020

    Declaration for DestructiveConfirmation
******************************************************************************/
#include <Object/Menu/DestructiveConfirmation.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/DepthStandard.hpp>

#include <Object/ObjectManager.hpp>
#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>


SoundManager smInDestructiveConfirmation;
DestructiveConfirmation::DestructiveConfirmation()
    : MenuObject(), menuBackground(nullptr), sureButton(nullptr), noButton(nullptr), selectionHighlight(nullptr), currentSelection(Sure), isTransparency(true), playerPressEnter(false),
    doThis([](){})
{
    menuBackground = new Object();
    menuBackground->GetTransform().SetParent(&GetTransform());
    Sprite* menuBackgroundSprite = new Sprite(menuBackground);
    menuBackground->AddComponent(menuBackgroundSprite);
    menuBackgroundSprite->SetImage("../assets/textures/UI/DestructiveConfirmationBackground.png");
    menuBackground->SetScale(vector2{ 0.8f, 1.28f });
    menuBackground->SetObjectName("MenuBackground");
    menuBackground->SetDepth(Depth_Standard::HUDText);
    menuBackground->SetObjectType(ObjectType::Menu);

    sureTransform.SetTranslation(vector2{ 0.f, 0.1f });
    sureTransform.SetScale(buttonInitSize);
    noTransform.SetTranslation(vector2{ 0.f, -0.2f });
    noTransform.SetScale(buttonInitSize);
    sureTransform.SetParent(&GetTransform());
    noTransform.SetParent(&GetTransform());


    sureButton = new Object();
    sureButton->GetTransform().SetParent(&GetTransform());
    Sprite* sureButtonSprite = new Sprite(sureButton);
    sureButton->AddComponent(sureButtonSprite);
    sureButtonSprite->SetImage("../assets/textures/UI/Sure.png");
    sureButton->SetObjectName("ResumeButton");
    sureButton->SetDepth(Depth_Standard::HUDFrontVFX);
    sureButton->SetObjectType(ObjectType::Menu);

    noButton = new Object();
    noButton->GetTransform().SetParent(&GetTransform());
    Sprite* noButtonSprite = new Sprite(noButton);
    noButton->AddComponent(noButtonSprite);
    noButtonSprite->SetImage("../assets/textures/UI/No.png");
    noButton->SetObjectName("OptionButton");
    noButton->SetDepth(Depth_Standard::HUDFrontVFX);
    noButton->SetObjectType(ObjectType::Menu);



    selectionHighlight = new Object();
    selectionHighlight->GetTransform().SetParent(&GetTransform());
    selectionHighlight->SetObjectName("Selection Highlight");
    selectionHighlight->SetDepth(0.f);
    selectionHighlight->SetObjectType(ObjectType::Menu);

    UpdateSelectionHighlightTransformation();
    smInDestructiveConfirmation = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
}

DestructiveConfirmation::~DestructiveConfirmation()
{
}

MenuObject* DestructiveConfirmation::MenuUpdate(float dt)
{
    UpdateSelection();
    UpdateSelectionHighlightTransparency(dt);

    // When esc key is pressed, return to game
    if (input.IsKeyTriggered(GLFW_KEY_ESCAPE))
    {
        smInDestructiveConfirmation.Play_Sound(UNDO_SOUND);
        return nullptr;
    }

    if (input.IsKeyPressed(GLFW_KEY_ENTER))
    {
        GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(0.3f));
        playerPressEnter = true;
    }
    else if (playerPressEnter)
    {
        playerPressEnter = false;
        GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(1.f));
        smInDestructiveConfirmation.Play_Sound(BUTTON_TRIGGERED_SOUND);
        switch (currentSelection)
        {
        case DestructiveConfirmation::Sure:
            doThis();
            break;
        case DestructiveConfirmation::No:
            return nullptr;
            break;
        default:
            break;
        }
    }
    return this;
}

void DestructiveConfirmation::AddChildObjectsDynamically()
{
    Layer* HUDLayer = ObjectManager::GetObjectManager()->FindLayer(HUD);
    HUDLayer->AddObjectDynamically(menuBackground);
    HUDLayer->AddObjectDynamically(sureButton);
    HUDLayer->AddObjectDynamically(noButton);
    HUDLayer->AddObjectDynamically(selectionHighlight);
}

void DestructiveConfirmation::CleanChildObjects()
{
    menuBackground->SetDead(true);
    sureButton->SetDead(true);
    noButton->SetDead(true);
    selectionHighlight->SetDead(true);
}

void DestructiveConfirmation::LerpIn(float timer)
{
    SetScale(EaseOutBounce(timer));
}

void DestructiveConfirmation::LerpOut(float timer)
{
    float scaler = 1.f - EaseOutBounce(timer);

    if (scaler < 0.f)
    {
        scaler = 0.f;
    }

    SetScale(scaler);
}

void DestructiveConfirmation::SetDoThis(std::function<void(void)> newDoThis)
{
    doThis = newDoThis;
}

void DestructiveConfirmation::SetCurrentSelection(MenuEnum newValue)
{
    if (newValue > No)
    {
        currentSelection = Sure;
    }
    else if (newValue < Sure)
    {
        currentSelection = No;
    }
    else
    {
        currentSelection = newValue;
    }
}

void DestructiveConfirmation::UpdateSelection() noexcept
{
    if (input.IsKeyTriggered(GLFW_KEY_DOWN))
    {
        smInDestructiveConfirmation.Play_Sound(CURSOR_MOVEMENT_SOUND);
        SetCurrentSelection(static_cast<MenuEnum>(currentSelection + 1));
    }
    else if (input.IsKeyTriggered(GLFW_KEY_UP))
    {
        smInDestructiveConfirmation.Play_Sound(CURSOR_MOVEMENT_SOUND);
        SetCurrentSelection(static_cast<MenuEnum>(currentSelection - 1));
    }
    else
    {
        return;
    }

    UpdateSelectionHighlightTransformation();
}

Object* DestructiveConfirmation::GetSelectedObject()
{
    switch (currentSelection)
    {
    case DestructiveConfirmation::MenuEnum::Sure:
        return sureButton;
        break;
    case DestructiveConfirmation::MenuEnum::No:
        return noButton;
        break;
    default:
        break;
    }
    return nullptr;
}

void DestructiveConfirmation::UpdateSelectionHighlightTransformation()
{
    sureButton->GetTransform().SetParent(&sureTransform);
    noButton->GetTransform().SetParent(&noTransform);

    Object* selectedObject = GetSelectedObject();
    selectionHighlight->GetTransform().SetParent(selectedObject->GetTransform().GetParent());
    selectedObject->GetTransform().SetParent(&selectionHighlight->GetTransform());
}

void DestructiveConfirmation::UpdateSelectionHighlightTransparency(float dt)
{
    // When a flag is on, decrease as mush as given dt
    if (isTransparency)
    {
        vector2 highlightSize = selectionHighlight->GetScale();
        selectionHighlight->SetScale(highlightSize.x + (dt / 2.f));

        // if the alpha value is smaller than minimum capacity
        if (highlightSize.x > 1.2f)
        {
            selectionHighlight->SetScale(1.2f);
            isTransparency = !isTransparency;
        }
    }
    // and increase when the flag is off 
    else
    {
        vector2 highlightSize = selectionHighlight->GetScale();
        selectionHighlight->SetScale(highlightSize.x - (dt / 2.f));

        // if the alpha value is bigger than maximum capacity
        if (highlightSize.x < 1.f)
        {
            selectionHighlight->SetScale(1.f);
            isTransparency = !isTransparency;
        }
    }
}

float DestructiveConfirmation::EaseInBounce(float timer)
{
    return 1.f - EaseOutBounce(1.f - timer);
}

float DestructiveConfirmation::EaseOutBounce(float timer)
{
    const float n1 = 7.5625f;
    const float d1 = 2.75f;

    if (timer < (1.f / d1))
    {
        return n1 * timer * timer;
    }
    else if (timer < (2.f / d1))
    {
        return n1 * (timer -= 1.5f / d1) * timer + 0.75f;
    }
    else if (timer < (2.5f / d1))
    {
        return n1 * (timer -= 2.25f / d1) * timer + 0.9375f;
    }
    else
    {
        return n1 * (timer -= 2.625f / d1) * timer + 0.984375f;
    }
}
