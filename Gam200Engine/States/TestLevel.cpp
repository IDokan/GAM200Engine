/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TestLevel.cpp
Author
    - Sinil.Kang rtd99062@gmail.com

Creation Date: 08.15.2019

    Source file for First Level to Test Sprite Component
******************************************************************************/
#include <iostream>
#include <cmath>
#include "TestLevel.hpp"
#include <Object/ObjectManager.hpp>
#include <Systems/Input.hpp>
#include <Graphics/GL.hpp>
#include <Graphics/Parallax scrolling/Layer.hpp>
#include "Sounds/SoundManager.hpp"
#include <Systems/FileIO.hpp>
// Include Components
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <Component/Animation.hpp>
#include <Component/TextComponent.hpp>
#include <Component/StringSprite.hpp>
#include <Component/StringPhysics.hpp>

#include <Object/InteractiveObject/TestInteractionObject.hpp>

SoundManager test;
void TestLevel::Load()
{
    test.Load_Sound();
    // Set Layer
    auto objManager = ObjectManager::GetObjectManager();
    //Player* player = new Player( , ,,);


    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 0.f });
    background->SetScale(vector2{ 2000.f,4000.f });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

    object1 = new Object();
    object1->SetObjectName("object1");
    object1->SetObjectType(Object::ObjectType::PLAYER_1);
    object1->SetTranslation(vector2{ 1.f,2.f });
    object1->SetScale(vector2{ 200.f });
    object1->AddComponent(new Sprite(object1));
    object1->AddComponent(new Physics(object1));
    object1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 1.f, 1.f });
    object1->SetDepth(-0.1f);
    object1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object1, Physics::ObjectType::RECTANGLE, vector2{ 0 }, vector2{ -50.f });
    objManager->FindLayer(LayerNames::Stage)->AddObject(object1);

    testObject = new Object();
    testObject->SetObjectName("test");
    testObject->SetObjectType(Object::ObjectType::OBSTACLE);
    testObject->SetTranslation(vector2{ 600 });
    testObject->SetScale(vector2{ 100.f });
    testObject->AddComponent(new Sprite(testObject));
    testObject->AddComponent(new Physics(testObject));
    testObject->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 1.f, 1.f });
    testObject->SetDepth(-0.1f);
    testObject->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(testObject, Physics::ObjectType::CIRCLE);
    objManager->FindLayer(LayerNames::Stage)->AddObject(testObject);

    object1 = new Object();
    object1->SetObjectType(Object::ObjectType::PLAYER_1);
    object1->SetObjectName("object1");
    object1->SetTranslation(vector2{ -200.f, -1800.f });
    object1->SetScale(vector2{ 150.f });
    object1->AddComponent(new Sprite(object1));
    object1->AddComponent(new Physics(object1));
    object1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p1.png");
    object1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object1, Physics::ObjectType::RECTANGLE);
    object1->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object1);

    object2 = new Object();
    object2->SetObjectName("object2");
    object2->SetObjectType(Object::ObjectType::PLAYER_2);
    object2->SetTranslation(vector2{ 200.f, -1800.f });
    object2->SetScale(vector2{ 150.f });
    object2->AddComponent(new Sprite(object2));
    object2->AddComponent(new Physics(object2));
    object2->SetDepth(-1.f);
    object2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object2, Physics::ObjectType::RECTANGLE);
    object2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");
    objManager->FindLayer(LayerNames::Stage)->AddObject(object2);

    string = new String(object1, object2);
    objManager->FindLayer(Stage)->AddObject(string);


    goalPoint = new Object();
    goalPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    goalPoint->SetObjectName("goalPoint");
    goalPoint->SetTranslation(vector2{ 0.f, 2000.f });
    goalPoint->SetScale(vector2{ 150.f });
    goalPoint->AddComponent(new Sprite(goalPoint));
    goalPoint->AddComponent(new Physics(goalPoint));
    goalPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(goalPoint, Physics::ObjectType::RECTANGLE);
    goalPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
    goalPoint->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    fileIO* a = 0;
    a->Input("../assets/tmp/objectData.txt");


    startPoint = new Object();
    startPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    startPoint->SetObjectName("goalPoint");
    startPoint->SetTranslation(vector2{ 0.f, -2000.f });
    startPoint->SetScale(vector2{ 150.f });
    startPoint->AddComponent(new Sprite(startPoint));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
    startPoint->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);

    gameClearPopUp = new Object();
    gameClearPopUp->SetObjectName("gameClearPopUp");
    gameClearPopUp->SetObjectType(Object::ObjectType::OBSTACLE);
    gameClearPopUp->SetTranslation(vector2{ cameraManager.GetPosition().x,cameraManager.GetPosition().y });
    gameClearPopUp->SetScale(vector2{ 1600.f,1000.f });
    gameClearPopUp->AddComponent(new Sprite(gameClearPopUp));
    gameClearPopUp->AddComponent(new Physics(gameClearPopUp));
    gameClearPopUp->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/GameClear.png");
    gameClearPopUp->SetDepth(-2.f);

    //=================================================================================================================
    //  Obstacles 1

    first_Objects_1 = new Object();
    first_Objects_1->SetObjectType(Object::ObjectType::OBSTACLE);
    first_Objects_1->SetObjectName("first_Objects_1");
    first_Objects_1->SetTranslation(vector2{ -930.f, -1500.f });
    first_Objects_1->SetScale(vector2{ 1000.f, 150.f });
    first_Objects_1->AddComponent(new Sprite(first_Objects_1));
    first_Objects_1->AddComponent(new Physics(first_Objects_1));
    first_Objects_1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(first_Objects_1, Physics::ObjectType::RECTANGLE);
    first_Objects_1->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(first_Objects_1);

    first_Objects_2 = new Object();
    first_Objects_2->SetObjectType(Object::ObjectType::OBSTACLE);
    first_Objects_2->SetObjectName("first_Objects_2");
    first_Objects_2->SetTranslation(vector2{ 0.f, -1500.f });
    first_Objects_2->SetScale(vector2{ 500.f, 150.f });
    first_Objects_2->AddComponent(new Sprite(first_Objects_2));
    first_Objects_2->AddComponent(new Physics(first_Objects_2));
    first_Objects_2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(first_Objects_2, Physics::ObjectType::RECTANGLE);
    first_Objects_2->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(first_Objects_2);

    first_Objects_3 = new Object();
    first_Objects_3->SetObjectType(Object::ObjectType::OBSTACLE);
    first_Objects_3->SetObjectName("first_Objects_3");
    first_Objects_3->SetTranslation(vector2{ 900.f, -1500.f });
    first_Objects_3->SetScale(vector2{ 900.f, 150.f });
    first_Objects_3->AddComponent(new Sprite(first_Objects_3));
    first_Objects_3->AddComponent(new Physics(first_Objects_3));
    first_Objects_3->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(first_Objects_3, Physics::ObjectType::RECTANGLE);
    first_Objects_3->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(first_Objects_3);

    //
    //=================================================================================================================

    //=================================================================================================================
    //Obstacle 3

    third_Objects_1 = new Object();
    third_Objects_1->SetObjectType(Object::ObjectType::OBSTACLE);
    third_Objects_1->SetObjectName("third_Objects_1");
    third_Objects_1->SetTranslation(vector2{ -600.f, 800.f });
    third_Objects_1->SetScale(vector2{ 500.f, 50.f });
    third_Objects_1->AddComponent(new Sprite(third_Objects_1));
    third_Objects_1->AddComponent(new Physics(third_Objects_1));
    third_Objects_1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(third_Objects_1, Physics::ObjectType::RECTANGLE);
    third_Objects_1->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(third_Objects_1);

    third_Objects_2 = new Object();
    third_Objects_2->SetObjectType(Object::ObjectType::OBSTACLE);
    third_Objects_2->SetObjectName("third_Objects_2");
    third_Objects_2->SetTranslation(vector2{ -825.f, 525.f });
    third_Objects_2->SetScale(vector2{ 50.f, 500.f });
    third_Objects_2->AddComponent(new Sprite(third_Objects_2));
    third_Objects_2->AddComponent(new Physics(third_Objects_2));
    third_Objects_2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(third_Objects_2, Physics::ObjectType::RECTANGLE);
    third_Objects_2->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(third_Objects_2);

    third_Objects_3 = new Object();
    third_Objects_3->SetObjectType(Object::ObjectType::OBSTACLE);
    third_Objects_3->SetObjectName("third_Objects_3");
    third_Objects_3->SetTranslation(vector2{ -550.f, 300.f });
    third_Objects_3->SetScale(vector2{ 500.f, 50.f });
    third_Objects_3->AddComponent(new Sprite(third_Objects_3));
    third_Objects_3->AddComponent(new Physics(third_Objects_3));
    third_Objects_3->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(third_Objects_3, Physics::ObjectType::RECTANGLE);
    third_Objects_3->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(third_Objects_3);

    third_Objects_4 = new Object();
    third_Objects_4->SetObjectType(Object::ObjectType::OBSTACLE);
    third_Objects_4->SetObjectName("third_Objects_4");
    third_Objects_4->SetTranslation(vector2{ -325.f, 737.f });
    third_Objects_4->SetScale(vector2{ 50.f, 175.f });
    third_Objects_4->AddComponent(new Sprite(third_Objects_4));
    third_Objects_4->AddComponent(new Physics(third_Objects_4));
    third_Objects_4->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(third_Objects_4, Physics::ObjectType::RECTANGLE);
    third_Objects_4->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(third_Objects_4);

    third_Objects_5 = new Object();
    third_Objects_5->SetObjectType(Object::ObjectType::OBSTACLE);
    third_Objects_5->SetObjectName("third_Objects_5");
    third_Objects_5->SetTranslation(vector2{ -325.f, 400.f });
    third_Objects_5->SetScale(vector2{ 50.f, 200.f });
    third_Objects_5->AddComponent(new Sprite(third_Objects_5));
    third_Objects_5->AddComponent(new Physics(third_Objects_5));
    third_Objects_5->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(third_Objects_5, Physics::ObjectType::RECTANGLE);
    third_Objects_5->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(third_Objects_5);

    map = new Object();
    map->SetObjectType(Object::ObjectType::OBSTACLE);
    map->SetObjectName("map");
    map->SetTranslation(vector2{ -575.f, 550.f });
    map->SetScale(vector2{ 200.f });
    map->AddComponent(new Sprite(map));
    map->AddComponent(new Physics(map));
    map->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(map, Physics::ObjectType::RECTANGLE);
    map->SetDepth(-1.f);
    map->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/map.png");
    objManager->FindLayer(LayerNames::Stage)->AddObject(map);


    sharpKnife = new Object();
    sharpKnife->SetObjectType(Object::ObjectType::OBSTACLE);
    sharpKnife->SetObjectName("sharpKnife");
    sharpKnife->SetTranslation(vector2{ -600.f, -300.f });
    sharpKnife->SetScale(vector2{ 300.f ,300.f });
    sharpKnife->AddComponent(new Sprite(sharpKnife));
    sharpKnife->AddComponent(new Physics(sharpKnife));
    sharpKnife->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(sharpKnife, Physics::ObjectType::CIRCLE);
    sharpKnife->SetDepth(-1.f);
    sharpKnife->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/sharp_box.png");
    objManager->FindLayer(LayerNames::Stage)->AddObject(sharpKnife);

    cameraManager.Init();
    //=========================================================================================
    // player movement information image update

    movement_p1 = new Object();
    //movement_p1->SetObjectType(Object::ObjectType::OBSTACLE);
    movement_p1->SetObjectName("movement_p1");
    movement_p1->SetTranslation(vector2{ -500.f, -1800.f });
    movement_p1->SetScale(vector2{ 300.f });
    movement_p1->AddComponent(new Sprite(movement_p1));
    movement_p1->SetDepth(-0.9f);
    movement_p1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/movement_P1.png");
    objManager->FindLayer(LayerNames::Stage)->AddObject(movement_p1);

    movement_p2 = new Object();
    //movement_p2->SetObjectType(Object::ObjectType::OBSTACLE);
    movement_p2->SetObjectName("movement_p2");
    movement_p2->SetTranslation(vector2{ 500.f, -1800.f });
    movement_p2->SetScale(vector2{ 300.f });
    movement_p2->AddComponent(new Sprite(movement_p2));
    movement_p2->SetDepth(-0.01f);
    movement_p2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/movement_P2.png");
    objManager->FindLayer(LayerNames::Stage)->AddObject(movement_p2);

    cameraManager.Init();

}

