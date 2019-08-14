/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
        dbsqhd106@gmail.com
Creation Date: 08.12.2019

    Header file for the Application.cpp
******************************************************************************/

#include "StateManager.hpp"
#include <iostream>

StateManager* StateManager::state_manager = nullptr;

StateManager * StateManager::GetStateManager()
{
    return state_manager;
}

void StateManager::Init()
{
    currentState = nullptr;
    states.clear();
}

void StateManager::Update(float dt)
{
    if (is_restart) 
    {
        currentState->Update(dt);
        if (currentState->isNextLevel()) {
            std::string tmpName = currentState->GetChangedLevelName();
            currentState->Unload();
            currentState = states.find(tmpName)->second.get();
            currentState->Load();
        }
    }
    else
    {
        std::cout << "Resume!\n";
    }

}

void StateManager::Clear()
{
    currentState = nullptr;
    states.clear();
}

void StateManager::AddStates(std::string name, State * state)
{
    auto tmp = std::make_pair(name, state);
    if (currentState == nullptr) {
        if (state->GetStateInfo() == GameStates::Menu ) {
            currentState = state;
            currentState->Load();
        }
    }
    states.insert(tmp);
}
