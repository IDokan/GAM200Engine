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
#include <Object/Menu/BaseMenu.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/DepthStandard.hpp>

#include <Object/ObjectManager.hpp>
#include <Systems/Input.hpp>

BaseMenu::BaseMenu()
    : MenuObject(), menuBackground(nullptr), resumeButton(nullptr), optionButton(nullptr), quitButton(nullptr), selectionHighlight(nullptr), currentSelection(Resume), isTransparency(true)
{
    menuBackground = new Object();
    menuBackground->GetTransform().SetParent(&GetTransform());
    Sprite* menuBackgroundSprite = new Sprite(menuBackground);
    menuBackground->AddComponent(menuBackgroundSprite);
    menuBackgroundSprite->SetColor(Graphics::Color4f{ 0.5f });
    menuBackground->SetScale(vector2{ 1.f, 1.5f });
    menuBackground->SetObjectName("MenuBackground");
    menuBackground->SetDepth(Depth_Standard::HUDBackground);
    menuBackground->SetObjectType(ObjectType::Menu);


    resumeButton = new Object();
    resumeButton->SetTranslation(vector2{ 0.f, 0.1f });
    resumeButton->SetScale(vector2{ 0.5f, 0.2f });
    resumeButton->GetTransform().SetParent(&GetTransform());
    Sprite* resumeButtonSprite = new Sprite(resumeButton);
    resumeButton->AddComponent(resumeButtonSprite);
    resumeButtonSprite->SetColor(Graphics::Color4f{ 0.f, 0.5f, 1.f });
    resumeButton->SetObjectName("ResumeButton");
    resumeButton->SetDepth(Depth_Standard::HUDImage);
    resumeButton->SetObjectType(ObjectType::Menu);

    optionButton = new Object();
    optionButton->SetTranslation(vector2{ 0.f, -0.2f });
    optionButton->SetScale(vector2{ 0.5f, 0.2f });
    optionButton->GetTransform().SetParent(&GetTransform());
    Sprite* optionButtonSprite = new Sprite(optionButton);
    optionButton->AddComponent(optionButtonSprite);
    optionButtonSprite->SetColor(Graphics::Color4f{ 1.f, 0.f, 1.f });
    optionButton->SetObjectName("OptionButton");
    optionButton->SetDepth(Depth_Standard::HUDImage);
    optionButton->SetObjectType(ObjectType::Menu);

    quitButton = new Object();
    quitButton->SetTranslation(vector2{ 0.f, -0.5f });
    quitButton->SetScale(vector2{ 0.5f, 0.2f });
    quitButton->GetTransform().SetParent(&GetTransform());
    Sprite* quitButtonSprite = new Sprite(quitButton);
    quitButton->AddComponent(quitButtonSprite);
    quitButtonSprite->SetColor(Graphics::Color4f{ 1.f, 1.f, 0.f });
    quitButton->SetObjectName("QuitButton");
    quitButton->SetDepth(Depth_Standard::HUDImage);
    quitButton->SetObjectType(ObjectType::Menu);



    selectionHighlight = new Object();
    selectionHighlight->GetTransform().SetParent(&GetTransform());
    Sprite* selectionHighlightSprite = new Sprite(selectionHighlight);
    selectionHighlight->AddComponent(selectionHighlightSprite);
    selectionHighlight->SetObjectName("Selection Highlight");
    selectionHighlight->SetDepth(Depth_Standard::HUDBackImage);
    selectionHighlight->SetObjectType(ObjectType::Menu);
    UpdateSelectionHighlightTransformation();

    
}

BaseMenu::~BaseMenu()
{
}

MenuObject* BaseMenu::MenuUpdate(float dt)
{
    UpdateSelection();
    UpdateSelectionHighlightTransparency(dt);

    // When esc key is pressed, return to game
    if (input.IsKeyTriggered(GLFW_KEY_ESCAPE))
    {
        return nullptr;
    }

    if (input.IsKeyTriggered(GLFW_KEY_ENTER))
    {
        GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(0.3f));
        switch (currentSelection)
        {
        case BaseMenu::Resume:
            return nullptr;
            break;
        case BaseMenu::Option:
            // return ptr to OptionMenu
            break;
        case BaseMenu::Quit:
            input.SetIsRunning(false);
            break;
        default:
            break;
        }
    }
    return this;
}

void BaseMenu::AddChildObjectsDynamically()
{
    Layer* HUDLayer = ObjectManager::GetObjectManager()->FindLayer(HUD);
    HUDLayer->AddObjectDynamically(menuBackground);
    HUDLayer->AddObjectDynamically(resumeButton);
    HUDLayer->AddObjectDynamically(optionButton);
    HUDLayer->AddObjectDynamically(quitButton);
    HUDLayer->AddObjectDynamically(selectionHighlight);
}

void BaseMenu::CleanChildObjects()
{
    menuBackground->SetDead(true);
    resumeButton->SetDead(true);
    optionButton->SetDead(true);
    quitButton->SetDead(true);
    selectionHighlight->SetDead(true);
}

void BaseMenu::SetCurrentSelection(MenuEnum newValue)
{
    if (newValue > Quit)
    {
        currentSelection = Resume;
    }
    else if (newValue < Resume)
    {
        currentSelection = Quit;
    }
    else
    {
        currentSelection = newValue;
    }
}

void BaseMenu::UpdateSelection() noexcept
{
    if (input.IsKeyTriggered(GLFW_KEY_DOWN))
    {
        SetCurrentSelection(static_cast<MenuEnum>(currentSelection + 1));
    }
    else if (input.IsKeyTriggered(GLFW_KEY_UP))
    {
        SetCurrentSelection(static_cast<MenuEnum>(currentSelection - 1));
    }
    else
    {
        return;
    }

    UpdateSelectionHighlightTransformation();
}

Object* BaseMenu::GetSelectedObject()
{
    switch (currentSelection)
    {
    case BaseMenu::MenuEnum::Resume:
        return resumeButton;
        break;
    case BaseMenu::MenuEnum::Option:
        return optionButton;
        break;
    case BaseMenu::MenuEnum::Quit:
        return quitButton;
        break;
    default:
        break;
    }
    return nullptr;
}

void BaseMenu::UpdateSelectionHighlightTransformation()
{
    Object* selectedObject = GetSelectedObject();
    selectionHighlight->SetTranslation(selectedObject->GetTranslation());
    selectionHighlight->SetScale(1.2f * selectedObject->GetScale());
}

void BaseMenu::UpdateSelectionHighlightTransparency(float dt)
{
    Sprite* selectionSprite = selectionHighlight->GetComponentByTemplate<Sprite>();
    Graphics::Color4f color = selectionSprite->GetColor();

    // When a flag is on, decrease as mush as given dt
    if (isTransparency)
    {
        color.alpha = color.alpha - dt;

        // if the alpha value is smaller than minimum capacity
        if (color.alpha < 0.f)
        {
            color.alpha = 0.f;
            isTransparency = !isTransparency;
        }
    }
    // and increase when the flag is off 
    else
    {
        color.alpha = color.alpha + dt;

        // if the alpha value is bigger than maximum capacity
        if (color.alpha > 1.f)
        {
            color.alpha = 1.f;
            isTransparency = !isTransparency;
        }
    }
    selectionSprite->SetColor(color);
}
