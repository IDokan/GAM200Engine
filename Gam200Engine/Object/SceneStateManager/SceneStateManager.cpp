/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SceneStateManager.cpp
Author
	- sinil.gang		rtd99062@gmail.com
Creation Date: 03.16.2020

		Source file for Scene State Manager
		This manager manages state of scene.
		Scene State consist of three different state.
			1. PlayerIsDead
				When Any player is dead, show 'press R to restart' and change players state with Message System.
			2. SceneComplete
				if both players reached goal, both player start dancing to celebrate their achievements.
			3. GameIsRunning
				Nothing to do in here.
******************************************************************************/
#include <Object/SceneStateManager/SceneStateManager.hpp>
#include <Component/StateMachine.hpp>

#include <States/SceneStates/GamsIsRunning.hpp>
#include <Component/MessageCapable.hpp>

#include <Systems/MessageSystem/Message.hpp>

SceneStateManager::SceneStateManager()
{
	AddComponent(new MessageCapable(this, MessageObjects::SceneStateManager, 
		[&](const Message& msg) -> bool
		{
			switch (msg.Msg)
			{
			default:
				break;
			}
		}
	));

	AddComponent(new StateMachine<SceneStateManager>(this));
	GetComponentByTemplate<StateMachine<SceneStateManager>>()->SetCurrentState(GameIsRunning::Get());
}