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

#pragma once

#include "State.hpp"
#include <unordered_map>
#include <memory>

class StateManager
{
public:
    static StateManager *GetStateManager();
    void GameRestart() const;
    void Init();
    void Update(float dt);
    void Clear();
    void AddStates(std::string name, State *state);

	void Draw() const noexcept;

	// Setters
	void SetNextLevel(std::string levelName) noexcept;

	// Getters
	std::vector<std::string> GetStateNames() const noexcept;
	State* GetCurrentState() const noexcept;
	
    bool is_restart = false;
     
private:
    StateManager(){};
    std::unordered_map < std::string, std::shared_ptr<State> > states;
    State *currentState = nullptr;
};