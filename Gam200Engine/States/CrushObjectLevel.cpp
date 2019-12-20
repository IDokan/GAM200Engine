/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CrushObjectLevel.cpp
Author: dbsqhd106@gmail.com

Creation Date: DEC/11th/2019

	Source file for the test object whether interact work or not
******************************************************************************/
#include <States/CrushObjectLevel.hpp>
#include <Object/ObjectManager.hpp>
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <Systems/Input.hpp>
#include <Component/GoalComponent.hpp>
#include <GLFW/glfw3.h>

CrushObjectLevel::CrushObjectLevel()
{
}

CrushObjectLevel::~CrushObjectLevel()
{
}

void CrushObjectLevel::Update(float dt)
{
    cameraManager.CameraMove(player1->GetTranslation(), player2->GetTranslation(), 1.1f);
    Input();
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
    vector2 player1Pos = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 player2Pos = player2->GetComponentByTemplate<Physics>()->GetPosition();
    player1->SetTranslation(player1Pos);
    player2->SetTranslation(player2Pos);
}



void CrushObjectLevel::Load()
{
    CrushObjectLevel::InitObject();
    cameraManager.Init(); 
}



void CrushObjectLevel::Input()
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

    const float minimum_scaling_limit = 125.f;
    const float scaling_constant = 1.f;

    if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        if (player1->GetScale().x <= minimum_scaling_limit || player2->GetComponentByTemplate<Physics>()->IsCollided())
        {
            
            return;
        }
        vector2 object1OldScale = player1->GetScale();
        vector2 object2OldScale = player2->GetScale();

        player1->SetScale(player1->GetScale() - scaling_constant);
        player2->SetScale(player2->GetScale() + scaling_constant);
        UpdateCollisionBox(player1, player2);

        player1->GetComponentByTemplate<Physics>()->ManageCollision();
        if (player2->GetComponentByTemplate<Physics>()->IsCollided())
        {
            player1->SetScale(object1OldScale);
            player2->SetScale(object2OldScale);
            UpdateCollisionBox(player1, player2);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
    {
        if (player2->GetScale().x <= minimum_scaling_limit || player1->GetComponentByTemplate<Physics>()->IsCollided())
        {
            return;
        }
        vector2 object1OldScale = player1->GetScale();
        vector2 object2OldScale = player2->GetScale();

        player1->SetScale(player1->GetScale() + scaling_constant);
        player2->SetScale(player2->GetScale() - scaling_constant);
        UpdateCollisionBox(player1, player2);

        player1->GetComponentByTemplate<Physics>()->ManageCollision();

        if (player1->GetComponentByTemplate<Physics>()->IsCollided())
        {
            player1->SetScale(object1OldScale);
            player2->SetScale(object2OldScale);
            UpdateCollisionBox(player1, player2);
        }
    }
}
void CrushObjectLevel::UpdateCollisionBox(Object* obj1, Object* obj2)
{
    obj1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(obj1, Physics::ObjectType::RECTANGLE);
    obj2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(obj2, Physics::ObjectType::RECTANGLE);
}



void CrushObjectLevel::InitObject()
{
    auto objManager = ObjectManager::GetObjectManager();



    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 0.f,-1050.f });
    background->SetScale(vector2{ 2000.f,2400.f });
    background->AddComponent(new Sprite(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

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

    object1 = new CrushableObject(vector2{ -809.f,-1529.f }, vector2{ 380.f,157.f }, Physics::ObjectType::RECTANGLE, string);
    object1->SetObjectName("obj_1");

    object2 = new CrushableObject(vector2{ 413.f,-1535.f }, vector2{ 1176.f,143.f }, Physics::ObjectType::RECTANGLE, string);
    object2->SetObjectName("obj_2");

    object3 = new CrushableObject(vector2{ -413.f,-764.f }, vector2{ 1159.f,157.f }, Physics::ObjectType::RECTANGLE, string);
    object3->SetObjectName("obj_3");

    object4 = new CrushableObject(vector2{ 806.f,-763.f }, vector2{ 394.f,143.f }, Physics::ObjectType::RECTANGLE, string);
    object4->SetObjectName("obj_4");

    object5 = new CrushableObject(vector2{ -394.f,-1530.f }, vector2{ 173.f,163.f }, Physics::ObjectType::RECTANGLE, string);
    object5->SetObjectName("obj_5");
	object5->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/background.png");

    object6 = new CrushableObject(vector2{ 389.f,-766.f }, vector2{ 173.f,159.f }, Physics::ObjectType::RECTANGLE, string);
    object6->SetObjectName("obj_6");
	object6->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/background.png");

	objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object4);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object5);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object6);
    objManager->FindLayer(Stage)->AddObject(string);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(background);

}


void CrushObjectLevel::GameRestart()
{
}

void CrushObjectLevel::Collision()
{
}

void CrushObjectLevel::Unload()
{
}