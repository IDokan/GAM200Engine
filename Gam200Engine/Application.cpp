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

#include <Graphics/ImGui/imgui.h>
#include <Graphics/ImGui/imgui_impl_opengl3.h>
#include "Graphics/ImGui/imgui_impl_glfw.h"


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

	// I'm not sure it is right place or not
	// One Possibility:
	// put it after /*renderer.Clear();*/
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const auto& stateManager = StateManager::GetStateManager();
	stateManager->Update(dt);
	ObjectManager::GetObjectManager()->Update(dt);
	stateManager->Draw();

    GetApplication()->Input();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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


	// ImGui Clear
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	window.ClearWindow();
}

