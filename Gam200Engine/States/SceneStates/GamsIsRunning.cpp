/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   GameIsRunning.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.16.2020

	Source file for GameIsRunning State
		When special message is received,
			Change State depends on message's type

		Enter
			- Nothing to do.

		Execute
			- Nothing to do.

		Exit
			- Nothing to do.
******************************************************************************/
#include <States/SceneStates/GamsIsRunning.hpp>
#include <Component/StateMachine.hpp>
#include <States/SceneStates/SceneComplete.hpp>

GameIsRunning* GameIsRunning::Get()
{
	static GameIsRunning* state = new GameIsRunning();
	return state;
}

void GameIsRunning::Enter(SceneStateManager* /*manager*/)
{
	// Do nothing
}

void GameIsRunning::Execute(SceneStateManager* manager)
{
	if (player1IsInGoal && player2IsInGoal)
	{
		manager->GetComponentByTemplate<StateMachine<SceneStateManager>>()->ChangeState(SceneComplete::Get());
	}
}

void GameIsRunning::Exit(SceneStateManager* /*manager*/)
{
	printf("Scene State Manger: GameIsRunning state is exited");
}

void GameIsRunning::SetPlayerIsInGoal(Player::Identifier playerID, bool inGoal) noexcept
{
	switch (playerID)
	{
	case Player::Identifier::Player1:
		player1IsInGoal = inGoal;
		break;
	case Player::Identifier::Player2:
		player2IsInGoal = inGoal;
		break;
	default:
		break;
	}
}

bool GameIsRunning::GetPlayerIsInGoal(Player::Identifier playerID) const noexcept
{
	switch (playerID)
	{
	case Player::Identifier::Player1:
		return player1IsInGoal;
		break;
	case Player::Identifier::Player2:
		return player2IsInGoal;
		break;
	default:
		break;
	}
	return false;
}

void GameIsRunning::CleanAssets() noexcept
{
	player1IsInGoal = false;
	player2IsInGoal = false;
}

GameIsRunning::GameIsRunning()
	: player1IsInGoal(false), player2IsInGoal(false)
{
}
