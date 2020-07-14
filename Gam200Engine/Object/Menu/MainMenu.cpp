/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MenuObject.hpp
Author
        rtd99062@gmail.com
Creation Date: 05.11.2020

    Declaration for Base Menu
        - Resume
        - Option
        - Quit
******************************************************************************/
#include <Object/Menu/MainMenu.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/DepthStandard.hpp>

#include <Object/ObjectManager.hpp>
#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>
#include <Systems/FileIO.hpp>

#include <Object/Menu/DestructiveConfirmation.hpp>

MainMenu::MainMenu()
    : MenuObject(), newButton(nullptr), loadButton(nullptr), howToPlayButton(nullptr), optionButton(nullptr), creditButton(nullptr), quitButton(nullptr), selectionHighlight(nullptr), currentSelection(NEWGAME), isTransparency(true), playerPressEnter(false)
{
    newTransform.SetTranslation(vector2{ 0.f, 0.4f });
    newTransform.SetScale(buttonInitSize);
    loadTransform.SetTranslation(vector2{ 0.f, 0.2f });
    loadTransform.SetScale(buttonInitSize);
    howToPlayTransform.SetTranslation(vector2{ 0.f, 0.f });
    howToPlayTransform.SetScale(buttonInitSize);
    optionTransform.SetTranslation(vector2{ 0.f, -0.2f });
    optionTransform.SetScale(buttonInitSize);
    creditTransform.SetTranslation(vector2{ 0.f, -0.4f });
    creditTransform.SetScale(buttonInitSize);
    quitTransform.SetTranslation(vector2{ 0.f, -0.6f });
    quitTransform.SetScale(buttonInitSize);
    newTransform.SetParent(&GetTransform());
    loadTransform.SetParent(&GetTransform());
    howToPlayTransform.SetParent(&GetTransform());
    optionTransform.SetParent(&GetTransform());
    creditTransform.SetParent(&GetTransform());
    quitTransform.SetParent(&GetTransform());

    newButton = new Object();
    newButton->GetTransform().SetParent(&GetTransform());
    Sprite* newButtonSprite = new Sprite(newButton);
    newButton->AddComponent(newButtonSprite);
    newButtonSprite->SetImage("../assets/textures/UI/NewGame.png");
    newButton->SetObjectName("NewButton");
    newButton->SetDepth(Depth_Standard::HUDImage);
    newButton->SetObjectType(ObjectType::Menu);

    loadButton = new Object();
    loadButton->GetTransform().SetParent(&GetTransform());
    Sprite* loadButtonSprite = new Sprite(loadButton);
    loadButton->AddComponent(loadButtonSprite);
    loadButtonSprite->SetImage("../assets/textures/UI/LoadGame.png");
    loadButton->SetObjectName("LoadButton");
    loadButton->SetDepth(Depth_Standard::HUDImage);
    loadButton->SetObjectType(ObjectType::Menu);

    howToPlayButton = new Object();
    howToPlayButton->GetTransform().SetParent(&GetTransform());
    Sprite* howToPlayButtonSprite = new Sprite(howToPlayButton);
    howToPlayButton->AddComponent(howToPlayButtonSprite);
    howToPlayButtonSprite->SetImage("../assets/textures/UI/HowToPlay.png");
    howToPlayButton->SetObjectName("HowToPlayButton");
    howToPlayButton->SetDepth(Depth_Standard::HUDImage);
    howToPlayButton->SetObjectType(ObjectType::Menu);

    optionButton = new Object();
    optionButton->GetTransform().SetParent(&GetTransform());
    Sprite* optionButtonSprite = new Sprite(optionButton);
    optionButton->AddComponent(optionButtonSprite);
    optionButtonSprite->SetImage("../assets/textures/UI/Option.png");
    optionButton->SetObjectName("OptionButton");
    optionButton->SetDepth(Depth_Standard::HUDImage);
    optionButton->SetObjectType(ObjectType::Menu);

    creditButton = new Object();
    creditButton->GetTransform().SetParent(&GetTransform());
    Sprite* creditButtonSprite = new Sprite(creditButton);
    creditButton->AddComponent(creditButtonSprite);
    creditButtonSprite->SetImage("../assets/textures/UI/Credit.png");
    creditButton->SetObjectName("CreditButton");
    creditButton->SetDepth(Depth_Standard::HUDImage);
    creditButton->SetObjectType(ObjectType::Menu);

    quitButton = new Object();
    quitButton->GetTransform().SetParent(&GetTransform());
    Sprite* quitButtonSprite = new Sprite(quitButton);
    quitButton->AddComponent(quitButtonSprite);
    quitButtonSprite->SetImage("../assets/textures/UI/Quit.png");
    quitButton->SetObjectName("ExitButton");
    quitButton->SetDepth(Depth_Standard::HUDImage);
    quitButton->SetObjectType(ObjectType::Menu);

    selectionHighlight = new Object();
    selectionHighlight->GetTransform().SetParent(&GetTransform());
    selectionHighlight->SetObjectName("Selection Highlight");
    selectionHighlight->SetDepth(0.f);
    selectionHighlight->SetObjectType(ObjectType::Menu);

    UpdateSelectionHighlightTransformation();
}

