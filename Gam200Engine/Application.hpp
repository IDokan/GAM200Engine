/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Header file for the Application.cpp
******************************************************************************/
#pragma once
#include "Window.hpp"
#include "Demo.hpp"


class Application
{
public:
    static Application* GetApplication();
    void Init();
    void Update(float dt);
    void Clear();
    void InputTest();
    void Input();
     vector2 GetWindowSize;

private:
    Application() = default;
    float fpsEllapsedTime = 0.f;
    int fpsFrames = 0;
    Window window;

	Demo demo;
};