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

#include <Object/ObjectManager.hpp>
#include <Component/Sprite/TextComponent.hpp>
#include <Object/DepthStandard.hpp>

PlayerIsDead* PlayerIsDead::Get()
{
	static PlayerIsDead* state = new PlayerIsDead();
	return state;
}

void PlayerIsDead::Enter(SceneStateManager* /*manager*/)
{
	printf("Scene enter PlayerIsDead state");

	// Send message that make both players die.
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::PlayerIsDead);
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::PlayerIsDead);

	// Display Image that indicate ¡°You are dead.Press ¡®R¡¯ to restart¡±
	PrepareAssets();
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(playerIsDeadText);

	// Play ¡°PlayerIsDead¡± sound.
	// TODO: with Robin
}

void PlayerIsDead::Execute(SceneStateManager* /*manager*/)
{
	if (input.IsKeyPressed(GLFW_KEY_R))
	{
		// Send message as many as needed.
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::SceneStateManager, MessageTypes::GameRestarted);
		SceneManager::GetSceneManager()->GameRestart();
	}
}

void PlayerIsDead::Exit(SceneStateManager* /*manager*/)
{
	playerIsDeadText->SetDead(true);
	playerIsDeadText = nullptr;
}

PlayerIsDead::PlayerIsDead()
	: playerIsDeadText(nullptr)
{
}

void PlayerIsDead::PrepareAssets() noexcept
{
	if (playerIsDeadText == nullptr)
	{
		playerIsDeadText = new Object();
		playerIsDeadText->SetObjectName("PlayerIsDead Text");
		playerIsDeadText->SetScale(0.5f);
		playerIsDeadText->AddComponent(new TextComponent(playerIsDeadText));
		playerIsDeadText->GetComponentByTemplate<TextComponent>()->SetString(L"Player Is Dead!\n Press 'R' to restart");
		playerIsDeadText->SetDepth(Depth_Standard::HUDText);
	}
}
