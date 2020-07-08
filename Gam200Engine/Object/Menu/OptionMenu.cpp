/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   OptionMenu.cpp
Author
        rtd99062@gmail.com
Creation Date: 06.20.2020

    Declaration for Option Menu
******************************************************************************/
#include <Object/Menu/OptionMenu.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Component/Sprite/Animation.hpp>
#include <Object/DepthStandard.hpp>

#include <Object/ObjectManager.hpp>
#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>

#include <Object/Menu/DestructiveConfirmation.hpp>

OptionMenu::OptionMenu()
    : MenuObject(), menuBackground(nullptr), volumeButton(nullptr), screenToggleButton(nullptr), selectionHighlight(nullptr), currentSelection(Volume), isTransparency(true), playerPressEnter(false)
{
    menuBackground = new Object();
    menuBackground->GetTransform().SetParent(&GetTransform());
    Sprite* menuBackgroundSprite = new Sprite(menuBackground);
    menuBackground->AddComponent(menuBackgroundSprite);
    menuBackgroundSprite->SetImage("../assets/textures/UI/OptionBackground.png");
    menuBackground->SetScale(vector2{ 1.f, 1.8f });
    menuBackground->SetObjectName("OptionBackground");
    menuBackground->SetDepth(Depth_Standard::HUDText);
    menuBackground->SetObjectType(ObjectType::Menu);

    volumeTransform.SetTranslation(vector2{ 0.f, 0.2f });
    volumeTransform.SetScale(vector2{0.2825f, 0.2335f});
    screenToggleTransform.SetTranslation(vector2{ 0.f, -0.1f });
    screenToggleTransform.SetScale(buttonInitSize);
    volumeTransform.SetParent(&GetTransform());
    screenToggleTransform.SetParent(&GetTransform());


    volumeButton = new Object();
    volumeButton->GetTransform().SetParent(&GetTransform());
    Animation* volumeButtonSprite = new Animation(volumeButton);
    volumeButton->AddComponent(volumeButtonSprite);
    volumeButtonSprite->SetImage("../assets/textures/UI/Volume.png");
    volumeButtonSprite->SetNumOfState(5);
    volumeButtonSprite->SetSpeed(0.f);
    volumeButtonSprite->SetState(2);
    volumeButton->SetObjectName("VolumeButton");
    volumeButton->SetDepth(Depth_Standard::HUDFrontVFX);
    volumeButton->SetObjectType(ObjectType::Menu);

    screenToggleButton = new Object();
    screenToggleButton->GetTransform().SetParent(&GetTransform());
    Animation* screenToggleButtonSprite = new Animation(screenToggleButton);
    screenToggleButtonSprite->SetNumOfState(2);
    screenToggleButtonSprite->SetSpeed(0.f);
    screenToggleButtonSprite->SetState(0);
    screenToggleButton->AddComponent(screenToggleButtonSprite);
    screenToggleButtonSprite->SetImage("../assets/textures/UI/ScreenToggle.png");
    screenToggleButton->SetObjectName("ScreenToggleButton");
    screenToggleButton->SetDepth(Depth_Standard::HUDFrontVFX);
    screenToggleButton->SetObjectType(ObjectType::Menu);



    selectionHighlight = new Object();
    selectionHighlight->GetTransform().SetParent(&GetTransform());
    selectionHighlight->SetObjectName("Selection Highlight");
    selectionHighlight->SetDepth(0.f);
    selectionHighlight->SetObjectType(ObjectType::Menu);

    UpdateSelectionHighlightTransformation();
}

OptionMenu::~OptionMenu()
{
}

MenuObject* OptionMenu::MenuUpdate(float dt)
{
    UpdateSelection();
    UpdateSelectionHighlightTransparency(dt);

    // When esc key is pressed, return to game
    if (input.IsKeyTriggered(GLFW_KEY_ESCAPE))
    {
        SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolumeOnMenu();
        SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(UNDO_SOUND);
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
        SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(BUTTON_TRIGGERED_SOUND);

        Animation* volumeAnimation = volumeButton->GetComponentByTemplate<Animation>();
        Animation* animation = screenToggleButton->GetComponentByTemplate<Animation>();

        switch (currentSelection)
        {
        case OptionMenu::Volume:
            volumeAnimation->SetState((volumeAnimation->GetState() + 1) % volumeAnimation->GetNumOfState());
            if (volumeAnimation->GetState() == 0)
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().MASTER_VOLUME_DOWN();
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().MASTER_VOLUME_DOWN();
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().MASTER_VOLUME_DOWN();
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().MASTER_VOLUME_DOWN();
            }
            else
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().MASTER_VOLUME_UP();
            }
            break;
        case OptionMenu::ScreenToggle:
            input.SetShouldToggleWindow(true);
            animation->SetState((animation->GetState() + 1) % 2);
            break;
        default:
            break;
        }
    }
    return this;
}

void OptionMenu::AddChildObjectsDynamically()
{
    Layer* HUDLayer = ObjectManager::GetObjectManager()->FindLayer(HUD);
    HUDLayer->AddObjectDynamically(menuBackground);
    HUDLayer->AddObjectDynamically(volumeButton);
    HUDLayer->AddObjectDynamically(screenToggleButton);
    HUDLayer->AddObjectDynamically(selectionHighlight);
}

void OptionMenu::CleanChildObjects()
{
    menuBackground->SetDead(true);
    volumeButton->SetDead(true);
    screenToggleButton->SetDead(true);
    selectionHighlight->SetDead(true);
}

void OptionMenu::LerpIn(float timer)
{
    SetScale(EaseOutBounce(timer));
}

void OptionMenu::LerpOut(float timer)
{
    float scaler = 1.f - EaseOutBounce(timer);

    if (scaler < 0.f)
    {
        scaler = 0.f;
    }

    SetScale(scaler);
}

void OptionMenu::SetCurrentSelection(MenuEnum newValue)
{
    if (newValue > ScreenToggle)
    {
        currentSelection = Volume;
    }
    else if (newValue < Volume)
    {
        currentSelection = ScreenToggle;
    }
    else
    {
        currentSelection = newValue;
    }
}

void OptionMenu::UpdateSelection() noexcept
{
    if (input.IsKeyTriggered(GLFW_KEY_DOWN))
    {
        SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(CURSOR_MOVEMENT_SOUND);
        SetCurrentSelection(static_cast<MenuEnum>(currentSelection + 1));
    }
    else if (input.IsKeyTriggered(GLFW_KEY_UP))
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

Object* OptionMenu::GetSelectedObject()
{
    switch (currentSelection)
    {
    case OptionMenu::MenuEnum::Volume:
        return volumeButton;
        break;
    case OptionMenu::MenuEnum::ScreenToggle:
        return screenToggleButton;
        break;
    default:
        break;
    }
    return nullptr;
}

void OptionMenu::UpdateSelectionHighlightTransformation()
{
    volumeButton->GetTransform().SetParent(&volumeTransform);
    screenToggleButton->GetTransform().SetParent(&screenToggleTransform);

    Object* selectedObject = GetSelectedObject();
    selectionHighlight->GetTransform().SetParent(selectedObject->GetTransform().GetParent());
    selectedObject->GetTransform().SetParent(&selectionHighlight->GetTransform());
}

void OptionMenu::UpdateSelectionHighlightTransparency(float dt)
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

float OptionMenu::EaseInBounce(float timer)
{
    return 1.f - EaseOutBounce(1.f - timer);
}

float OptionMenu::EaseOutBounce(float timer)
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
