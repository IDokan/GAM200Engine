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
}

void MenuScene::Update(float dt)
{
	MenuScene::Input();

	totalDT += dt;
	
	if ((static_cast<int>(totalDT) % 2) == 1)
	{
		player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
		player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
	}
	else
	{
		player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);
		player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);
	}

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
	//fileIO* fileio = new fileIO;
	//fileio->Output("../assets/fileIO/menuSettings.txt");
}

void MenuScene::Input()
{
	if (input.IsKeyTriggered(GLFW_KEY_UP))
	{
		--selection;
		if (selection < 0)
			selection += 5;

		if ((selection % 5) == ButtonRow::PLAY)
		{
			selectionArrow->SetTranslation(vector2{ 450, 100 });
		}
		else if ((selection % 5) == ButtonRow::HOWTOPLAY)
		{
			selectionArrow->SetTranslation(vector2{ 450, 0 });
		}
		else if ((selection % 5) == ButtonRow::SETTINGS)
		{
			selectionArrow->SetTranslation(vector2{ 450, -100 });
		}
		else if ((selection % 5) == ButtonRow::CREDIT)
		{
			selectionArrow->SetTranslation(vector2{ 450, -200 });
		}
		else if ((selection % 5) == ButtonRow::QUIT)
		{
			selectionArrow->SetTranslation(vector2{ 450, -300 });
		}
	}
	else if (input.IsKeyTriggered(GLFW_KEY_DOWN))
	{
		++selection;

		if ((selection % 5) == ButtonRow::PLAY)
		{
			selectionArrow->SetTranslation(vector2{ 450, 100 });
		}
		else if ((selection % 5) == ButtonRow::HOWTOPLAY)
		{
			selectionArrow->SetTranslation(vector2{ 450, 0 });
		}
		else if ((selection % 5) == ButtonRow::SETTINGS)
		{
			selectionArrow->SetTranslation(vector2{ 450, -100 });
		}
		else if ((selection % 5) == ButtonRow::CREDIT)
		{
			selectionArrow->SetTranslation(vector2{ 450, -200 });
		}
		else if ((selection % 5) == ButtonRow::QUIT)
		{
			selectionArrow->SetTranslation(vector2{ 450, -300 });
		}
	}

	if (input.IsKeyPressed(GLFW_KEY_ENTER))
	{
		if ((selection % 5) == ButtonRow::PLAY)
		{
			SceneManager::GetSceneManager()->SetNextScene("AlphaTutorialLevel1");
		}
		else if ((selection % 5) == ButtonRow::HOWTOPLAY)
		{
			SceneManager::GetSceneManager()->SetNextScene("OneWayPassLevel");
		}
		else if ((selection % 5) == ButtonRow::SETTINGS)
		{
			SceneManager::GetSceneManager()->SetNextScene("Option");
		}
		else if ((selection % 5) == ButtonRow::CREDIT)
		{
			SceneManager::GetSceneManager()->SetNextScene("OneWayPassLevel");
		}
		else if ((selection % 5) == ButtonRow::QUIT)
		{
			input.SetIsRunning(false);
		}
	}

}

void MenuScene::Collision()
{
}

void MenuScene::InitObject()
{
	gameTitle = new Object();
	gameTitle->SetObjectName("gametitle");
	gameTitle->SetTranslation(vector2{ 0, 300 });
	gameTitle->SetScale(vector2{ 600, 300 });
	gameTitle->SetObjectType(Object::ObjectType::TEST);
	gameTitle->AddComponent(new Sprite(gameTitle));
	gameTitle->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/GAME_NAME.png");
	gameTitle->SetDepth(Depth_Standard::Button);

	Transform transform;
	transform.SetTranslation(vector2(600, 100));
	transform.SetScale(vector2(200, 75));

	nextLevelButton = new Object();
	nextLevelButton->SetObjectName("nextlevel");
	nextLevelButton->SetTranslation(transform.GetTranslation());
	nextLevelButton->SetScale(transform.GetScale());
	nextLevelButton->SetObjectType(Object::ObjectType::BUTTON);
	nextLevelButton->AddComponent(new Sprite(nextLevelButton));
	nextLevelButton->AddComponent(new Button(nextLevelButton, Button::Identifier::NextScene, "TutorialLevel", transform));
	nextLevelButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/play.png");
	nextLevelButton->SetDepth(Depth_Standard::Button);

	transform.SetTranslation(vector2(600, 0));
	transform.SetScale(vector2(200, 75));

	howToPlayButton = new Object();
	howToPlayButton->SetObjectName("howtoplay");
	howToPlayButton->SetTranslation(transform.GetTranslation());
	howToPlayButton->SetScale(transform.GetScale());
	howToPlayButton->SetObjectType(Object::ObjectType::BUTTON);
	howToPlayButton->AddComponent(new Sprite(howToPlayButton));
	howToPlayButton->AddComponent(new Button(howToPlayButton, Button::Identifier::NextScene, "TutorialLevel", transform));
	howToPlayButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/how_to_play.png");
	howToPlayButton->SetDepth(Depth_Standard::Button);

	transform.SetTranslation(vector2(600, -100));
	transform.SetScale(vector2(200, 75));

	settingButton = new Object();
	settingButton->SetObjectName("setting");
	settingButton->SetTranslation(transform.GetTranslation());
	settingButton->SetScale(transform.GetScale());
	settingButton->SetObjectType(Object::ObjectType::BUTTON);
	settingButton->AddComponent(new Sprite(settingButton));
	settingButton->AddComponent(new Button(settingButton, Button::Identifier::NextScene, "TutorialLevel", transform));
	settingButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/setting.png");
	settingButton->SetDepth(Depth_Standard::Button);

	transform.SetTranslation(vector2(600, -200));
	transform.SetScale(vector2(200, 75));

	creditButton = new Object();
	creditButton->SetObjectName("credit");
	creditButton->SetTranslation(transform.GetTranslation());
	creditButton->SetScale(transform.GetScale());
	creditButton->SetObjectType(Object::ObjectType::BUTTON);
	creditButton->AddComponent(new Sprite(creditButton));
	creditButton->AddComponent(new Button(creditButton, Button::Identifier::NextScene, "TutorialLevel", transform));
	creditButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/credit.png");
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
	quitButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/quit.png");
	quitButton->SetDepth(Depth_Standard::Button);
	
	selectionArrow = new Object();
	selectionArrow->SetObjectName("selectionBox");
	selectionArrow->SetTranslation(vector2{ 450, 100 });
	selectionArrow->SetScale(vector2{50, 50});
	selectionArrow->SetObjectType(Object::ObjectType::TEST);
	selectionArrow->AddComponent(new Sprite(selectionArrow));
	selectionArrow->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/Arrow.png");
	selectionArrow->SetDepth(Depth_Standard::Button);


	auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::Stage)->AddObject(gameTitle);
	objManager->FindLayer(LayerNames::Stage)->AddObject(nextLevelButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(howToPlayButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(settingButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(creditButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(quitButton);
	objManager->FindLayer(LayerNames::Stage)->AddObject(selectionArrow);
}



