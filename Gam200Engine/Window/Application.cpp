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
#include <Systems/MessageSystem/MessageDispatcher.hpp>

// Include States
#include <Scenes/Editor.hpp>
#include <Scenes/TutorialLevel.hpp>
#include <Scenes/TutorialLevel1.hpp>
#include <Scenes/TutorialLevel2.hpp>
#include <Scenes/Level1.hpp>

#include <Systems/ObstaclesDrawingHelper.hpp>


Application* Application::GetApplication()
{
    static Application* app = new Application();
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

//#ifdef _DEBUG
	SceneManager::GetSceneManager()->AddScenes("TutorialLevel2", dynamic_cast<Scene*>(new TutorialLevel2()));
	
//#endif
    SceneManager::GetSceneManager()->AddScenes("TutorialLevel1", dynamic_cast<Scene*>(new TutorialLevel1()));
    SceneManager::GetSceneManager()->AddScenes("TutorialLevel", dynamic_cast<Scene*>(new TutorialLevel()));
    SceneManager::GetSceneManager()->AddScenes("Level1", dynamic_cast<Scene*>(new Level1()));
    

	ObstaclesDrawingHelper::Get()->Init();
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
	MessageDispatcher::GetDispatcher()->DispatchDelayedMessages();
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

