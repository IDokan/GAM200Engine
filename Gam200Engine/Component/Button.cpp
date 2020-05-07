/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Button.cpp
Author
    - jiwon.jung jjwon6218@gmail.com
Creation Date: 03.22.2020

    Source file for Button component
******************************************************************************/
#include "Component/Button.hpp"
#include "Systems/Input.hpp"
#include "Scenes/SceneManager.hpp"
#include "Object/ObjectManager.hpp"
#include "Graphics/ImGui/MyImGui.hpp"
#include <Window/Engine.hpp>

Button::Button(Object* obj, Identifier behavior, const std::string& nextStage, const Transform& buttonTransformData)
    :Component(obj), id(behavior), targetStage(nextStage)
{
    buttonTransform = buttonTransformData.GetTranslation();
    buttonScale = buttonTransformData.GetScale();
}

Button::~Button()
{
}

void Button::Init()
{
}

void Button::Update(float /*dt*/)
{
    Button::Input();
}

void Button::Clear()
{
}

void Button::Input()
{
    float mousePosX, mousePosY;
    mousePosX = input.GetMouseRelativePosition().x;
    mousePosY = input.GetMouseRelativePosition().y;

    if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        if ((mousePosX <= (buttonTransform.x + (0.5f * buttonScale.x)))
            && (mousePosX >= (buttonTransform.x - (0.5f * buttonScale.x)))
            && (mousePosY <= (buttonTransform.y + (0.5f * buttonScale.y)))
            && (mousePosY >= (buttonTransform.y - (0.5f * buttonScale.y))))
        {
            if (id == Identifier::NextScene)
            {
                SceneManager::GetSceneManager()->SetNextScene(targetStage);
            }
            else
            {
                //Add Quit features in here

            }
        }
    }
}
