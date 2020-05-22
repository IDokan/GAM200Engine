/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   OptionMenu.cpp
Author
        rtd99062@gmail.com
Creation Date: 05.11.2020

    Declaration for Option Menu
        - Declared
******************************************************************************/
#include <Object/Menu/OptionMenu.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/DepthStandard.hpp>

#include <Object/ObjectManager.hpp>
#include <Systems/Input.hpp>
#include "OptionMenu.hpp"


OptionMenu::OptionMenu()
    : unknownButton(nullptr), selectionHighlight(nullptr), currentSelection(Unknown), isTransparency(true)
{
    unknownButton = new Object();
    unknownButton->GetTransform().SetParent(&GetTransform());
    Sprite* unknownButtonSprite = new Sprite(unknownButton);
    unknownButton->AddComponent(unknownButtonSprite);
    unknownButton->SetObjectName("QuitButton");
    unknownButton->SetDepth(Depth_Standard::HUDImage);
    unknownButton->SetObjectType(ObjectType::Menu);



    selectionHighlight = new Object();
    selectionHighlight->GetTransform().SetParent(&GetTransform());
    Sprite* selectionHighlightSprite = new Sprite(selectionHighlight);
    selectionHighlight->AddComponent(selectionHighlightSprite);
    selectionHighlight->SetObjectName("Selection Highlight");
    selectionHighlight->SetDepth(Depth_Standard::HUDBackImage);
    selectionHighlight->SetObjectType(ObjectType::Menu);

    
}

OptionMenu::~OptionMenu()
{
}

MenuObject* OptionMenu::MenuUpdate(float dt)
{
    // When esc key is pressed, return to game
    if (input.IsKeyTriggered(GLFW_KEY_ESCAPE))
    {
        return nullptr;
    }

    if (input.IsKeyTriggered(GLFW_KEY_ENTER))
    {
        switch (currentSelection)
        {
        case OptionMenu::Unknown:
            return nullptr;
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
    HUDLayer->AddObjectDynamically(unknownButton);
    HUDLayer->AddObjectDynamically(selectionHighlight);
}

void OptionMenu::SetCurrentSelection(MenuEnum newValue)
{
    if (newValue > Unknown)
    {
        currentSelection = Unknown;
    }
    else if (newValue < Unknown)
    {
        currentSelection = Unknown;
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

Object* OptionMenu::GetSelectedObject()
{
    switch (currentSelection)
    {
    case OptionMenu::MenuEnum::Unknown:
        return unknownButton;
        break;
    default:
        break;
    }
    return nullptr;
}

void OptionMenu::UpdateSelectionHighlightTransformation()
{
    Object* selectedObject = GetSelectedObject();
    selectionHighlight->SetTranslation(selectedObject->GetTranslation());
    selectionHighlight->SetScale(1.2f * selectedObject->GetScale());
}

void OptionMenu::UpdateSelectionHighlightTransparency(float dt)
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
