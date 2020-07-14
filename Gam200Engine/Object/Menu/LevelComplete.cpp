/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   LevelComplete.cpp
Author
        rtd99062@gmail.com
Creation Date: 07.13.2020

    Source file for the Level Complete Menu
******************************************************************************/
#include <Object/Menu/LevelComplete.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Component/Sprite/Animation.hpp>
#include <Object/DepthStandard.hpp>

#include <Object/ObjectManager.hpp>
#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>

#include <Object/Menu/DestructiveConfirmation.hpp>
#include <Object/Particles/ParticleEmitter.hpp>

LevelComplete::LevelComplete()
    : MenuObject(), menuBackground(nullptr), goNextButton(nullptr), goMainMenuButton(nullptr), selectionHighlight(nullptr), confetti(nullptr), currentSelection(Go2NextLevel), isTransparency(true), playerPressEnter(false)
{
    menuBackground = new Object();
    menuBackground->GetTransform().SetParent(&GetTransform());
    Sprite* menuBackgroundSprite = new Sprite(menuBackground);
    menuBackground->AddComponent(menuBackgroundSprite);
    menuBackgroundSprite->SetImage("../assets/textures/UI/LevelClearBackground.png");
    menuBackground->SetScale(vector2{ 1.f, 1.6f });
    menuBackground->SetObjectName("Level Complete Background");
    menuBackground->SetDepth(Depth_Standard::HUDBackground);
    menuBackground->SetObjectType(ObjectType::Menu);

    nextTransform.SetTranslation(vector2{ 0.f });
    nextTransform.SetScale(buttonInitSize);
    mainMenuTransform.SetTranslation(vector2{ 0.f, -0.4f });
    mainMenuTransform.SetScale(buttonInitSize);
    nextTransform.SetParent(&GetTransform());
    mainMenuTransform.SetParent(&GetTransform());


    goNextButton = new Object();
    goNextButton->GetTransform().SetParent(&GetTransform());
    Sprite* goNextSprite = new Sprite(goNextButton);
    goNextButton->AddComponent(goNextSprite);
    goNextSprite->SetImage("../assets/textures/UI/NextLevel.png");
    goNextButton->SetObjectName("NextLevel");
    goNextButton->SetDepth(Depth_Standard::HUDImage);
    goNextButton->SetObjectType(ObjectType::Menu);

    goMainMenuButton = new Object();
    goMainMenuButton->GetTransform().SetParent(&GetTransform());
    Sprite* goMainMenuButtonSprite = new Sprite(goMainMenuButton);
    goMainMenuButton->AddComponent(goMainMenuButtonSprite);
    goMainMenuButtonSprite->SetImage("../assets/textures/UI/MainMenu.png");
    goMainMenuButton->SetObjectName("MainMenu");
    goMainMenuButton->SetDepth(Depth_Standard::HUDImage);
    goMainMenuButton->SetObjectType(ObjectType::Menu);

    confetti = new ParticleEmitter(15.f, 80.f, 100, [&]() ->Particle::ParticleObject
        {
            Graphics::Color4f colors[3];
            colors[0] = Graphics::Color4f(1.f, 0.f, 0.f);
            colors[1] = Graphics::Color4f(0.f, 1.f, 0.f);
            colors[2] = Graphics::Color4f(0.f, 0.f, 1.f);
            float startX = (static_cast<float>(rand() % 250) - 125) / 125.f;
            Particle::ParticleObject p;
            p.transform.SetScale(vector2{ 0.025f, 0.025f });
            p.transform.SetTranslation(vector2{ startX, 1.f });
            float rotation = static_cast<float>(rand() % 314) / 100.f;
            p.transform.SetRotation(rotation);
            p.transform.SetDepth(Depth_Standard::HUD);
            p.life = 1.f;
            p.color = colors[rand() % 3];
            p.velocity = vector2{ 0.f, -2.5f };

            return p;
        },
        [&](Particle::ParticleObject& p, float dt)
        {
            p.transform.SetTranslation(p.transform.GetTranslation() + (dt * p.velocity));
        }
        );
    confetti->SetObjectName("Confetti Emitter");
    confetti->SetShouldReviveParticle(false);
    confetti->SetParticleImage("../assets/textures/circle.png");
    confetti->SetDepth(Depth_Standard::HUDFrontVFX);


    selectionHighlight = new Object();
    selectionHighlight->GetTransform().SetParent(&GetTransform());
    selectionHighlight->SetObjectName("Selection Highlight");
    selectionHighlight->SetDepth(0.f);
    selectionHighlight->SetObjectType(ObjectType::Menu);

    UpdateSelectionHighlightTransformation();
}

