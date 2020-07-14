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

Credit::Credit() : totalDT(0.0f)
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
	if (input.IsKeyPressed(GLFW_KEY_SPACE) || input.IsKeyPressed(GLFW_KEY_ENTER))
	{
		dt = 10.f * dt;
	}

	totalDT += dt;
    Credit::Input();
	cameraManager.MoveUp(dt, -30);
	float currYaxis = cameraManager.GetPosition().y;

	if (totalDT > 50.f || currYaxis < -1800.f)
	{
		SceneManager::GetSceneManager()->SetNextScene("MenuScene");
		totalDT = 0.0f;
	}
}

void Credit::GameRestart()
{

}

void Credit::Unload()
{
}

void Credit::Input()
{
    if (input.IsAnyKeyTriggered() && !input.IsKeyTriggered(GLFW_KEY_SPACE) && !input.IsKeyPressed(GLFW_KEY_ENTER))
    {
        SceneManager::GetSceneManager()->SetNextScene("MenuScene");
    }
}

void Credit::Collision()
{

}

void Credit::InitObject()
{
	list1 = new Object();
	list1->SetObjectName("credit1");
	list1->SetTranslation(vector2(0.f, 0.f));
	list1->SetScale(vector2(600.f, 600.f));
	list1->SetObjectType(Object::ObjectType::TEST);
	list1->AddComponent(new Sprite(list1));
	list1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/credit1.png");
	list1->SetDepth(Depth_Standard::Obstacle);

	list2 = new Object();
	list2->SetObjectName("credit2");
	list2->SetTranslation(vector2(0.f, -450.f));
	list2->SetScale(vector2(600.f, 300.f));
	list2->SetObjectType(Object::ObjectType::TEST);
	list2->AddComponent(new Sprite(list2));
	list2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/credit2.png");
	list2->SetDepth(Depth_Standard::Obstacle);

	list3 = new Object();
	list3->SetObjectName("credit3");
	list3->SetTranslation(vector2(0.f, -750.f));
	list3->SetScale(vector2(600.f, 300.f));
	list3->SetObjectType(Object::ObjectType::TEST);
	list3->AddComponent(new Sprite(list3));
	list3->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/credit3.png");
	list3->SetDepth(Depth_Standard::Obstacle);

	list4 = new Object();
	list4->SetObjectName("credit4");
	list4->SetTranslation(vector2(0.f, -1250.f));
	list4->SetScale(vector2(600.f, 600.f));
	list4->SetObjectType(Object::ObjectType::TEST);
	list4->AddComponent(new Sprite(list4));
	list4->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/credit4.png");
	list4->SetDepth(Depth_Standard::Obstacle);

	digipenLogo = new Object();
	digipenLogo->SetObjectName("digipenLogo");
	digipenLogo->SetTranslation(vector2(0.f, -1700));
	digipenLogo->SetScale(vector2(700.f, 223.f));
	digipenLogo->SetObjectType(Object::ObjectType::TEST);
	digipenLogo->AddComponent(new Sprite(digipenLogo));
	digipenLogo->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/Logos/DigiPenLogo.png");
	digipenLogo->SetDepth(Depth_Standard::Obstacle);

	auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::Stage)->AddObject(list1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(list2);
	objManager->FindLayer(LayerNames::Stage)->AddObject(list3);
	objManager->FindLayer(LayerNames::Stage)->AddObject(list4);
	objManager->FindLayer(LayerNames::Stage)->AddObject(digipenLogo);
}