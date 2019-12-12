/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.cpp
Author
    - Sinil.Kang            rtd99062@gmail.com
    - Hyerin.Jung       junghl0621@gmail.com

Creation Date: 12.10.2019

    Source file for level that player learned how to move player
******************************************************************************/
#include <States/BasicMovementLevel.hpp>

BasicMovementLevel::BasicMovementLevel()
{
}

BasicMovementLevel::~BasicMovementLevel()
{
}

void BasicMovementLevel::Load()
{
    //fileIO* a = 0;
    //a->Input("../assets/tmp/objectData.txt");

    BasicMovementLevel::InitObject();

    cameraManager.Init();
}

void BasicMovementLevel::Update(float dt)
{
    BasicMovementLevel::Input();
    BasicMovementLevel::Collision();
}

void BasicMovementLevel::Unload()
{
}

void BasicMovementLevel::Input()
{
    player1->Move();
    player2->Move();

}

void BasicMovementLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void BasicMovementLevel::InitObject() {

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

    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(Stage)->AddObject(string);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);   

}