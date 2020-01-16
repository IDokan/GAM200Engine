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
#include <Systems/Input.hpp>
#include <iostream>
#include "Graphics/GL.hpp"
#include "States/StateManager.hpp"
#include "Object/ObjectManager.hpp"

#include <Graphics/ImGui/MyImGui.hpp>

// Include States
#include <States/BasicMovementLevel.hpp>
#include <States/OneWayPassLevel.hpp>
#include <States/SizeScalingLevel.hpp>
#include <States/CrushObjectLevel.hpp>
#include <States/DeadLevel.hpp>


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

#ifdef _DEBUG
    StateManager::GetStateManager()->AddStates("TestLevel", dynamic_cast<State*>(new TestLevel()));
	StateManager::GetStateManager()->AddStates("BasicMovementLevel", dynamic_cast<State*>(new BasicMovementLevel()));
#endif	
	StateManager::GetStateManager()->AddStates("OneWayPassLevel", dynamic_cast<State*>(new OneWayPassLevel()));
	StateManager::GetStateManager()->AddStates("DeadLevel", dynamic_cast<State*>(new DeadLevel()));
    StateManager::GetStateManager()->AddStates("CrushObjectLevel", dynamic_cast<State*>(new CrushObjectLevel()));
	StateManager::GetStateManager()->AddStates("TestLevel", dynamic_cast<State*>(new TestLevel()));
	StateManager::GetStateManager()->AddStates("ProtoLevel", dynamic_cast<State*>(new ProtoLevel()));
	
	 
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

	const auto& stateManager = StateManager::GetStateManager();
	stateManager->Update(dt);
	ObjectManager::GetObjectManager()->Update(dt);
	stateManager->Draw();

    GetApplication()->Input();

	// I'm not sure it is right place or not
	// One Possibility:
	// put it after /*renderer.Clear();*/
	MyImGui::UpdateImGui(show_demo_window, dt);

	// Change Order of calling function : SwapBuffer 
	window.SwapBackBuffer();
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


void Application::Clear()
{
	StateManager::GetStateManager()->Clear();
	ObjectManager::GetObjectManager()->Clear();


	// ImGui Clear
	MyImGui::ClearImGui();

	window.ClearWindow();
}

