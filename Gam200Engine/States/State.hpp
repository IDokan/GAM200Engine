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
#include <string>

enum class GameStates 
{
    Menu, Game, Credit, None
};

class State
{
public:
	virtual ~State() = default;
	virtual void Load() = 0;
    virtual void Update(float dt) = 0;
    virtual void Unload() = 0;

public:
    void LevelChangeTo(std::string name)
    {
        next_level = name;
    }
    std::string GetChangedLevelName()
    {
        return next_level;
    }
    bool isNextLevel() 
    {
        return is_next;
    }
    GameStates GetStateInfo() 
    {
        return current_state_info;
    }

protected:    
    GameStates current_state_info = GameStates::None;
    std::string next_level;
    bool is_next = false;

};