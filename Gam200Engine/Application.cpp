/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.cpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Source file for the make window
******************************************************************************/
#include "Application.hpp"
#include "Input.hpp"
#include <iostream>
#include "Graphics/GL.hpp"

Application* Application::GetApplication()
{
    static Application* app = new Application;
    return app;
}

void Application::Init()
{
    window.CreateWindow();
    GetWindowSize = window.WindowSize();

	Graphics::GL::setup();

	demo.Init();
}

void Application::Update(float dt)
{
    input.TriggeredReset();

    fpsEllapsedTime += dt;
    ++fpsFrames;
    if (fpsEllapsedTime >= 1.0f)
    {
        fpsEllapsedTime = 0;
        fpsFrames = 0;
    }

	demo.Draw();

    window.PollEvent();
    window.SwapBackBuffer();

    if (input.IsKeyTriggered(GLFW_KEY_A))
    {
        std::cout << "a" << std::endl;
    }
    if (input.IsKeyTriggered(GLFW_KEY_F))
    {
        window.ToggleFullscreen();
    }
    if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_LEFT))
    {
        std::cout << "mouse button triggered" << std::endl;
    }
    if (input.IsMouseDoubleClicked(GLFW_MOUSE_BUTTON_LEFT))
    {
        std::cout << "mouse button double clicked" << std::endl;
    }
}

void Application::Clear()
{
}
