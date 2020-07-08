/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MenuScene.cpp
Author
	- jiwon.jung jjwon6218@gmail.com
Creation Date: 03.13.2020

	Source file for scene which works as menu
******************************************************************************/
#include <Scenes/MenuScene.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/StateMachine.hpp>
#include <States/Walking.hpp>
#include "Component/Button.hpp"
#include "Object/DepthStandard.hpp"
#include <Scenes/SceneManager.hpp>

#include <States/PlayerStates/PlayerReachesGoal.hpp>

#include <Object/SceneStateManager/SceneStateManager.hpp>
#include <States/SceneStates/PauseAndMenu.hpp>
#include <Object/Menu/DestructiveConfirmation.hpp>

MenuScene::MenuScene(): background(nullptr)
{
	selection = 0;
	totalDT = 0.f;
	isMenu = true;
}

MenuScene::~MenuScene()
{

}

void MenuScene::Load()
{
	fileIO* fileio = new fileIO;
	fileio->Input("../assets/fileIO/menuSettings.txt", &player1, &player2, &string);
	MenuScene::InitObject();
	cameraManager.Init();

	selection = 0;
	isSelected = false;
	isMenuPop = false;

	delete fileio;
}

void MenuScene::Update(float dt)
{
	MenuScene::Input();

	totalDT += dt;
	
	if ((static_cast<int>(totalDT) % 2) == 1)
	{
		player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f); //0, 3
		player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
	}
	else 
	{
		player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
		player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
		//player1->GetComponentByTemplate<Physics>()->SetPosition(vector2{ -400.f, -100.f });
		//player2->GetComponentByTemplate<Physics>()->SetPosition(vector2{ -600.f, -100.f });
	}
	MenuScene::Collision();

	vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
	vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

	player1->SetTranslation(obj1Position);
	player2->SetTranslation(obj2Position);
	
	
}

void MenuScene::GameRestart()
{
}

void MenuScene::Unload()
{
}

