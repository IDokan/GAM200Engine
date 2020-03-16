/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   PlayerIsDead.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.16.2020

	Source file for PlayerIsDead State
		When Any player is dead, scene become this state.

		Enter
			- Send message that make both players die.
			- Display Image that indicate ¡°You are dead. Press ¡®R¡¯ to restart¡±
			- Play ¡°PlayerIsDead¡± sound.
		
		Execute
			- Wait until player press ¡®R¡¯.

		Exit
			- Stop "PlayerIsDead" sound.

******************************************************************************/
#include <States/SceneStates/PlayerIsDead.hpp>
#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>
#include <Systems/MessageSystem/MessageDispatcher.hpp>

PlayerIsDead* PlayerIsDead::Get()
{
	static PlayerIsDead* state = new PlayerIsDead();
	return state;
}

void PlayerIsDead::Enter(SceneStateManager* manager)
{
	printf("Scene enter PlayerIsDead state");

	// Send message that make both players die.
	// Display Image that indicate ¡°You are dead.Press ¡®R¡¯ to restart¡±
	// Play ¡°PlayerIsDead¡± sound.
}

void PlayerIsDead::Execute(SceneStateManager* manager)
{
	if (input.IsKeyPressed(GLFW_KEY_R))
	{
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::SceneStateManager, MessageTypes::GameRestarted);
		SceneManager::GetSceneManager()->GameRestart();
	}
}

void PlayerIsDead::Exit(SceneStateManager* manager)
{
	printf("Scene exit PlayerIsDead state");
}

PlayerIsDead::PlayerIsDead()
{
}
