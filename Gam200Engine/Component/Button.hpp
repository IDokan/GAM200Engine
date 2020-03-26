/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Button.hpp
Author
    - jiwon.jung jjwon6218@gmail.com
Creation Date: 03.22.2020

    Header file for Button component
******************************************************************************/
#pragma once
#include <string>
#include <Component/Component.hpp>
#include "Object/Transform.hpp"
#include "Window/Application.hpp"

class Application;

class Button : public Component
{
public:
    enum class Identifier
    {
        NextScene,
        Quit,
    };
public:
    Button(Object* obj, Identifier behavior, const std::string& nextStage, const Transform& buttonTransformData);
    virtual ~Button();

    virtual void Init() override;
    virtual void Update(float dt) override;
    virtual void Clear() override;

    void Input();

private:
    Identifier id;
    std::string targetStage;
    vector2 buttonTransform;
    vector2 buttonScale;
};
