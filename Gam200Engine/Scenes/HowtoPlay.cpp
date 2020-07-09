/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   HowtoPlay.cpp
Author
	- jjwon6218@gmail.com
Creation Date: 05.29.2020

	cpp file for how to play level
******************************************************************************/
#include <Scenes/HowtoPlay.hpp>
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

HowToPlay::HowToPlay() : background(nullptr)
{
    isMenu = true;
}

HowToPlay::~HowToPlay()
{

}

void HowToPlay::Load()
{
	HowToPlay::InitObject();
	cameraManager.Init();
}

void HowToPlay::Update(float dt)
{
	if (input.IsKeyTriggered(GLFW_KEY_DOWN))
	{
		cameraManager.MoveUp(dt, -10.f);
	}
	if (input.IsKeyTriggered(GLFW_KEY_UP))
	{
		cameraManager.MoveUp(dt, 10.f);
	}

	HowToPlay::Input();
}

void HowToPlay::GameRestart()
{

}

void HowToPlay::Unload()
{
}

void HowToPlay::Input()
{
	if (input.IsKeyTriggered(GLFW_KEY_ESCAPE))
	{
        SceneManager::GetSceneManager()->SetNextScene("MenuScene");
	}
}

void HowToPlay::Collision()
{
}

void HowToPlay::InitObject()
{
	background = new Object();
	background->SetObjectName("background");
	background->SetTranslation(vector2{ 1.f });
	background->SetScale(vector2{ 10000.f });
	background->AddComponent(new Sprite(background));
	background->AddComponent(new Physics(background));
	background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");
	background->SetDepth(Depth_Standard::FurtherBackground);


	//Movement part
	movementIndicator1 = new Object();
	movementIndicator1->SetObjectName("movementIndicator1");
	movementIndicator1->SetTranslation(vector2{ -468.f, 314.f });
	movementIndicator1->SetScale(vector2{ 280.f, 235.f });
	movementIndicator1->AddComponent(new Sprite(movementIndicator1));
	movementIndicator1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/wasdSign.png");
	movementIndicator1->SetObjectType(Object::ObjectType::TEST);
	movementIndicator1->SetDepth(Depth_Standard::WoodSign);

	movementIndicator2 = new Object();
	movementIndicator2->SetObjectName("movementIndicator2");
	movementIndicator2->SetTranslation(vector2{ -178.f, 313.f });
	movementIndicator2->SetScale(vector2{ 280.f, 235.f });
	movementIndicator2->AddComponent(new Sprite(movementIndicator2));
	movementIndicator2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/arrowSign.png");
	movementIndicator2->SetObjectType(Object::ObjectType::TEST);
	movementIndicator2->SetDepth(Depth_Standard::WoodSign);

	movementExplanation = new Object();
	movementExplanation->SetObjectName("movementExplanation");
	movementExplanation->SetTranslation(vector2{ 252.f, 276.f });
	movementExplanation->SetScale(vector2{ 375.f, 125.f });
	movementExplanation->AddComponent(new Sprite(movementExplanation));
	movementExplanation->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/howtoplay1.png");
	movementExplanation->SetObjectType(Object::ObjectType::TEST);
	movementExplanation->SetDepth(Depth_Standard::WoodSign);

	//Size part
	sizeIndicator = new Object();
	sizeIndicator->SetObjectName("sizeIndicator");
	sizeIndicator->SetTranslation(vector2{ -429.f, 17.f });
	sizeIndicator->SetScale(vector2{ 338.f, 276.f });
	Animation* animation = new Animation(sizeIndicator);
	sizeIndicator->AddComponent(animation);
	animation->SetImage("../assets/textures/sizeSign.png");
	animation->SetNumOfState(1);
	animation->SetSpeed(2.5f);
	animation->SetFrame(6);
	sizeIndicator->SetObjectType(Object::ObjectType::TEST);
	sizeIndicator->SetDepth(Depth_Standard::WoodSign);

	sizeExplanation = new Object();
	sizeExplanation->SetObjectName("sizeExplanation");
	sizeExplanation->SetTranslation(vector2{ -350.f, -157.f });
	sizeExplanation->SetScale(vector2{ 500.f, 125.f });
	sizeExplanation->AddComponent(new Sprite(sizeExplanation));
	sizeExplanation->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/howtoplay2.png");
	sizeExplanation->SetObjectType(Object::ObjectType::TEST);
	sizeExplanation->SetDepth(Depth_Standard::WoodSign);

	//Button part

	//Movable box part
	movableBox = new Object();
	movableBox->SetObjectName("movableBox");
	movableBox->SetTranslation(vector2{ -529.f, -259.f });
	movableBox->SetScale(vector2{ 100.f, 100.f });
	movableBox->AddComponent(new Sprite(movableBox));
	movableBox->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/moving_object.png");
	movableBox->SetObjectType(Object::ObjectType::TEST);
	movableBox->SetDepth(Depth_Standard::WoodSign);

    movableBox1 = new Object();
    movableBox1->SetObjectName("movableBox");
    movableBox1->SetTranslation(vector2{ -529.f, -383.f });
    movableBox1->SetScale(vector2{ 100.f, 100.f });
    movableBox1->AddComponent(new Sprite(movableBox1));
    movableBox1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/moving_object_UP.png");
    movableBox1->SetObjectType(Object::ObjectType::TEST);
    movableBox1->SetDepth(Depth_Standard::WoodSign);

	movableBoxExplanation = new Object();
	movableBoxExplanation->SetObjectName("movableBoxExplanation");
	movableBoxExplanation->SetTranslation(vector2{ -212.f, -301.f });
	movableBoxExplanation->SetScale(vector2{ 500.f, 125.f });
	movableBoxExplanation->AddComponent(new Sprite(movableBoxExplanation));
	movableBoxExplanation->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/howtoplay3.png");
	movableBoxExplanation->SetObjectType(Object::ObjectType::TEST);
	movableBoxExplanation->SetDepth(Depth_Standard::WoodSign);



	////Object manager part
	auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
	objManager->FindLayer(LayerNames::Stage)->AddObject(movementIndicator1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(movementIndicator2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(movementExplanation);
	objManager->FindLayer(LayerNames::Stage)->AddObject(sizeIndicator);
	objManager->FindLayer(LayerNames::Stage)->AddObject(sizeExplanation);
	objManager->FindLayer(LayerNames::Stage)->AddObject(movableBox);
    objManager->FindLayer(LayerNames::Stage)->AddObject(movableBox1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(movableBoxExplanation);

}
