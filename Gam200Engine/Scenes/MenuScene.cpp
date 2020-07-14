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
#include <Scenes/Scene.hpp>

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
	SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(SOUNDS::HOWTOPLAY_MAIN_BGM);
	SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(SOUNDS::HOWTOPLAY_MAIN_BGM,1.f);

	sceneStateManager->GetComponentByTemplate<StateMachine<SceneStateManager>>()->ChangeState(pam);
	current_scene_info = GameScenes::MainMenu;
}

void MenuScene::Update(float dt)
{
	MenuScene::Input();

	MenuScene::Collision();
}

void MenuScene::GameRestart()
{
}

void MenuScene::Unload()
{
	SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().UnLoad_Sound();
}

void MenuScene::Input()
{
	
}

void MenuScene::Collision()
{
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

	pressEnter = new Object();
	pressEnter->SetObjectName("pressEnter");
	pressEnter->SetTranslation(vector2{ 0, -380 });
	pressEnter->SetScale(vector2{ 750, 60 });
	pressEnter->SetObjectType(Object::ObjectType::TEST);
	pressEnter->AddComponent(new Sprite(pressEnter));
	pressEnter->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/pressEnter.png");
	pressEnter->SetDepth(Depth_Standard::Button);

	auto objManager = ObjectManager::GetObjectManager();
	objManager->FindLayer(LayerNames::Stage)->AddObject(gameTitle);
	objManager->FindLayer(LayerNames::Stage)->AddObject(pressEnter);
}