LevelComplete::~LevelComplete()
{
}

MenuObject* LevelComplete::MenuUpdate(float dt)
{
    confetti->SetShouldReviveParticle(true);

    UpdateSelection();
    UpdateSelectionHighlightTransparency(dt);

    if (input.IsKeyPressed(GLFW_KEY_ENTER) || input.IsKeyTriggered(GLFW_KEY_SPACE))
    {
        GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(0.3f));
        playerPressEnter = true;
    }
    else if (playerPressEnter)
    {
        playerPressEnter = false;
        GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(1.f));
        SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(SELECT_SOUND);

        switch (currentSelection)
        {
        case LevelComplete::Go2NextLevel:
            SceneManager::GetSceneManager()->SetNextScene(SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneStateManager()->GetNameOfSelectedLevel());
            break;
        case LevelComplete::Back2Main:
            dynamic_cast<DestructiveConfirmation*>(PauseAndMenu::Get()->confirmMenu)->SetDoThis([&]()
                {
                    SceneManager::GetSceneManager()->SetNextScene("MenuScene");
                });
            return PauseAndMenu::Get()->confirmMenu;
            break;
        default:
            break;
        }
    }
    return this;
}

void LevelComplete::AddChildObjectsDynamically()
{
    Layer* HUDLayer = ObjectManager::GetObjectManager()->FindLayer(HUD);
    HUDLayer->AddObjectDynamically(menuBackground);
    HUDLayer->AddObjectDynamically(goNextButton);
    HUDLayer->AddObjectDynamically(goMainMenuButton);
    HUDLayer->AddObjectDynamically(confetti);
    HUDLayer->AddObjectDynamically(selectionHighlight);
}

void LevelComplete::CleanChildObjects()
{
    menuBackground->SetDead(true);
    goNextButton->SetDead(true);
    goMainMenuButton->SetDead(true);
    confetti->SetDead(true);
    selectionHighlight->SetDead(true);
}

void LevelComplete::LerpIn(float timer)
{
    SetScale(EaseOutBounce(timer));
}

void LevelComplete::LerpOut(float timer)
{
    float scaler = 1.f - EaseOutBounce(timer);

    if (scaler < 0.f)
    {
        scaler = 0.f;
    }

    SetScale(scaler);
}

void LevelComplete::SetCurrentSelection(MenuEnum newValue)
{
    if (newValue > Back2Main)
    {
        currentSelection = Go2NextLevel;
    }
    else if (newValue < Go2NextLevel)
    {
        currentSelection = Back2Main;
    }
    else
    {
        currentSelection = newValue;
    }
}

void LevelComplete::UpdateSelection() noexcept
{
    if (input.IsKeyTriggered(GLFW_KEY_DOWN) || input.IsKeyTriggered(GLFW_KEY_S))
    {
        SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(CURSOR_MOVEMENT_SOUND);
        SetCurrentSelection(static_cast<MenuEnum>(currentSelection + 1));
    }
    else if (input.IsKeyTriggered(GLFW_KEY_UP) || input.IsKeyTriggered(GLFW_KEY_W))
    {
        SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(CURSOR_MOVEMENT_SOUND);
        SetCurrentSelection(static_cast<MenuEnum>(currentSelection - 1));
    }
    else
    {
        return;
    }

    UpdateSelectionHighlightTransformation();
}

Object* LevelComplete::GetSelectedObject()
{
    switch (currentSelection)
    {
    case LevelComplete::MenuEnum::Go2NextLevel:
        return goNextButton;
        break;
    case LevelComplete::MenuEnum::Back2Main:
        return goMainMenuButton;
        break;
    default:
        break;
    }
    return nullptr;
}

void LevelComplete::UpdateSelectionHighlightTransformation()
{
    goNextButton->GetTransform().SetParent(&nextTransform);
    goMainMenuButton->GetTransform().SetParent(&mainMenuTransform);

    Object* selectedObject = GetSelectedObject();
    selectionHighlight->GetTransform().SetParent(selectedObject->GetTransform().GetParent());
    selectedObject->GetTransform().SetParent(&selectionHighlight->GetTransform());
}

void LevelComplete::UpdateSelectionHighlightTransparency(float dt)
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

float LevelComplete::EaseInBounce(float timer)
{
    return 1.f - EaseOutBounce(1.f - timer);
}

float LevelComplete::EaseOutBounce(float timer)
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