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

GameIsRunning* GameIsRunning::Get()
{
	static GameIsRunning* state = new GameIsRunning();
	return state;
}

void GameIsRunning::Enter(SceneStateManager* /*manager*/)
{
	// Do nothing
}

void GameIsRunning::Execute(SceneStateManager* /*manager*/)
{
	// Do nothing
}

void GameIsRunning::Exit(SceneStateManager* /*manager*/)
{
	printf("Scene State Manger: GameIsRunning state is exited");
}

GameIsRunning::GameIsRunning()
{
}