bool check_haha = false;
void TestLevel::Update(float /*dt*/)
{
    TestLevel::LimitStringLength();
    TestLevel::Collision();
    TestLevel::Input();

    vector2 obj1Position = object1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = object2->GetComponentByTemplate<Physics>()->GetPosition();

    object1->SetTranslation(obj1Position);
    object2->SetTranslation(obj2Position);

    // DEBUG object should be updated after camera Update()
    cameraManager.CameraMove(obj1Position, obj2Position, 1.1f);

    auto objManager = ObjectManager::GetObjectManager();


    //Collision Check with goalPoint and Player 1 or 2
    if (goalPoint->GetComponentByTemplate<Physics>()->IsCollideWith(object1)
        && isCheck_Clear == false)
    {
        objManager->FindLayer(LayerNames::HUD)->AddObject(gameClearPopUp);
        isCheck_Clear = true;
    }

    PlayerScaling();



    if (sharpKnife->GetComponentByTemplate<Physics>()->IsCollideWith(string))
    {
        object1->SetTranslation(vector2{ 0.f, -2000.f });
        object2->SetTranslation(vector2{ 200.f, -2000.f });
    }

    DeadAndRestart();
}

void TestLevel::Unload()
{
    fileIO* a = 0;
    a->Output();
    ObjectManager* objManager = ObjectManager::GetObjectManager();
    for (const auto& layers : objManager->GetLayerContainer())
    {
        for (const auto& obj : layers->GetObjContainer())
        {
            obj->SetDead(true);
        }
    }

}

