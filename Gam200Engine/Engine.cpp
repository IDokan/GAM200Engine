/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Engine.cpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Source file for running program
******************************************************************************/
#include "Engine.hpp"
#include "Application.hpp"
#include "Input.hpp"
#include <iostream>

Application* app_ = nullptr;

void Engine::Init()
{
    app_ = Application::GetApplication();
    app_->Init();
    timer.Reset();
    isRunning = false;
}

void Engine::Update()
{
    if (input.IsKeyTriggered(GLFW_KEY_ESCAPE))
    {
        app_->GetApplication()->Clear();
        isRunning = true;
    }
    dt = static_cast<float>(timer.GetElapsedSeconds());
    timer.Reset();
    app_->Update(dt);
}

void Engine::Clear()
{
}
