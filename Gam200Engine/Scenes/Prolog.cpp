/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Prolog.hpp
Author
	- doyoung413@gmail.com
Creation Date: 07.09.2020

	Source file for prolog level
******************************************************************************/
#include <Scenes/Prolog.hpp>
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
#include <Component/Sprite/TextComponent.hpp>

Prolog::Prolog() : background(nullptr)
{
	isMenu = true;
	cutCount = 0;
	delay = 0.f;
	maxDelay = 3.0f;
}

Prolog::~Prolog()
{

}

void Prolog::Load()
{

	//fileIO* fileio = new fileIO;
	//fileio->Input("../assets/fileIO/Ending.txt", nullptr, nullptr, nullptr);
	Prolog::InitObject();
	cameraManager.Init();

	//delete fileio;
}

void Prolog::Update(float dt)
{
	delay += dt;
	if (delay > maxDelay)
	{
		delay = 0.0f;
		isCutChanged = true;
		cutCount += 1;
	}
	
	Prolog::Input();
	if (isCutChanged == true)
	{
		switch (cutCount)
		{
		case 1:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/prolog2.png");
			break;
		case 2:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/prolog3.png");
			break;
		case 3:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/prolog4.png");
			break;
		case 4:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/prolog5.png");
			break;
		case 5:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/prolog6.png");
			break;
		case 6:
			cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/prolog7.png");
			break;
		case 7:
			delay = 0.0f;
			cutCount = 0;
			SceneManager::GetSceneManager()->SetNextScene("AlphaTutorialLevel1");
			break;
		}
		isCutChanged = false;
	}
}

void Prolog::GameRestart()
{

}

void Prolog::Unload()
{
}

void Prolog::Input()
{
	if (input.IsKeyTriggered(GLFW_KEY_S))
	{
		cutCount = 0;
		delay = 0.0f;
		SceneManager::GetSceneManager()->SetNextScene("AlphaTutorialLevel1");
	}
	else if (input.IsAnyKeyTriggered())
	{
		delay = 0.0f;
		isCutChanged = true;
		cutCount += 1;
	}
}

void Prolog::InitObject()
{
	
	cutScene = new Object();
	cutScene->SetObjectName("cutScene");
	cutScene->SetTranslation(vector2(0.f, 0.f));
	cutScene->SetScale(vector2(800.f, 600.f));
	cutScene->SetObjectType(Object::ObjectType::TEST);
	cutScene->AddComponent(new Sprite(cutScene));
	cutScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/cutscenes/prolog1.png");
	cutScene->SetDepth(Depth_Standard::Obstacle);
	
	pressS = new Object();
	pressS->SetObjectName("pressS");
	pressS->SetTranslation(vector2(400, -400));
	TextComponent* text = new TextComponent(pressS);
	pressS->AddComponent(text);
	text->SetString(L"press \"S\" to Skip");
	pressS->SetObjectName("pressS");

	auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::Stage)->AddObject(cutScene);
	objManager->FindLayer(LayerNames::Stage)->AddObject(pressS);
}