void MenuScene::Input()
{

	if (input.IsKeyPressed(GLFW_KEY_ENTER))
	{
		isSelected = true;
	}
	else if (input.IsKeyReleased(GLFW_KEY_ENTER) && input.IsKeyTriggered(GLFW_KEY_ENTER) == false && isSelected == true)
	{
		if ((selection % 6) == ButtonRow::NEWGAME)
		{
			SceneManager::GetSceneManager()->SetNextScene("AlphaTutorialLevel1");
		}
		else if ((selection % 6) == ButtonRow::LOADGAME)
		{
			fileIO* loadGame = new fileIO;
			loadGame->LoadGame();
		}
		else if ((selection % 6) == ButtonRow::HOWTOPLAY)
		{
			SceneManager::GetSceneManager()->SetNextScene("HowToPlay");
		}
		else if ((selection % 6) == ButtonRow::SETTINGS)
		{
			SceneManager::GetSceneManager()->SetNextScene("Option");
		}
		else if ((selection % 6) == ButtonRow::CREDIT)
		{
			SceneManager::GetSceneManager()->SetNextScene("Credit");
		}
		else if ((selection % 6) == ButtonRow::QUIT)
		{
			dynamic_cast<DestructiveConfirmation*>(PauseAndMenu::Get()->confirmMenu)->SetDoThis(
				[&]()
				{
					input.SetIsRunning(false);
				}
			);
			PauseAndMenu::Get()->defaultItem = PauseAndMenu::Get()->confirmMenu;
			sceneStateManager->GetComponentByTemplate<StateMachine<SceneStateManager>>()->ChangeState(PauseAndMenu::Get());

			isMenuPop = true;

			input.TriggeredReset();
		}
		soundManager.Play_Sound(SELECT_SOUND);
		isSelected = false;
	}
	if (isMenuPop == true)
	{
		if (input.IsKeyTriggered(GLFW_KEY_ENTER))
		{
			isMenuPop = false;
			isSelected = false;
		}
		return;
	}

	if (input.IsKeyTriggered(GLFW_KEY_UP))
	{
		--selection;
		if (selection < 0)
			selection += 6;

		if ((selection % 6) == ButtonRow::NEWGAME)
		{
			selectionArrow->SetTranslation(vector2{ 425, 200 });
		}
		else if ((selection % 6) == ButtonRow::LOADGAME)
		{
			selectionArrow->SetTranslation(vector2{ 425, 100 });
		}
		else if ((selection % 6) == ButtonRow::HOWTOPLAY)
		{
			selectionArrow->SetTranslation(vector2{ 425, 0 });
		}
		else if ((selection % 6) == ButtonRow::SETTINGS)
		{
			selectionArrow->SetTranslation(vector2{ 425, -100 });
		}
		else if ((selection % 6) == ButtonRow::CREDIT)
		{
			selectionArrow->SetTranslation(vector2{ 425, -200 });
		}
		else if ((selection % 6) == ButtonRow::QUIT)
		{
			selectionArrow->SetTranslation(vector2{ 425, -300 });
		}
		soundManager.Play_Sound(CURSOR_MOVEMENT_SOUND);
	}
	else if (input.IsKeyTriggered(GLFW_KEY_DOWN))
	{
		++selection;

		if ((selection % 6) == ButtonRow::NEWGAME)
		{
			selectionArrow->SetTranslation(vector2{ 425, 200 });
		}
		else if ((selection % 6) == ButtonRow::LOADGAME)
		{
			selectionArrow->SetTranslation(vector2{ 425, 100 });
		}
		else if ((selection % 6) == ButtonRow::HOWTOPLAY)
		{
			selectionArrow->SetTranslation(vector2{ 425, 0 });
		}
		else if ((selection % 6) == ButtonRow::SETTINGS)
		{
			selectionArrow->SetTranslation(vector2{ 425, -100 });
		}
		else if ((selection % 6) == ButtonRow::CREDIT)
		{
			selectionArrow->SetTranslation(vector2{ 425, -200 });
		}
		else if ((selection % 6) == ButtonRow::QUIT)
		{
			selectionArrow->SetTranslation(vector2{ 425, -300 });
		}
		soundManager.Play_Sound(CURSOR_MOVEMENT_SOUND);
	}

}

