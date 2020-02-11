/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.cpp
Author
    - Hyerin.Jung       junghl0621@gmail.com

Creation Date: 12.10.2019

    Source file for level that player learned how to move player
******************************************************************************/
#include <States/TutorialLevel.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>

SoundManager TestBGMSoundForDebugMode;
TutorialLevel::TutorialLevel() : background(nullptr)
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::Load()
{
    fileIO* a = 0;
    a->Input("../assets/fileIO/saveloadFile.txt");

    TutorialLevel::InitObject();

    cameraManager.Init();
    TestBGMSoundForDebugMode.Load_Sound();
    TestBGMSoundForDebugMode.Play_Sound(SOUNDS::BACKGROUND_SOUND);
    TestBGMSoundForDebugMode.SetVolume(BACKGROUND_SOUND, 0.2f);

}

void TutorialLevel::Update(float /*dt*/)
{
    TutorialLevel::Input();
    TutorialLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(obj1Position, obj2Position, 1.1f);
}

void TutorialLevel::GameRestart()
{
}

void TutorialLevel::Unload()
{
    fileIO* a = 0;
    a->Output();
}

void TutorialLevel::Input()
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

void TutorialLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void TutorialLevel::InitObject() {

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 1.f });
    background->SetScale(vector2{ 2000.f , 4000.f});
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

    string = new String(player1, player2);

    goalPoint = new Object();
    goalPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    goalPoint->SetObjectName("goalPoint");
    goalPoint->SetTranslation(vector2{ 1000.f, -1200.f });
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
    startPoint->SetTranslation(vector2{ -800.f, -2000.f });
    startPoint->SetScale(vector2{ 150.f });
    startPoint->AddComponent(new Sprite(startPoint));
    startPoint->AddComponent(new GoalComponent(startPoint, "OneWayPassLevel"));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
    startPoint->SetDepth(-1.f);


    //================================   BLOCKS   ===================================
    block1 = new Object();
    block1->SetObjectType(Object::ObjectType::OBSTACLE);
    block1->SetObjectName("block1");
    block1->SetTranslation(vector2{ -850.f, -1400.f });
    block1->SetScale(vector2{ 300.f, 10.f });
    block1->AddComponent(new Sprite(block1));
    block1->AddComponent(new Physics(block1));
    block1->SetDepth(-1.f);

    block2 = new Object();
    block2->SetObjectType(Object::ObjectType::OBSTACLE);
    block2->SetObjectName("block2");
    block2->SetTranslation(vector2{ -500.f, -1400.f });
    block2->SetScale(vector2{ 100.f, 10.f });
    block2->AddComponent(new Sprite(block2));
    block2->AddComponent(new Physics(block2));
    block2->SetDepth(-1.f);

    block3 = new Object();
    block3->SetObjectType(Object::ObjectType::OBSTACLE);
    block3->SetObjectName("block3");
    block3->SetTranslation(vector2{ -150.f, -1400.f });
    block3->SetScale(vector2{ 300.f, 10.f });
    block3->AddComponent(new Sprite(block3));
    block3->AddComponent(new Physics(block3));
    block3->SetDepth(-1.f);

    block4 = new Object();
    block4->SetObjectType(Object::ObjectType::OBSTACLE);
    block4->SetObjectName("block4");
    block4->SetTranslation(vector2{ 0.f, -1700.f });
    block4->SetScale(vector2{ 10.f, 600.f });
    block4->AddComponent(new Sprite(block4));
    block4->AddComponent(new Physics(block4));
    block4->SetDepth(-1.f);

    block5 = new Object();
    block5->SetObjectType(Object::ObjectType::OBSTACLE);
    block5->SetObjectName("block5");
    block5->SetTranslation(vector2{ 300.f, -1800.f });
    block5->SetScale(vector2{ 10.f, 400.f });
    block5->AddComponent(new Sprite(block5));
    block5->AddComponent(new Physics(block5));
    block5->SetDepth(-1.f);

    block6 = new Object();
    block6->SetObjectType(Object::ObjectType::OBSTACLE);
    block6->SetObjectName("block6");
    block6->SetTranslation(vector2{ 300.f, -1200.f });
    block6->SetScale(vector2{ 10.f, 400.f });
    block6->AddComponent(new Sprite(block6));
    block6->AddComponent(new Physics(block6));
    block6->SetDepth(-1.f);

    block7 = new Object();
    block7->SetObjectType(Object::ObjectType::OBSTACLE);
    block7->SetObjectName("block7");
    block7->SetTranslation(vector2{ -1000.f, -350.f });
    block7->SetScale(vector2{ 1300.f, 10.f });
    block7->AddComponent(new Sprite(block7));
    block7->AddComponent(new Physics(block7));
    block7->SetDepth(-1.f);

    block8 = new Object();
    block8->SetObjectType(Object::ObjectType::OBSTACLE);
    block8->SetObjectName("block8");
    block8->SetTranslation(vector2{ 425.f, -1400.f });
    block8->SetScale(vector2{ 250.f, 10.f });
    block8->AddComponent(new Sprite(block8));
    block8->AddComponent(new Physics(block8));
    block8->SetDepth(-1.f);

    block9 = new Object();
    block9->SetObjectType(Object::ObjectType::OBSTACLE);
    block9->SetObjectName("block9");
    block9->SetTranslation(vector2{ 900.f, -1400.f });
    block9->SetScale(vector2{ 200.f, 10.f });
    block9->AddComponent(new Sprite(block9));
    block9->AddComponent(new Physics(block9));
    block9->SetDepth(-1.f);

    //========================================================================

    block10 = new Object();
    block10->SetObjectType(Object::ObjectType::OBSTACLE);
    block10->SetObjectName("block10");
    block10->SetTranslation(vector2{ 900.f, -1000.f });
    block10->SetScale(vector2{ 750.f, 10.f });
    block10->AddComponent(new Sprite(block10));
    block10->AddComponent(new Physics(block10));
    block10->SetDepth(-1.f);

    block11 = new Object();
    block11->SetObjectType(Object::ObjectType::OBSTACLE);
    block11->SetObjectName("block11");
    block11->SetTranslation(vector2{ 500.f, -700.f });
    block11->SetScale(vector2{ 10.f, 600.f });
    block11->AddComponent(new Sprite(block11));
    block11->AddComponent(new Physics(block11));
    block11->SetDepth(-1.f);

    block12 = new Object();
    block12->SetObjectType(Object::ObjectType::OBSTACLE);
    block12->SetObjectName("block12");
    block12->SetTranslation(vector2{ 625.f, -300.f });//´úÇÔ¿ä
    block12->SetScale(vector2{ 150.f, 10.f });
    block12->AddComponent(new Sprite(block12));
    block12->AddComponent(new Physics(block12));
    block12->SetDepth(-1.f);

    block13 = new Object();
    block13->SetObjectType(Object::ObjectType::OBSTACLE);
    block13->SetObjectName("block13");
    block13->SetTranslation(vector2{ 925.f, -300.f });
    block13->SetScale(vector2{ 150.f, 10.f });
    block13->AddComponent(new Sprite(block13));
    block13->AddComponent(new Physics(block13));
    block13->SetDepth(-1.f);


    //=============================   OBJECTS   ====================================
    moveBox1 = new Object();
    moveBox1->SetObjectType(Object::ObjectType::OBSTACLE);
    moveBox1->SetObjectName("moveBox1");
    moveBox1->SetTranslation(vector2{ 600.f, -1400.f });
    moveBox1->SetScale(vector2{ 200.f });
    moveBox1->AddComponent(new Sprite(moveBox1));
    moveBox1->AddComponent(new Physics(moveBox1));
    moveBox1->SetDepth(-1.f);

    lock = new Object();
    lock->SetObjectType(Object::ObjectType::OBSTACLE);
    lock->SetObjectName("lock");
    lock->SetTranslation(vector2{ 600.f, -1400.f });
    lock->SetScale(vector2{ 150.f });
    lock->AddComponent(new Sprite(lock));
    lock->AddComponent(new Physics(lock));
    lock->SetDepth(-1.f);




//============================================================================
    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(string);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);

    //================================   BLOCKS   ===================================
    objManager->FindLayer(LayerNames::Stage)->AddObject(block1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block4);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block5);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block6);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block7);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block8);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block9);

    //=============================   OBJECTS   ====================================
    objManager->FindLayer(LayerNames::Stage)->AddObject(moveBox1);

    //===========================================================================
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

}