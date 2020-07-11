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
#include <Scenes/Intro.hpp>
#include <Scenes/TutorialLevel.hpp>
#include <Scenes/TutorialLevel1.hpp>
#include <Scenes/TutorialLevel2.hpp>
#include <Scenes/Option.hpp>
#include <Scenes/MenuScene.hpp>
#include <Scenes/AlphaTutorialLevel1.hpp>
#include <Scenes/Level3.hpp>
#include <Scenes/Credit.hpp>
#include <Scenes/HowtoPlay.hpp>
#include <Scenes/Level4.hpp>
#include <Scenes/Ending.hpp>

#include <Systems/ObstaclesDrawingHelper.hpp>

// SingleTons
#include <States/AIStates/MouseIdle.hpp>
#include <States/AIStates/Patrol.hpp>
#include <States/PlayerStates/Idle.hpp>
#include <States/PlayerStates/Move.hpp>
#include <States/PlayerStates/Pause.hpp>
#include <States/PlayerStates/PlayerReachesGoal.hpp>
#include <States/PlayerStates/UpdateAnimation.hpp>
#include <States/SceneStates/GamsIsRunning.hpp>
#include <States/SceneStates/PauseAndMenu.hpp>
#include <States/SceneStates/PlayerIsDead.hpp>
#include <States/SceneStates/SceneComplete.hpp>
#include <States/StringStates/StringIdle.hpp>
#include <States/StringStates/StringStretched.hpp>


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

    SceneManager::GetSceneManager()->AddScenes("Intro", dynamic_cast<Scene*>(new Intro()));
    SceneManager::GetSceneManager()->AddScenes("Level4", dynamic_cast<Scene*>(new Level4()));
    SceneManager::GetSceneManager()->AddScenes("MenuScene", dynamic_cast<Scene*>(new MenuScene()));
    SceneManager::GetSceneManager()->AddScenes("AlphaTutorialLevel1", dynamic_cast<Scene*>(new AlphaTutorialLevel1()));
    SceneManager::GetSceneManager()->AddScenes("TutorialLevel2", dynamic_cast<Scene*>(new TutorialLevel2()));
    SceneManager::GetSceneManager()->AddScenes("Level3", dynamic_cast<Scene*>(new Level3()));
    SceneManager::GetSceneManager()->AddScenes("TutorialLevel", dynamic_cast<Scene*>(new TutorialLevel()));
    SceneManager::GetSceneManager()->AddScenes("TutorialLevel1", dynamic_cast<Scene*>(new TutorialLevel1()));
    SceneManager::GetSceneManager()->AddScenes("Option", dynamic_cast<Scene*>(new OptionLevel()));
    SceneManager::GetSceneManager()->AddScenes("Credit", dynamic_cast<Scene*>(new Credit()));
    SceneManager::GetSceneManager()->AddScenes("HowToPlay", dynamic_cast<Scene*>(new HowToPlay()));
    SceneManager::GetSceneManager()->AddScenes("Ending", dynamic_cast<Scene*>(new Ending()));

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

	const auto& sceneManager = SceneManager::GetSceneManager();
	sceneManager->Update(dt);
	ObjectManager::GetObjectManager()->Update(dt);
	MessageDispatcher::GetDispatcher()->DispatchDelayedMessages();
	sceneManager->Draw();

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
    if (input.GetShouldToggleWindow() == true)
    {
        window.ToggleFullscreen();
        input.SetShouldToggleWindow(false);
    }
    if (window.ShouldClose() == true)
    {
        input.SetIsRunning(false);
    }

    if (input.IsKeyTriggered(GLFW_KEY_8))
    {
        if (Move::Get()->moveValue < 300.f)
        {
            Move::Get()->RecalculateAndSetMoveValue(400.f);
        }
        else
        {
            Move::Get()->RecalculateAndSetMoveValue(200.f);
        }
    }
}

void Application::ClearSingleTons()
{
    delete MouseIdle::Get();
    delete Patrol::Get();
    delete Idle::Get();
    delete Move::Get();
    delete Pause::Get();
    delete PlayerReachesGoal::Get();
    delete UpdateAnimation::Get();
    delete GameIsRunning::Get();
    delete PauseAndMenu::Get();
    delete PlayerIsDead::Get();
    delete SceneComplete::Get();
    delete StringIdle::Get();
    delete StringStretched::Get();
}


void Application::Clear()
{
	SceneManager::GetSceneManager()->Clear();
	ObjectManager::GetObjectManager()->Clear();


	// ImGui Clear
	MyImGui::ClearImGui();
	window.ClearWindow();

    ClearSingleTons();
}