void TestLevel::Input()
{
    /**********************Moving Object 1*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_W))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_D))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_A))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_A))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_S))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_A))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_D))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_D))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_W) && input.IsKeyReleased(GLFW_KEY_A) && input.IsKeyReleased(GLFW_KEY_S) && input.IsKeyReleased(GLFW_KEY_D))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }




    /**********************Moving Object 2*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_UP))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_LEFT))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_DOWN))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_RIGHT))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_UP) && input.IsKeyReleased(GLFW_KEY_LEFT) && input.IsKeyReleased(GLFW_KEY_DOWN) && input.IsKeyReleased(GLFW_KEY_RIGHT))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }
    if (input.IsKeyTriggered(GLFW_KEY_G))
    {
        if (object1->GetComponentByTemplate<Physics>()->GetIsGhost() == true)
        {
            object1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
        }
        else
        {
            object1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
        }
    }
}

void TestLevel::Collision()
{
    object1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void TestLevel::GameDead()
{
    object1->SetTranslation(vector2{ -200.f, -1900.f });
    object1->GetComponentByTemplate<Physics>()->SetOldPosition(vector2{ -200.f, -1900.f });
    object2->SetTranslation(vector2{ 200.f, -1900.f }); //change actual location 
    object2->GetComponentByTemplate<Physics>()->SetOldPosition(vector2{ -200.f, -1900.f });

    string->InitString();

    cameraManager.InitializeCurrentCameraSetting();
}

void UpdateCollisionBox(Object* obj1, Object* obj2)
{
    obj1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(obj1, Physics::ObjectType::RECTANGLE);
    obj2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(obj2, Physics::ObjectType::RECTANGLE);
}

void TestLevel::PlayerScaling()
{
    const float minimum_scaling_limit = 125.f;
    const float scaling_constant = 1.f;

    if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        if (object1->GetScale().x <= minimum_scaling_limit || object2->GetComponentByTemplate<Physics>()->IsCollided())
        {
            return;
        }
        vector2 object1OldScale = object1->GetScale();
        vector2 object2OldScale = object2->GetScale();

        object1->SetScale(object1->GetScale() - scaling_constant);
        object2->SetScale(object2->GetScale() + scaling_constant);
        UpdateCollisionBox(object1, object2);

        TestLevel::Collision();
        if (object2->GetComponentByTemplate<Physics>()->IsCollided())
        {
            object1->SetScale(object1OldScale);
            object2->SetScale(object2OldScale);
            UpdateCollisionBox(object1, object2);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
    {
        if (object2->GetScale().x <= minimum_scaling_limit || object1->GetComponentByTemplate<Physics>()->IsCollided())
        {
            return;
        }
        vector2 object1OldScale = object1->GetScale();
        vector2 object2OldScale = object2->GetScale();

        object1->SetScale(object1->GetScale() + scaling_constant);
        object2->SetScale(object2->GetScale() - scaling_constant);
        UpdateCollisionBox(object1, object2);

        TestLevel::Collision();

        if (object1->GetComponentByTemplate<Physics>()->IsCollided())
        {
            object1->SetScale(object1OldScale);
            object2->SetScale(object2OldScale);
            UpdateCollisionBox(object1, object2);
        }
    }
}

void TestLevel::DeadAndRestart()
{
    // Game over when the players out of background bound. 
    if ((object1->GetComponentByTemplate<Physics>()->GetPosition().x < -(background->GetScale().x / 2) ||
        object1->GetComponentByTemplate<Physics>()->GetPosition().x >(background->GetScale().x / 2) ||
        object2->GetComponentByTemplate<Physics>()->GetPosition().x < -(background->GetScale().x / 2) ||
        object2->GetComponentByTemplate<Physics>()->GetPosition().x >(background->GetScale().x / 2))
        )
    {
        GameDead();
    }
}

void TestLevel::LimitStringLength()
{
    if (string->GetStringLength() > 1000.f)
    {
        object1->GetComponentByTemplate<Physics>()->SetIsCollide(true);
        object2->GetComponentByTemplate<Physics>()->SetIsCollide(true);

        object1->GetComponentByTemplate<Physics>()->SetPosition(object1->GetComponentByTemplate<Physics>()->GetOldPosition());
        object2->GetComponentByTemplate<Physics>()->SetPosition(object2->GetComponentByTemplate<Physics>()->GetOldPosition());
    }
}
