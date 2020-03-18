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

#include <Component/Sprite/Sprite.hpp>
#include <Object/DepthStandard.hpp>
#include <Object/ObjectManager.hpp>

SceneComplete* SceneComplete::Get()
{
	static SceneComplete* state = new SceneComplete();
	return state;
}

void SceneComplete::Enter(SceneStateManager* /*manager*/)
{
	// Send message ¡°Players reached goal!¡± to both players.
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::SceneComplete);
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::SceneComplete);

	// Display menu that congratulate players and give a couple of choice.
	PrepareAssets();
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(menuBackground);
	//ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(backToMain);
	//ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(goToNextLevel);

	// Play "Scene Complete Sound"
	// TODO:
}

void SceneComplete::Execute(SceneStateManager* /*manager*/)
{
	// Wait until player do anything with buttons.
}

void SceneComplete::Exit(SceneStateManager* /*manager*/)
{
	menuBackground->SetDead(true);
	menuBackground = nullptr;
	backToMain->SetDead(true);
	backToMain = nullptr;
	goToNextLevel->SetDead(true);
	goToNextLevel = nullptr;
	// Stop "Scene Complete Sound"
}

SceneComplete::SceneComplete()
	:menuBackground(nullptr), backToMain(nullptr), goToNextLevel(nullptr)
{
}

void SceneComplete::PrepareAssets() noexcept
{
	if (menuBackground == nullptr)
	{
		menuBackground = new Object();
		menuBackground->SetObjectName("menuBackground");
		menuBackground->SetScale(vector2{ 1.f, 0.6f });
		Sprite* spriteOfBackground = new Sprite(menuBackground);
		menuBackground->AddComponent(spriteOfBackground);
		spriteOfBackground->SetColor(Graphics::Color4f{ 1.f, 0.725f, 0.f });
		spriteOfBackground->SetImage("../assets/textures/rect.png");
		menuBackground->SetDepth(Depth_Standard::HUDBackground);
	}

	if (backToMain == nullptr)
	{
		backToMain = new Object();
		backToMain->SetObjectName("BackToMain Button");
		backToMain->SetScale(vector2{ 2.f, 1.f });
		backToMain->SetTranslation(vector2{ -2.f, -1.f });
		Sprite* spriteOfBackButton = new Sprite(backToMain);
		backToMain->AddComponent(spriteOfBackButton);
		spriteOfBackButton->SetImage("../assets/textures/rect.png");
		backToMain->SetDepth(Depth_Standard::HUDImage);
	}

	if (goToNextLevel == nullptr)
	{
		goToNextLevel = new Object();
		goToNextLevel->SetObjectName("GoToNextLevel Button");
		goToNextLevel->SetScale(vector2{ 2.f, 1.f });
		goToNextLevel->SetTranslation(vector2{ 2.f, -1.f });
		Sprite* spriteOfNextLevelButton = new Sprite(goToNextLevel);
		goToNextLevel->AddComponent(spriteOfNextLevelButton);
		spriteOfNextLevelButton->SetImage("../assets/textures/rect.png");
		goToNextLevel->SetDepth(Depth_Standard::HUDImage);
	}

}
