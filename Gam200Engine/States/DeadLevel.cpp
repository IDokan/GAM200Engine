/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: DeadLevel.cpp
Author: dbsqhd106@gmail.com

Creation Date: DEC/11th/2019

    Header file for the test object whether interact work or not
******************************************************************************/
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <States/DeadLevel.hpp>
#include <Systems/Input.hpp>
#include <Component/Physics.hpp>
#include <Object/InteractiveObject/ObstacleObject.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Sounds/SoundManager.hpp>

SoundManager testSoundForDead;
DeadLevel::DeadLevel(): background(nullptr), obj_1(nullptr), obj_2(nullptr), obj_3(nullptr)
{
}

DeadLevel::~DeadLevel()
{
}

void DeadLevel::Update(float /*dt*/)
{
	cameraManager.CameraMove(player1, player2, 1.1f);
    Input();
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
    vector2 player1Pos = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 player2Pos = player2->GetComponentByTemplate<Physics>()->GetPosition();
    player1->SetTranslation(player1Pos);
    player2->SetTranslation(player2Pos);

    if ((player1->GetComponentByTemplate<Physics>()->GetPosition().x < -(background->GetScale().x / 2) ||
        player1->GetComponentByTemplate<Physics>()->GetPosition().x >(background->GetScale().x / 2) ||
        player2->GetComponentByTemplate<Physics>()->GetPosition().x < -(background->GetScale().x / 2) ||
        player2->GetComponentByTemplate<Physics>()->GetPosition().x >(background->GetScale().x / 2))
        )
    {
        GameRestart();
    }
}

void DeadLevel::GameRestart()
{

    testSoundForDead.Play_Sound(SOUNDS::FALLING_SOUND);
    player1->SetTranslation(vector2{ -200.f, -2000.f });
    player2->SetTranslation(vector2{ 200.f, -2000.f }); //change actual location
    player1->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(player1->GetTranslation());
    player2->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(player2->GetTranslation());
    player1->GetComponentByTemplate<Physics>()->SetOldPosition(player1->GetTranslation());
    player2->GetComponentByTemplate<Physics>()->SetOldPosition(player2->GetTranslation());
    player1->GetComponentByTemplate<Physics>()->SetPosition(player1->GetTranslation());
    player2->GetComponentByTemplate<Physics>()->SetPosition(player2->GetTranslation());
    string->InitString();
}

void DeadLevel::Load()
{
    DeadLevel::InitObject();
    cameraManager.Init();
    testSoundForDead.Load_Sound();
    testSoundForDead.SetVolume(FALLING_SOUND, 1);
}

void DeadLevel::Unload()
{
}

void DeadLevel::Input()
{
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

void DeadLevel::InitObject()
{
    auto objManager = ObjectManager::GetObjectManager();

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 0.f,-1050.f });
    background->SetScale(vector2{ 2000.f,2400.f });
    background->AddComponent(new Sprite(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");
    objManager->FindLayer(LayerNames::Stage)->AddObject(background);

    player1 = new Object();
    player1->SetObjectType(Object::ObjectType::PLAYER_1);
    player1->SetObjectName("player1");
    player1->SetTranslation(vector2{ -200.f, -2000.f });
    player1->SetScale(vector2{ 150.f });
    player1->AddComponent(new Sprite(player1));
    player1->AddComponent(new Physics(player1));
    player1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p1.png");
    player1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player1, Physics::ObjectType::RECTANGLE);
    player1->SetDepth(-1.f);

    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);

    player2 = new Object();
    player2->SetObjectName("player2");
    player2->SetObjectType(Object::ObjectType::PLAYER_2);
    player2->SetTranslation(vector2{ 200.f, -2000.f });
    player2->SetScale(vector2{ 150.f });
    player2->AddComponent(new Sprite(player2));
    player2->AddComponent(new Physics(player2));
    player2->SetDepth(-1.f);
    player2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player2, Physics::ObjectType::RECTANGLE);
    player2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");

    string = new String(player1, player2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(string);

    obj_1 = new ObstacleObject(vector2{ -307.f, -411.f }, vector2{ 340.f ,750.f }, Physics::ObjectType::CIRCLE);
    obj_1->SetObjectType(Object::ObjectType::OBSTACLE);
    obj_1->SetObjectName("obj_1");
    obj_1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/sharp_box.png");
    objManager->FindLayer(LayerNames::Stage)->AddObject(obj_1);


    obj_2 = new ObstacleObject(vector2{ 565.f, -574.f }, vector2{ 570.f ,910.f }, Physics::ObjectType::CIRCLE);
    obj_2->SetObjectType(Object::ObjectType::OBSTACLE);
    obj_2->SetObjectName("obj_2");
    obj_2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/sharp_box.png");
    objManager->FindLayer(LayerNames::Stage)->AddObject(obj_2);


    obj_3 = new ObstacleObject(vector2{ -420.f, -1300.f }, vector2{ 740.f ,715.f }, Physics::ObjectType::CIRCLE);
    obj_3->SetObjectType(Object::ObjectType::OBSTACLE);
    obj_3->SetObjectName("obj_3");
    obj_3->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/sharp_box.png");
    objManager->FindLayer(LayerNames::Stage)->AddObject(obj_3);

	startPoint = new Object();
	startPoint->SetObjectType(Object::ObjectType::OBSTACLE);
	startPoint->SetObjectName("startPoint");
	startPoint->SetTranslation(vector2{ 0.f, -2175.f });
	startPoint->SetScale(vector2{ 250.f,150.f });
	startPoint->AddComponent(new Sprite(startPoint));
	startPoint->AddComponent(new Physics(startPoint));
	startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
	startPoint->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
	startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
	startPoint->SetDepth(-1.f);
	objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);

	goalPoint = new Object();
	goalPoint->SetObjectType(Object::ObjectType::OBSTACLE);
	goalPoint->SetObjectName("goalPoint");
	goalPoint->SetTranslation(vector2{ 0.f, -400.f });
	goalPoint->SetScale(vector2{ 250.f,150.f });
	goalPoint->AddComponent(new Sprite(goalPoint));
	goalPoint->AddComponent(new GoalComponent(goalPoint, "CrushObjectLevel"));
	goalPoint->AddComponent(new Physics(goalPoint));
	goalPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(goalPoint, Physics::ObjectType::RECTANGLE);
	goalPoint->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
	goalPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
	goalPoint->SetDepth(-1.f);

    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    
}
