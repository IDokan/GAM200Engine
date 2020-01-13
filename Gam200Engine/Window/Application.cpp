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
#include "Scenes/SceneManager.hpp"
#include "Object/ObjectManager.hpp"

#include <Graphics/ImGui/MyImGui.hpp>

// Include States
#include <Scenes/BasicMovementLevel.hpp>
#include <Scenes/OneWayPassLevel.hpp>
#include <Scenes/SizeScalingLevel.hpp>
#include <Scenes/CrushObjectLevel.hpp>
#include <Scenes/DeadLevel.hpp>
#include <Scenes/ProtoLevel.hpp>
#include <Scenes/TestLevel.hpp>


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

	SceneManager::GetSceneManager()->Init();
	ObjectManager::GetObjectManager()->Init();

#ifdef _DEBUG
	SceneManager::GetSceneManager()->AddScenes("BasicMovementLevel", dynamic_cast<Scene*>(new BasicMovementLevel()));
#endif									
	SceneManager::GetSceneManager()->AddScenes("OneWayPassLevel", dynamic_cast<Scene*>(new OneWayPassLevel()));
	SceneManager::GetSceneManager()->AddScenes("DeadLevel", dynamic_cast<Scene*>(new DeadLevel()));
    SceneManager::GetSceneManager()->AddScenes("CrushObjectLevel", dynamic_cast<Scene*>(new CrushObjectLevel()));
	SceneManager::GetSceneManager()->AddScenes("TestLevel", dynamic_cast<Scene*>(new TestLevel()));
	SceneManager::GetSceneManager()->AddScenes("ProtoLevel", dynamic_cast<Scene*>(new ProtoLevel()));
	
	 
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

	const auto& stateManager = SceneManager::GetSceneManager();
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
	SceneManager::GetSceneManager()->Clear();
	ObjectManager::GetObjectManager()->Clear();


	// ImGui Clear
	MyImGui::ClearImGui();

	window.ClearWindow();
}

