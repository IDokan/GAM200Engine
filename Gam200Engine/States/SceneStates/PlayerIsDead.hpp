/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   PlayerIsDead.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.16.2020

	Header file for PlayerIsDead State
		When Any player is dead, scene become this state.
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>

class PlayerIsDead : public State<SceneStateManager>
{
public:
	static PlayerIsDead* Get();

	void Enter(SceneStateManager* manager) override;
	void Execute(SceneStateManager* manager) override;
	void Exit(SceneStateManager* manager) override;


private:
	PlayerIsDead();
};

