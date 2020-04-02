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
#include <Window/Engine.hpp>
#include <Window/Application.hpp>
#include <Systems/Input.hpp>
#include <iostream>
#include <Object/ObjectManager.hpp>
#include <Scenes/SceneManager.hpp>
#include <Sounds/SoundManager.hpp>
#include <Systems/Timer.hpp>

Application* app_ = nullptr;
//SoundManager BGM;
void Engine::Init()
{
    ////-----------TEST SOUNDS-------------------------
    //test.Load_Sound();
    //test.Play_Sound(SOUNDS::JAMJAMTEST_SOUND);
    //test.SetVolume(JAMJAMTEST_SOUND, 1);
    //------------------------------------------------

    app_ = Application::GetApplication();
    app_->Init();
	Timer* timer = Timer::GetTimer();
    timer->Reset();
    isRunning = true;
}

void Engine::Update()
{
    dt = static_cast<float>(Timer::GetTimer()->GetElapsedSeconds());
	Timer::GetTimer()->Reset();

    app_->Update(dt);
    if (input.IsKeyTriggered(GLFW_KEY_ESCAPE) || input.IsRunning() == false)
    {
        //throw "Hello nice to meet you :)";
        app_->GetApplication()->Clear();
        isRunning = false;
    }
}

void Engine::Clear()
{
	delete Application::GetApplication();
	delete ObjectManager::GetObjectManager();
	delete SceneManager::GetSceneManager();
}
