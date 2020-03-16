/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SceneComplete.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.16.2020

	Source file for SceneComplete State
		if both players reached goal, both player start dancing to celebrate their achievements.
																			--------- -> This is my hope
		Enter
			- Send message ¡°Players reached goal!¡± to both players.
			- Display menu that congratulate players and give a couple of choice.
			- Play "Scene Complete Sound"
		
		Execute
			- Wait until player do anything with buttons.

		Exit
			- Stop "Scene Complete Sound"

******************************************************************************/
#include <States/SceneStates/SceneComplete.hpp>
#include <Systems/MessageSystem/MessageDispatcher.hpp>

SceneComplete* SceneComplete::Get()
{
	static SceneComplete* state = new SceneComplete();
	return state;
}

void SceneComplete::Enter(SceneStateManager* manager)
{
	// Send message ¡°Players reached goal!¡± to both players.
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::PlayerIsDead);
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::PlayerIsDead);

	// Display menu that congratulate players and give a couple of choice.
	// TODO:

	// Play "Scene Complete Sound"
	// TODO:
}

void SceneComplete::Execute(SceneStateManager* manager)
{
	// Wait until player do anything with buttons.
}

void SceneComplete::Exit(SceneStateManager* manager)
{
	// Stop "Scene Complete Sound"
}

SceneComplete::SceneComplete()
{
}
