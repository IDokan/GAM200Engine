/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   GameIsRunning.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.16.2020

	Header file for GameIsRunning State
		When special message is received,
			Change State depends on message's type
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>

#include <Object/Players/Player.h>

class GameIsRunning : public State<SceneStateManager>
{
public:
	static GameIsRunning* Get();

	void Enter(SceneStateManager* manager) override;
	void Execute(SceneStateManager* manager, float dt) override;
	void Exit(SceneStateManager* manager) override;

	void SetIsHostageRescued(bool is) noexcept;
	bool GetIsHostageRescued() noexcept;
	void SetPlayerIsInGoal(Player::Identifier playerID, bool inGoal) noexcept;
	bool GetPlayerIsInGoal(Player::Identifier playerID) const noexcept;

	void CleanAssets() noexcept;

private:
	GameIsRunning();

	bool isHostageRescued;
	bool player1IsInGoal;
	bool player2IsInGoal;
};