MainMenu::~MainMenu()
{
}

MenuObject* MainMenu::MenuUpdate(float dt)
{
    UpdateSelection();
    UpdateSelectionHighlightTransparency(dt);

    if (input.IsKeyPressed(GLFW_KEY_ENTER))
    {
        GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(0.3f));
        playerPressEnter = true;
    }
    else if (playerPressEnter)
    {
        playerPressEnter = false;
        GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(1.f));
        SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(SOUNDS::SELECT_SOUND);
        fileIO* loadGame = nullptr;
        switch (currentSelection)
        {
        case MainMenu::NEWGAME:
            SceneManager::GetSceneManager()->SetNextScene("AlphaTutorialLevel1");
            break;
        case MainMenu::LOADGAME:
            loadGame = new fileIO;
            loadGame->LoadGame();
            delete loadGame;
            break;
        case MainMenu::HOWTOPLAY:
            SceneManager::GetSceneManager()->SetNextScene("HowToPlay");
            break;
        case MainMenu::OPTION:
            return PauseAndMenu::Get()->optionMenu;
            break;
        case MainMenu::CREDIT:
            SceneManager::GetSceneManager()->SetNextScene("Credit");
            break;
        case MainMenu::QUIT:
            dynamic_cast<DestructiveConfirmation*>(PauseAndMenu::Get()->confirmMenu)->SetDoThis([&]()
                {
                    input.SetIsRunning(false);
                });
            return PauseAndMenu::Get()->confirmMenu;
            break;
        default:
            break;
        }
    }
    return this;
}

void MainMenu::AddChildObjectsDynamically()
{
    Layer* HUDLayer = ObjectManager::GetObjectManager()->FindLayer(HUD);
    HUDLayer->AddObjectDynamically(newButton);
    HUDLayer->AddObjectDynamically(loadButton);
    HUDLayer->AddObjectDynamically(howToPlayButton);
    HUDLayer->AddObjectDynamically(optionButton);
    HUDLayer->AddObjectDynamically(creditButton);
    HUDLayer->AddObjectDynamically(quitButton);
    HUDLayer->AddObjectDynamically(selectionHighlight);
}

void MainMenu::CleanChildObjects()
{
    newButton->SetDead(true);
    loadButton->SetDead(true);
    howToPlayButton->SetDead(true);
    optionButton->SetDead(true);
    creditButton->SetDead(true);
    quitButton->SetDead(true);
    selectionHighlight->SetDead(true);
}

void MainMenu::LerpIn(float timer)
{
    SetScale(1.f);
}

void MainMenu::LerpOut(float timer)
{
    SetScale(0.f);
}

void MainMenu::SetCurrentSelection(MenuEnum newValue)
{
    if (newValue > QUIT)
    {
        currentSelection = NEWGAME;
    }
    else if (newValue < NEWGAME)
    {
        currentSelection = QUIT;
    }
    else
    {
        currentSelection = newValue;
    }
}

void MainMenu::UpdateSelection() noexcept
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

Object* MainMenu::GetSelectedObject()
{
    switch (currentSelection)
    {
    case MainMenu::MenuEnum::NEWGAME:
        return newButton;
        break;
    case MainMenu::MenuEnum::LOADGAME:
        return loadButton;
        break;
    case MainMenu::MenuEnum::HOWTOPLAY:
        return howToPlayButton;
        break;
    case MainMenu::MenuEnum::OPTION:
        return optionButton;
        break;
    case MainMenu::MenuEnum::CREDIT:
        return creditButton;
        break;
    case MainMenu::MenuEnum::QUIT:
        return quitButton;
        break;
    default:
        break;
    }
    return nullptr;
}

void MainMenu::UpdateSelectionHighlightTransformation()
{
    newButton->GetTransform().SetParent(&newTransform);
    loadButton->GetTransform().SetParent(&loadTransform);
    howToPlayButton->GetTransform().SetParent(&howToPlayTransform);
    optionButton->GetTransform().SetParent(&optionTransform);
    creditButton->GetTransform().SetParent(&creditTransform);
    quitButton->GetTransform().SetParent(&quitTransform);

    Object* selectedObject = GetSelectedObject();
    selectionHighlight->GetTransform().SetParent(selectedObject->GetTransform().GetParent());
    selectedObject->GetTransform().SetParent(&selectionHighlight->GetTransform());
}

void MainMenu::UpdateSelectionHighlightTransparency(float dt)
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

float MainMenu::EaseInBounce(float timer)
{
    return 1.f - EaseOutBounce(1.f - timer);
}

float MainMenu::EaseOutBounce(float timer)
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
