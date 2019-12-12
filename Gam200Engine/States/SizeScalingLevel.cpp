/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SizeScalingLevel.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 12.10.2019

	Source file for level that teach size scaling
******************************************************************************/
#include <States/SizeScalingLevel.hpp>

SizeScalingLevel::SizeScalingLevel()
{
}

SizeScalingLevel::~SizeScalingLevel()
{
}

void SizeScalingLevel::Load()
{
}

void SizeScalingLevel::Update(float /*dt*/)
{
}

void SizeScalingLevel::GameRestart()
{
}

void SizeScalingLevel::Unload()
{
}
void SizeScalingLevel::Input()
{
    player1->Move();
    player2->Move();

}

void SizeScalingLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void SizeScalingLevel::InitObject() {

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 0.f });
    background->SetScale(vector2{ 2000.f,2000.f });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

    player1 = new Player1("player1", vector2{ -200.f ,-800.f }, vector2{ 150.f }, Physics::ObjectType::RECTANGLE, -1.f);
    player1->SetObjectType(Object::ObjectType::PLAYER_1);
    player1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p1.png");
    player1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player1, Physics::ObjectType::RECTANGLE);

    player2 = new Player2("player2", vector2{ 200.f ,-800.f }, vector2{ 150.f }, Physics::ObjectType::RECTANGLE, 0.f);
    player2->SetObjectType(Object::ObjectType::PLAYER_2);
    player2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");
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

    scaleObject1 = new Object();
    scaleObject1->SetObjectType(Object::ObjectType::OBSTACLE);
    scaleObject1->SetObjectName("scaleObj1");
    scaleObject1->SetTranslation(vector2{ -500.f, -300.f });
    scaleObject1->SetScale(vector2{ 150.f });
    scaleObject1->SetRotation(45);
    scaleObject1->AddComponent(new Sprite(scaleObject1));
    scaleObject1->AddComponent(new Physics(scaleObject1));
    scaleObject1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(scaleObject1, Physics::ObjectType::RECTANGLE);
    scaleObject1->SetDepth(-1.f);

    scaleObject2 = new Object();
    scaleObject2->SetObjectType(Object::ObjectType::OBSTACLE);
    scaleObject2->SetObjectName("scaleObj2");
    scaleObject2->SetTranslation(vector2{ -500.f, 300.f });
    scaleObject2->SetScale(vector2{ 150.f });
    scaleObject2->SetRotation(275);
    scaleObject2->AddComponent(new Sprite(scaleObject2));
    scaleObject2->AddComponent(new Physics(scaleObject2));
    scaleObject2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(scaleObject2, Physics::ObjectType::RECTANGLE);
    scaleObject2->SetDepth(-1.f);


    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(Stage)->AddObject(string);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(scaleObject1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(scaleObject2);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

}
