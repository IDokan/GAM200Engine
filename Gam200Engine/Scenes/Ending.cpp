/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Ending.hpp
Author
	- doyoung413@gmail.com
Creation Date: 07.09.2020

	Source file for ending level
******************************************************************************/
#include <Scenes/Ending.hpp>
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

Ending::Ending() : background(nullptr)
{
	isMenu = true;
}

Ending::~Ending()
{

}

void Ending::Load()
{

	//fileIO* fileio = new fileIO;
	//fileio->Input("../assets/fileIO/Ending.txt", nullptr, nullptr, nullptr);
	Ending::InitObject();
	cameraManager.Init();

	//delete fileio;
}

void Ending::Update(float dt)
{
	Ending::Input();
	if (isCutChanged == true)
	{
		switch (cutCount)
		{
		case 1:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending2.png");
			break;
		case 2:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending3.png");
			break;
		case 3:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending4.png");
			break;
		case 4:
			cutScene->SetTranslation(vector2(0.f, 0.f));
			cutScene->SetScale(vector2(840.f, 500.f));
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending5.png");
			break;
		case 5:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending6.png");
			break;
		case 6:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending7.png");
			break;
		case 7:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending8.png");
			break;
		case 8:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending9.png");
			break;
		case 9:
			cutScene->SetTranslation(vector2(0.f, 0.f));
			cutScene->SetScale(vector2(800.f, 300.f));
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending10.png");
			break;
		case 10:
			SceneManager::GetSceneManager()->SetNextScene("Credit");
			break;
		}
		isCutChanged = false;
	}
}

void Ending::GameRestart()
{

}

void Ending::Unload()
{
}

void Ending::Input()
{
	if (input.IsKeyTriggered(GLFW_KEY_S))
	{
		SceneManager::GetSceneManager()->SetNextScene("Credit");
	}
	else if (input.IsAnyKeyTriggered())
	{
		isCutChanged = true;
		cutCount += 1;
	}
}

void Ending::InitObject()
{/*
	background = new Object();
	background->SetObjectName("background1");
	background->SetTranslation(vector2{ 1.f });
	background->SetScale(vector2{ 10000.f });
	background->AddComponent(new Sprite(background));
	background->AddComponent(new Physics(background));
	background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");
	background->SetDepth(Depth_Standard::FurtherBackground);*/

	cutScene = new Object();
	cutScene->SetObjectName("cutScene");
	cutScene->SetTranslation(vector2(0.f, 0.f));
	cutScene->SetScale(vector2(840.f, 650.f));
	cutScene->SetObjectType(Object::ObjectType::TEST);
	cutScene->AddComponent(new Sprite(cutScene));
	cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending1.png");
	cutScene->SetDepth(Depth_Standard::Obstacle);

	auto objManager = ObjectManager::GetObjectManager();

	//objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
	objManager->FindLayer(LayerNames::Stage)->AddObject(cutScene);
}