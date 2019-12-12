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
#include <Component/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>

BasicMovementLevel::BasicMovementLevel()
{
}

BasicMovementLevel::~BasicMovementLevel()
{
}

void BasicMovementLevel::Load()
{
    fileIO* a = 0;
    a->Input("../assets/tmp/objectData.txt");

    BasicMovementLevel::InitObject();

    cameraManager.Init();
}

void BasicMovementLevel::Update(float dt)
{
    BasicMovementLevel::Input();
    BasicMovementLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(obj1Position, obj2Position, 1.1f);
}

void BasicMovementLevel::GameRestart()
{
}

void BasicMovementLevel::Unload()
{
	fileIO* a = 0;
	a->Output();
}

void BasicMovementLevel::Input()
{
    /**********************Moving Object 1*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_W))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_D))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_A))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_A))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_S))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_A))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_D))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_D))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_W) && input.IsKeyReleased(GLFW_KEY_A) && input.IsKeyReleased(GLFW_KEY_S) && input.IsKeyReleased(GLFW_KEY_D))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }




    /**********************Moving Object 2*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_UP))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_LEFT))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_DOWN))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_RIGHT))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_UP) && input.IsKeyReleased(GLFW_KEY_LEFT) && input.IsKeyReleased(GLFW_KEY_DOWN) && input.IsKeyReleased(GLFW_KEY_RIGHT))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }
    if (input.IsKeyTriggered(GLFW_KEY_G))
    {
        if (player1->GetComponentByTemplate<Physics>()->GetIsGhost() == true)
        {
            player1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
        }
        else
        {
            player1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
        }
    }

}

void BasicMovementLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void BasicMovementLevel::InitObject() {

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 1.f });
    background->SetScale(vector2{ 1000.f });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

    player1 = new Object();
    player1->SetObjectType(Object::ObjectType::PLAYER_1);
    player1->SetObjectName("player1");
    player1->SetTranslation(vector2{ -200.f, -400.f });
    player1->SetScale(vector2{ 150.f });
    player1->AddComponent(new Sprite(player1));
    player1->AddComponent(new Physics(player1));
    player1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p1.png");
    player1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player1, Physics::ObjectType::RECTANGLE);
    player1->SetDepth(-1.f);

    player2 = new Object();
    player2->SetObjectName("player2");
    player2->SetObjectType(Object::ObjectType::PLAYER_2);
    player2->SetTranslation(vector2{ 200.f, -400.f });
    player2->SetScale(vector2{ 150.f });
    player2->AddComponent(new Sprite(player2));
    player2->AddComponent(new Physics(player2));
    player2->SetDepth(-1.f);
    player2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player2, Physics::ObjectType::RECTANGLE);
    player2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");

    //player1 = new Player1("player1", vector2{ -200.f ,-800.f }, vector2{ 150.f }, Physics::ObjectType::RECTANGLE, -1.f);
    //player1->SetObjectType(Object::ObjectType::PLAYER_1);
    //player1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player1, Physics::ObjectType::RECTANGLE);
    //player2 = new Player2("player2", vector2{ 200.f ,-800.f }, vector2{ 150.f }, Physics::ObjectType::RECTANGLE, 0.f);
    //player2->SetObjectType(Object::ObjectType::PLAYER_2);
    //player2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player2, Physics::ObjectType::RECTANGLE);

    string = new String(player1, player2);

    goalPoint = new Object();
    goalPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    goalPoint->SetObjectName("goalPoint");
    goalPoint->SetTranslation(vector2{ 0.f, 500.f });
    goalPoint->SetScale(vector2{ 150.f });
    goalPoint->AddComponent(new Sprite(goalPoint));
	goalPoint->AddComponent(new GoalComponent(goalPoint, "OneWayPassLevel"));
    goalPoint->AddComponent(new Physics(goalPoint));
    goalPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(goalPoint, Physics::ObjectType::RECTANGLE);
    goalPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
    goalPoint->SetDepth(-1.f);

    startPoint = new Object();
    startPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    startPoint->SetObjectName("startPoint");
    startPoint->SetTranslation(vector2{ 0.f, -500.f });
    startPoint->SetScale(vector2{ 150.f });
    startPoint->AddComponent(new Sprite(startPoint));
	startPoint->AddComponent(new GoalComponent(startPoint, "OneWayPassLevel"));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
    startPoint->SetDepth(-1.f);

    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(string);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);   

}