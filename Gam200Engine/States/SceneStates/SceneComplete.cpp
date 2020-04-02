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
			- Send message ��Players reached goal!�� to both players.
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
#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>

bool IsMousePositionInBox(vector2 mousePosition, vector2 boxPosition, vector2 boxScale)
{
	vector2 min{ boxPosition - (boxScale / 2.f) };
	vector2 max{ boxPosition + (boxScale / 2.f) };

	return !(
		mousePosition.x < min.x ||
		mousePosition.y < min.y ||
		max.x < mousePosition.x ||
		max.y < mousePosition.y
		);
}

SceneComplete* SceneComplete::Get()
{
	static SceneComplete* state = new SceneComplete();
	return state;
}

void SceneComplete::Enter(SceneStateManager* /*manager*/)
{
	// Send message ��Players reached goal!�� to both players.
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::SceneComplete);
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::SceneComplete);

	// Display menu that congratulate players and give a couple of choice.
	PrepareAssets();
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(menuBackground);
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(backToMain);
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(goToNextLevel);

	// Play "Scene Complete Sound"
	// TODO:
}

void SceneComplete::Execute(SceneStateManager* manager)
{
	// Wait until player do anything with buttons.
	vector2 mousePos = input.GetMouseAbsolutePosition();
	if (IsMousePositionInBox(mousePos, vector2{ -200.f, 0.f }, vector2{ 160.f, 180.f }))
	{
		if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			printf("Back To Mainmenu button is triggered\n");
		}
		else	if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			printf("Back To Mainmenu button is pressed!\n");
		}
		else
		{
			printf("Back To Mainmenu button is hovered!\n");
		}
	}
	if (IsMousePositionInBox(mousePos, vector2{ 200.f, 0.f }, vector2{ 160.f, 180.f }))
	{
		if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			SceneManager::GetSceneManager()->SetNextScene(manager->GetNameOfSelectedLevel());
		}
		else	if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			printf("Go to Next Level button is pressed!\n");
		}
		else
		{
			printf("Go to Next Level button is hovered!\n");
		}
	}
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
		// When scale is { 0.4f, 0.4f } and translation is { -0.25f, 0.f }
		//		-360, +90											-40, +90
		//
		//									-200, 0
		//
		//		-360, -90											-40, -90
		// Width = 160 & Height = 180
		backToMain = new Object();
		backToMain->SetObjectName("BackToMain Button");
		backToMain->SetScale(vector2{ 0.4f, 0.4f });
		backToMain->SetTranslation(vector2{ -0.25f, 0.f });
		Sprite* spriteOfBackButton = new Sprite(backToMain);
		backToMain->AddComponent(spriteOfBackButton);
		spriteOfBackButton->SetImage("../assets/textures/backToMainmenu.png");
		backToMain->SetDepth(Depth_Standard::HUDImage);
	}

	if (goToNextLevel == nullptr)
	{
		// When scale is { 0.4f, 0.4f } and translation is { 0.25f, 0.f }
		//		+40, +90											360, +90
		//
		//									200, 0
		//
		//		+40, -90											360, -90
		// Width = 160 & Height = 180
		goToNextLevel = new Object();
		goToNextLevel->SetObjectName("GoToNextLevel Button");
		goToNextLevel->SetScale(vector2{ 0.4f, 0.4f });
		goToNextLevel->SetTranslation(vector2{ 0.25f, 0.f });
		Sprite* spriteOfNextLevelButton = new Sprite(goToNextLevel);
		goToNextLevel->AddComponent(spriteOfNextLevelButton);
		spriteOfNextLevelButton->SetImage("../assets/textures/goToNextLevel.png");
		goToNextLevel->SetDepth(Depth_Standard::HUDImage);
	}

}

void SceneComplete::CleanAssets() noexcept
{
	menuBackground = nullptr;
	backToMain = nullptr;
	goToNextLevel = nullptr;
}