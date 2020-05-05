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
#include <States/SceneStates/PlayerIsDead.hpp>
#include <States/SceneStates/SceneComplete.hpp>
#include <Component/MessageCapable.hpp>

#include <Systems/MessageSystem/Message.hpp>
#include <Systems/MessageSystem/MessageDispatcher.hpp>

SceneStateManager::SceneStateManager()
	: nameOfSelectedLevel("BasicMovementLevel")
{
	AddComponent(new MessageCapable(this, MessageObjects::SceneStateManager, 
		[&](const Message& msg) -> bool
		{
			StateMachine<SceneStateManager>* stateMachine = GetComponentByTemplate<StateMachine<SceneStateManager>>();
			switch (msg.Msg)
			{
			case MessageTypes::PlayerIsDead:
				stateMachine->ChangeState(PlayerIsDead::Get());
				break;
			case MessageTypes::GameRestarted:
				stateMachine->ChangeState(GameIsRunning::Get());
				MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::GameRestarted);
				MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::GameRestarted);
				break;
			case MessageTypes::HostageRescued:
				if (GameIsRunning* state = GameIsRunning::Get();
					state == stateMachine->GetCurrentState())
				{
					state->SetIsHostageRescued(true);
				}
				break;
			case MessageTypes::PlayerReachedGoal:
				// if currentState is GameIsRunning
				if (GameIsRunning* state = GameIsRunning::Get();
					state == stateMachine->GetCurrentState())
				{
					switch (msg.Sender)
					{
					case MessageObjects::Player1:
						state->SetPlayerIsInGoal(Player::Identifier::Player1, true);
						break;
					case MessageObjects::Player2:
						state->SetPlayerIsInGoal(Player::Identifier::Player2, true);
						break;
					default:
						break;
					}
				}
				break;
			case MessageTypes::PlayerExitedFromGoal:
				// if currentState is GameIsRunning
				if (GameIsRunning* state = GameIsRunning::Get();
					state == stateMachine->GetCurrentState())
				{
					switch (msg.Sender)
					{
					case MessageObjects::Player1:
						state->SetPlayerIsInGoal(Player::Identifier::Player1, false);
						break;
					case MessageObjects::Player2:
						state->SetPlayerIsInGoal(Player::Identifier::Player2, false);
						break;
					default:
						break;
					}
				}
			default:
				return false;
				break;
			}
			return true;
		}
	));

	AddComponent(new StateMachine<SceneStateManager>(this));
	GetComponentByTemplate<StateMachine<SceneStateManager>>()->SetCurrentState(GameIsRunning::Get());

	SetObjectName("SceneStateManager");
}

void SceneStateManager::SetNameOfSelectedLevel(std::string name) noexcept
{
	nameOfSelectedLevel = name;
}

std::string SceneStateManager::GetNameOfSelectedLevel() const noexcept
{
	return nameOfSelectedLevel;
}
