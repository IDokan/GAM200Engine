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
	delay = 0;
	maxDelay = 3.0f;
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
	delay += dt;
	if (delay > maxDelay)
	{
		delay = 0.0f;
		isCutChanged = true;
		cutCount += 1;
	}

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
			maxDelay = 1.0f;
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
			maxDelay = 3.0f;
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
		delay = 0.0f;
		isCutChanged = true;
		cutCount += 1;
	}
}

void Ending::InitObject()
{
	cutScene = new Object();
	cutScene->SetObjectName("cutScene");
	cutScene->SetTranslation(vector2(0.f, 0.f));
	cutScene->SetScale(vector2(840.f, 650.f));
	cutScene->SetObjectType(Object::ObjectType::TEST);
	cutScene->AddComponent(new Sprite(cutScene));
	cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/ending1.png");
	cutScene->SetDepth(Depth_Standard::Obstacle);

	pressS = new Object();
	pressS->SetObjectName("pressS");
	pressS->SetTranslation(vector2(600, -400));
	pressS->SetScale(vector2(300, 50));
	pressS->SetObjectType(Object::ObjectType::TEST);
	pressS->AddComponent(new Sprite(pressS));
	pressS->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/pressS.png");
	pressS->SetDepth(Depth_Standard::Obstacle);

	auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::Stage)->AddObject(cutScene);
	objManager->FindLayer(LayerNames::Stage)->AddObject(pressS);
}