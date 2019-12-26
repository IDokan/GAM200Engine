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
#include <iostream>
#include <algorithm>
#include "StateManager.hpp"


StateManager * StateManager::GetStateManager()
{
    static StateManager* state_manager = new StateManager();
    return state_manager;
}

void StateManager::GameRestart() const
{
    currentState->GameRestartState();
}

void StateManager::Init()
{
    currentState = nullptr;
    states.clear();
}

void StateManager::Update(float dt)
{
    if (!is_restart) 
    {
        currentState->Update(dt);
        if (currentState->isNextLevel()) {
	        const std::string tmpName = currentState->GetChangedLevelName();
            currentState->UnloadState();
            if (const auto & state = states.find(tmpName);
				state != states.end())
            {
				currentState = state->second.get();
            }
            else
            {
				// Print DEBUG data
				std::cout << "Change level failed!\n";
            }
            currentState->LoadState();
        }
    }
    else
    {
        //std::cout << "Resume!\n";
    }

}

void StateManager::Clear()
{
	currentState->UnloadState();
    currentState = nullptr;

    states.clear();
}

void StateManager::AddStates(std::string name, State * state)
{
    auto tmp = std::make_pair(name, state);
    if (currentState == nullptr) {
        // Why does it be right logic? I should double check
    	// if (state->GetStateInfo() == GameStates::Menu ) 
		{
            currentState = state;
            currentState->LoadState();
        }
    }
    states.insert(tmp);
}

// Helper function to get a Draw from each State
void StateManager::Draw() const noexcept
{
	currentState->Draw();
}

void StateManager::SetNextLevel(std::string levelName) noexcept
{
	currentState->LevelChangeTo(levelName);
}

std::vector<std::string> StateManager::GetStateNames() const noexcept
{
	std::vector<std::string> stateNames;
	std::for_each(std::begin(states), std::end(states), [&](const std::pair< std::string, std::shared_ptr<State>>& stateUnit)
		{
			stateNames.push_back(stateUnit.first);
		}
	);

	return stateNames;
}

State* StateManager::GetCurrentState() const noexcept
{
	return currentState;
}
