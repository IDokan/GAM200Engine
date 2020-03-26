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

MenuScene::MenuScene() //: background(nullptr)
{

}

MenuScene::~MenuScene()
{

}

void MenuScene::Load()
{
	/*fileIO* fileio = new fileIO;
	fileio->Input("../assets/fileIO/menuSettings.txt", &player1, &player2, &string);*/

	MenuScene::InitObject();
	cameraManager.Init();
}

void MenuScene::Update(float /*dt*/)
{
	MenuScene::Input();
	
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
}

void MenuScene::Collision()
{
}

void MenuScene::InitObject()
{
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
	nextLevelButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/PlayButton.png");
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
	howToPlayButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/HowToPlayButton.png");
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
	settingButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/SettingButton.png");
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
	creditButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/CreditButton.png");
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
	quitButton->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/QuitButton.png");
	quitButton->SetDepth(Depth_Standard::Button);

	auto objManager = ObjectManager::GetObjectManager();
	objManager->FindLayer(LayerNames::HUD)->AddObject(nextLevelButton);
	objManager->FindLayer(LayerNames::HUD)->AddObject(howToPlayButton);
	objManager->FindLayer(LayerNames::HUD)->AddObject(settingButton);
	objManager->FindLayer(LayerNames::HUD)->AddObject(creditButton);
	objManager->FindLayer(LayerNames::HUD)->AddObject(quitButton);

}



