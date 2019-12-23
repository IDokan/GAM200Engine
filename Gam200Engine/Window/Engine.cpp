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
#include <States/StateManager.hpp>
#include <Sounds/SoundManager.hpp>

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
    timer.Reset();
    isRunning = false;
}

void Engine::Update()
{
    dt = static_cast<float>(timer.GetElapsedSeconds());
    timer.Reset();

    app_->Update(dt);
    if (input.IsKeyTriggered(GLFW_KEY_ESCAPE))
    {
        //throw "Hello nice to meet you :)";
        app_->GetApplication()->Clear();
        isRunning = true;
    }
}

void Engine::Clear()
{
	delete Application::GetApplication();
	delete ObjectManager::GetObjectManager();
	delete StateManager::GetStateManager();
}