void MenuScene::Collision()
{
	player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void MenuScene::InitObject()
{
	gameTitle = new Object();
	gameTitle->SetObjectName("gametitle");
	gameTitle->SetTranslation(vector2{ 0, 250 }); //0, 200
	gameTitle->SetScale(vector2{ 600, 300 }); //900, 450
	gameTitle->SetObjectType(Object::ObjectType::TEST);
	gameTitle->AddComponent(new Sprite(gameTitle));
	gameTitle->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/UI/GAME_TITLE.png");
	gameTitle->SetDepth(Depth_Standard::Button);

	Transform transform;

	transform.SetTranslation(vector2(600, 200));
	transform.SetScale(vector2(200, 75));

	nextLevelButton = new Object();
	nextLevelButton->SetObjectName("NewGamelevel");
	nextLevelButton->SetTranslation(transform.GetTranslation());
	nextLevelButton->SetScale(transform.GetScale());
	nextLevelButton->SetObjectType(Object::ObjectType::BUTTON);
	nextLevelButton->AddComponent(new Sprite(nextLevelButton));
	nextLevelButton->AddComponent(new Button(nextLevelButton, Button::Identifier::NextScene, "AlphaTutorialLevel1", transform));
	nextLevelButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/UI/NewGame.png");
	nextLevelButton->SetDepth(Depth_Standard::Button);

	transform.SetTranslation(vector2(600, 100));
	transform.SetScale(vector2(200, 75));

	loadGameButton = new Object();
	loadGameButton->SetObjectName("LoadGamelevel");
	loadGameButton->SetTranslation(transform.GetTranslation());
	loadGameButton->SetScale(transform.GetScale());
	loadGameButton->SetObjectType(Object::ObjectType::BUTTON);
	loadGameButton->AddComponent(new Sprite(loadGameButton));
	loadGameButton->AddComponent(new Button(loadGameButton, Button::Identifier::NextScene, "AlphaTutorialLevel1", transform));
	loadGameButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/UI/LoadGame.png");
	loadGameButton->SetDepth(Depth_Standard::Button);

	transform.SetTranslation(vector2(600, 0));
	transform.SetScale(vector2(200, 75));

	howToPlayButton = new Object();
	howToPlayButton->SetObjectName("howtoplay");
	howToPlayButton->SetTranslation(transform.GetTranslation());
	howToPlayButton->SetScale(transform.GetScale());
	howToPlayButton->SetObjectType(Object::ObjectType::BUTTON);
	howToPlayButton->AddComponent(new Sprite(howToPlayButton));
	howToPlayButton->AddComponent(new Button(howToPlayButton, Button::Identifier::NextScene, "HowToPlay", transform));
	howToPlayButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/UI/HowToPlay.png");
	howToPlayButton->SetDepth(Depth_Standard::Button);

	transform.SetTranslation(vector2(600, -100));
	transform.SetScale(vector2(200, 75));

	settingButton = new Object();
	settingButton->SetObjectName("setting");
	settingButton->SetTranslation(transform.GetTranslation());
	settingButton->SetScale(transform.GetScale());
	settingButton->SetObjectType(Object::ObjectType::BUTTON);
	settingButton->AddComponent(new Sprite(settingButton));
	settingButton->AddComponent(new Button(settingButton, Button::Identifier::NextScene, "Option", transform));
	settingButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/UI/Option.png");
	settingButton->SetDepth(Depth_Standard::Button);

	transform.SetTranslation(vector2(600, -200));
	transform.SetScale(vector2(200, 75));

	creditButton = new Object();
	creditButton->SetObjectName("credit");
	creditButton->SetTranslation(transform.GetTranslation());
	creditButton->SetScale(transform.GetScale());
	creditButton->SetObjectType(Object::ObjectType::BUTTON);
	creditButton->AddComponent(new Sprite(creditButton));
	creditButton->AddComponent(new Button(creditButton, Button::Identifier::NextScene, "Credit", transform));
	creditButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/UI/Credit.png");
	creditButton->SetDepth(Depth_Standard::Button);

	transform.SetTranslation(vector2(600, -300));
	transform.SetScale(vector2(200, 75));

	quitButton = new Object();
	quitButton->SetObjectName("quit");
	quitButton->SetTranslation(transform.GetTranslation());
	quitButton->SetScale(transform.GetScale());
	quitButton->SetObjectType(Object::ObjectType::BUTTON);
	quitButton->AddComponent(new Sprite(quitButton));
	quitButton->AddComponent(new Button(quitButton, Button::Identifier::Quit, "TutorialLevel", transform));
	quitButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/UI/Quit.png");
	quitButton->SetDepth(Depth_Standard::Button);
	
	selectionArrow = new Object();
	selectionArrow->SetObjectName("selectionBox");
	selectionArrow->SetTranslation(vector2{ 425.f, 200.f });
	selectionArrow->SetScale(vector2{100.f});
	selectionArrow->SetObjectType(Object::ObjectType::TEST);
	Animation* selectionAnimation = new Animation(selectionArrow);
	selectionArrow->AddComponent(selectionAnimation);
	selectionAnimation->SetImage("../assets/textures/Hostage.png");
	selectionAnimation->SetState(1);
	selectionAnimation->SetFrame(6);
	selectionAnimation->SetSpeed(5.f);
	selectionArrow->SetDepth(Depth_Standard::Button);

	player1->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(PlayerReachesGoal::Get());
	player2->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(PlayerReachesGoal::Get());


	auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::Stage)->AddObject(gameTitle);
	objManager->FindLayer(LayerNames::Stage)->AddObject(loadGameButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(nextLevelButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(howToPlayButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(settingButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(creditButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(quitButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(selectionArrow);
}



