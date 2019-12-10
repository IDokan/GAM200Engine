/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   State.hpp
Author
		rtd99062@gmail.com
Creation Date: 08.12.2019

	Header file for the abstract class for all of state
******************************************************************************/

#pragma once
#include <string>
#include <Graphics/CameraManager.hpp>

enum class GameStates 
{
    Menu, Game, Proto, Test, Credit, None
};

class State abstract
{
public:
	State()
		:current_state_info(GameStates::None), next_level({}), is_next(false), cameraManager({})
	{}
	virtual ~State() = default;
	virtual void Load() = 0;
    virtual void Update(float dt) = 0;
    virtual void Unload() = 0;

	virtual void Draw() const noexcept;

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
    GameStates current_state_info;
    std::string next_level;
    bool is_next;


	Graphics::CameraManager cameraManager{};
};