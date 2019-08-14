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
    void Init();
    void Update(float dt);
    void Clear();
    void AddStates(std::string name, State *state);

    bool is_restart = false;
     
private:
    static StateManager* state_manager;
    std::unordered_map < std::string, std::shared_ptr<State> > states;
    State *currentState = nullptr;
};