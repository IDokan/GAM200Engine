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
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/StateMachine.hpp>
#include <Object/DepthStandard.hpp>
#include <Scenes/SceneManager.hpp>

#include <States/PlayerStates/PlayerReachesGoal.hpp>

#include <Object/Menu/MainMenu.hpp>

#include <Object/SceneStateManager/SceneStateManager.hpp>
#include <States/SceneStates/PauseAndMenu.hpp>
#include <Object/Menu/DestructiveConfirmation.hpp>

MenuScene::MenuScene(): background(nullptr)
{
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

	PauseAndMenu* pam = PauseAndMenu::Get();
	pam->defaultItem = pam->mainMenu;
	sceneStateManager->GetComponentByTemplate<StateMachine<SceneStateManager>>()->ChangeState(pam);
	
}

void MenuScene::Update(float dt)
{
	MenuScene::Input();

	
	if ((static_cast<int>(totalDT) % 2) == 1)
	{
		player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
		player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
	}
	else 
	{
		player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
		player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
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

	player1->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(PlayerReachesGoal::Get());
	player2->GetComponentByTemplate<StateMachine<Player>>()->ChangeState(PlayerReachesGoal::Get());

	auto objManager = ObjectManager::GetObjectManager();
	objManager->FindLayer(LayerNames::Stage)->AddObject(gameTitle);
}



