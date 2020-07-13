/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Credit.cpp
Author
	- jjwon6218@gmail.com
Creation Date: 05.22.2020

	Source file for credit level
******************************************************************************/
#include <Scenes/Credit.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/StateMachine.hpp>
#include "Component/Button.hpp"
#include "Object/DepthStandard.hpp"
#include <Scenes/SceneManager.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>

Credit::Credit() : background(nullptr)
{
    isMenu = true;
}

Credit::~Credit()
{

}

void Credit::Load()
{
	Credit::InitObject();
	cameraManager.Init(); 
}

void Credit::Update(float dt)
{
    Credit::Input();
}

void Credit::GameRestart()
{

}

void Credit::Unload()
{
	//fileIO* fileio = new fileIO;
	//fileio->Output("../assets/fileIO/savedCredit.txt");
}

void Credit::Input()
{
    if (input.IsAnyKeyTriggered())
    {
        SceneManager::GetSceneManager()->SetNextScene("MenuScene");
    }
}

void Credit::Collision()
{

}

void Credit::InitObject()
{
	background = new Object();
	background->SetObjectName("background1");
	background->SetTranslation(vector2{ 1.f });
	background->SetScale(vector2{ 10000.f });
	background->AddComponent(new Sprite(background));
	background->AddComponent(new Physics(background));
	background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");
	background->SetDepth(Depth_Standard::FurtherBackground);

	list1 = new Object();
	list1->SetObjectName("credit1");
	list1->SetTranslation(vector2(-400.f, 83.f));
	list1->SetScale(vector2(600.f, 600.f));
	list1->SetObjectType(Object::ObjectType::TEST);
	list1->AddComponent(new Sprite(list1));
	list1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/credit1.png");
	list1->SetDepth(Depth_Standard::Obstacle);

	list2 = new Object();
	list2->SetObjectName("credit2");
	list2->SetTranslation(vector2(100.f, 83.f));
	list2->SetScale(vector2(600.f, 600.f));
	list2->SetObjectType(Object::ObjectType::TEST);
	list2->AddComponent(new Sprite(list2));
	list2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/credit2.png");
	list2->SetDepth(Depth_Standard::Obstacle);

	list3 = new Object();
	list3->SetObjectName("credit2");
	list3->SetTranslation(vector2(500.f, 83.f));
	list3->SetScale(vector2(600.f, 600.f));
	list3->SetObjectType(Object::ObjectType::TEST);
	list3->AddComponent(new Sprite(list3));
	list3->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/credit3.png");
	list3->SetDepth(Depth_Standard::Obstacle);

	digipenLogo = new Object();
	digipenLogo->SetObjectName("digipenLogo");
	digipenLogo->SetTranslation(vector2(0.f, -273.f));
	digipenLogo->SetScale(vector2(595.f, 223.f));
	digipenLogo->SetObjectType(Object::ObjectType::TEST);
	digipenLogo->AddComponent(new Sprite(digipenLogo));
	digipenLogo->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/DigiPenLogo.png");
	digipenLogo->SetDepth(Depth_Standard::Obstacle);

	auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
	objManager->FindLayer(LayerNames::Stage)->AddObject(list1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(list2);
	objManager->FindLayer(LayerNames::Stage)->AddObject(list3);
	objManager->FindLayer(LayerNames::Stage)->AddObject(digipenLogo);
}