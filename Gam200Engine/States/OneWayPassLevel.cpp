/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   OneWayPassLevel.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
    - Hyerin Jung junghl0621@gmail.com
Creation Date: 12.10.2019

	Source file for level that string make player move easily
******************************************************************************/
#include <States/OneWayPassLevel.hpp>
#include <Object/Players/Player1.h>
#include <Object/Players/Player2.h>
#include <Object/ObjectManager.hpp>

OneWayPassLevel::OneWayPassLevel()
{
}

OneWayPassLevel::~OneWayPassLevel()
{
}

void OneWayPassLevel::Load()
{
    OneWayPassLevel::InitObject();

    cameraManager.Init();
}

void OneWayPassLevel::Update(float dt)
{
	cameraManager.CameraMove(player1->GetTranslation(), player2->GetTranslation(), 1.1f);
	Input();
}

void OneWayPassLevel::Unload()
{
}

void OneWayPassLevel::Input()
{
    player1->Move();
    player2->Move();
}

void OneWayPassLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void OneWayPassLevel::InitObject() {

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 0.f });
    background->SetScale(vector2{ 2000.f,2000.f });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

    player1 = new Player1("player1", vector2{ -200.f ,-800.f }, vector2{ 150.f }, Physics::ObjectType::RECTANGLE, -1.f);
    player1->SetObjectType(Object::ObjectType::PLAYER_1);
    player1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player1, Physics::ObjectType::RECTANGLE);

    player2 = new Player2("player2", vector2{ 200.f ,-800.f }, vector2{ 150.f }, Physics::ObjectType::RECTANGLE, 0.f);
    player2->SetObjectType(Object::ObjectType::PLAYER_2);
    player2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player2, Physics::ObjectType::RECTANGLE);

    string = new String(player1, player2);

    goalPoint = new Object();
    goalPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    goalPoint->SetObjectName("goalPoint");
    goalPoint->SetTranslation(vector2{ 0.f, 1000.f });
    goalPoint->SetScale(vector2{ 150.f });
    goalPoint->AddComponent(new Sprite(goalPoint));
    goalPoint->AddComponent(new Physics(goalPoint));
    goalPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(goalPoint, Physics::ObjectType::RECTANGLE);
    goalPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
    goalPoint->SetDepth(-1.f);

    startPoint = new Object();
    startPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    startPoint->SetObjectName("goalPoint");
    startPoint->SetTranslation(vector2{ 0.f, -1000.f });
    startPoint->SetScale(vector2{ 150.f });
    startPoint->AddComponent(new Sprite(startPoint));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
    startPoint->SetDepth(-1.f);

    first_Objects_1 = new Object();
    first_Objects_1->SetObjectType(Object::ObjectType::OBSTACLE);
    first_Objects_1->SetObjectName("first_Objects_1");
    first_Objects_1->SetTranslation(vector2{ -930.f, 0.f });
    first_Objects_1->SetScale(vector2{ 1000.f, 150.f });
    first_Objects_1->AddComponent(new Sprite(first_Objects_1));
    first_Objects_1->AddComponent(new Physics(first_Objects_1));
    first_Objects_1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(first_Objects_1, Physics::ObjectType::RECTANGLE);
    first_Objects_1->SetDepth(-1.f);

    first_Objects_2 = new Object();
    first_Objects_2->SetObjectType(Object::ObjectType::OBSTACLE);
    first_Objects_2->SetObjectName("first_Objects_2");
    first_Objects_2->SetTranslation(vector2{ 0.f, 0.f });
    first_Objects_2->SetScale(vector2{ 500.f, 150.f });
    first_Objects_2->AddComponent(new Sprite(first_Objects_2));
    first_Objects_2->AddComponent(new Physics(first_Objects_2));
    first_Objects_2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(first_Objects_2, Physics::ObjectType::RECTANGLE);
    first_Objects_2->SetDepth(-1.f);

    first_Objects_3 = new Object();
    first_Objects_3->SetObjectType(Object::ObjectType::OBSTACLE);
    first_Objects_3->SetObjectName("first_Objects_3");
    first_Objects_3->SetTranslation(vector2{ 900.f, 0.f });
    first_Objects_3->SetScale(vector2{ 900.f, 150.f });
    first_Objects_3->AddComponent(new Sprite(first_Objects_3));
    first_Objects_3->AddComponent(new Physics(first_Objects_3));
    first_Objects_3->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(first_Objects_3, Physics::ObjectType::RECTANGLE);
    first_Objects_3->SetDepth(-1.f);

    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(Stage)->AddObject(string);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(first_Objects_1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(first_Objects_2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(first_Objects_3);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

}
