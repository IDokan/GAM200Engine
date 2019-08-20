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
#include "States/StateManager.hpp"
#include "Object/ObjectManager.hpp"

Application* Application::GetApplication()
{
    static Application* app = new Application;
    return app;
}

void Application::Init()
{
    window.CreateWindow();
    window.TurnOnMonitorVerticalSynchronization(true);
    GetWindowSize = window.WindowSize();
   
    input.Init();

	Graphics::GL::setup();

	StateManager::GetStateManager()->Init();
	ObjectManager::GetObjectManager()->Init();

	StateManager::GetStateManager()->AddStates("testLevel", dynamic_cast<State*>(&testLevel));
}

void Application::Update(float dt)
{
    input.TriggeredReset();

    fpsEllapsedTime += dt;
    ++fpsFrames;
    if (fpsEllapsedTime >= 1.0f)
    {
        std::cout << fpsFrames << std::endl;
        fpsEllapsedTime = 0;
        fpsFrames = 0;
    }

    window.PollEvent();
    window.SwapBackBuffer();

	const auto& stateManager = StateManager::GetStateManager();
	stateManager->Update(dt);
	ObjectManager::GetObjectManager()->Update(dt);
	stateManager->Draw();

    GetApplication()->Input();
}

void Application::Input()
{
    if (input.IsKeyTriggered(GLFW_KEY_V))
    {
        window.TurnOnMonitorVerticalSynchronization(!window.IsMonitorVerticalSynchronizationOn());
    }  
    if (input.IsKeyTriggered(GLFW_KEY_F))
    {
        window.ToggleFullscreen();
    }  
}

void Application::InputTest()
{
    if (input.IsKeyPressed (GLFW_KEY_A))
    {
        std::cout << "A" << std::endl;
    }
    if (input.IsKeyPressed(GLFW_KEY_B))
    {
        std::cout << "B" << std::endl;
    }
    if (input.IsKeyReleased(GLFW_KEY_B))
    {
        std::cout << "B" << std::endl;
    }
    if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_LEFT))
    {
        std::cout << "left mouse button triggered" << std::endl;
    }
    if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_RIGHT))
    {
        std::cout << "right mouse button triggered" << std::endl;
    }
    if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_MIDDLE))
    {
        std::cout << "middle mouse button triggered" << std::endl;
    }
    if (input.IsMouseDoubleClicked(GLFW_MOUSE_BUTTON_LEFT))
    {
        std::cout << "mouse button double clicked" << std::endl;
    }
}

void Application::Clear()
{
	StateManager::GetStateManager()->Clear();
	ObjectManager::GetObjectManager()->Clear();
}

