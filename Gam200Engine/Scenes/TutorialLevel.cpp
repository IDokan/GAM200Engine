/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.cpp
Author
    - Hyerin.Jung       junghl0621@gmail.com

Creation Date: 02.11.2020

    Source file for level that player learned how to move player
******************************************************************************/
#include <Scenes/TutorialLevel.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>
#include <Object/Players/Player.h>
//lock and key
#include<Systems/MessageSystem/Message.hpp>
#include<Systems/MessageSystem/MessageDispatcher.hpp>
#include<Component/MessageCapable.hpp>



TutorialLevel::TutorialLevel() : background(nullptr)
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::Load()
{
    fileIO* a = 0;
    a->Input("../assets/fileIO/savedTutorial.txt");

    TutorialLevel::InitObject();

    cameraManager.Init();
    //TestBGMSoundForDebugMode.Load_Sound();
    //TestBGMSoundForDebugMode.Play_Sound(SOUNDS::BACKGROUND_SOUND);
    //TestBGMSoundForDebugMode.SetVolume(BACKGROUND_SOUND, 0.2f);

}

void TutorialLevel::Update(float /*dt*/)
{
    TutorialLevel::Input();

    static bool unLock1 = false;
    static bool unLock2 = false;
    if (!unLock1)
        if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(key1)
            || player2->GetComponentByTemplate<Physics>()->IsCollideWith(key1))
        {
            MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Key1, MessageObjects::Lock1, MessageTypes::GetKey, 0, 0);
            key1->SetDead(true);
            unLock1= true;
        }
    if(!unLock2)
    if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(key2)
        || player2->GetComponentByTemplate<Physics>()->IsCollideWith(key2))
    {
        MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Key2, MessageObjects::Lock2, MessageTypes::GetKey, 0, 0);
        key2->SetDead(true);
        unLock2 = true;
    }

    TutorialLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(player1, player2, 1.1f);
}

void TutorialLevel::GameRestart()
{
}

void TutorialLevel::Unload()
{
    fileIO* a = 0;
    a->Output("../assets/fileIO/savedTutorial.txt");
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
   
    player1 = new Player(Player::Identifier::Player1);
    player2 = new Player(Player::Identifier::Player2);
    string = new String(player1, player2);

    key1 = new Object();
    key1->SetObjectName("key1");
    key1->SetTranslation(vector2{ 100.f,1450.f });
    key1->SetObjectType(Object::ObjectType::KEY_1);
    key1->SetScale(vector2{ 100.f });
    key1->AddComponent(new Sprite(key1));
    key1->AddComponent(new Physics(key1));
    key1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/key1.png");
    key1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(key1, Physics::ObjectType::CIRCLE);
    key1->SetDepth(-1.f);

    key2 = new Object();
    key2->SetObjectName("key2");
    key2->SetTranslation(vector2{ -800.f, 600.f });
    key2->SetObjectType(Object::ObjectType::KEY_2);
    key2->SetScale(vector2{ 100.f });
    key2->AddComponent(new Sprite(key2));
    key2->AddComponent(new Physics(key2));
    key2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/key2.png");
    key2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(key2, Physics::ObjectType::CIRCLE);
    key2->SetDepth(-1.f);
    
    lock1 = new Object();
    lock1->SetObjectName("lock1");
    lock1->SetTranslation(vector2{ 600.f, 1050.f });
    lock1->SetObjectType(Object::ObjectType::LOCK_1);
    lock1->SetScale(100.f);
    lock1->AddComponent(new Sprite(lock1));
    lock1->AddComponent(new Physics(lock1));
    lock1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/lock1.png");
    lock1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(lock1, Physics::ObjectType::CIRCLE);
    lock1->SetDepth(-1.f);
    lock1->AddComponent(new MessageCapable(lock1, MessageObjects::Lock1, [&](const Message& msg)->bool
    {
        switch (msg.Msg)
        {
        case MessageTypes::GetKey:
            lock1->SetDead(true);
            break;
        default:
            return false;
        }
        return true;
    }));

    lock2 = new Object();
    lock2->SetObjectName("lock2");
    lock2->SetTranslation(vector2{ 760.f,400.f });
    lock2->SetObjectType(Object::ObjectType::LOCK_2);
    lock2->SetScale(100.f);
    lock2->AddComponent(new Sprite(lock2));
    lock2->AddComponent(new Physics(lock2));
    lock2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/lock2.png");
    lock2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(lock2, Physics::ObjectType::CIRCLE);
    lock2->SetDepth(-1.f);
    lock2->AddComponent(new MessageCapable(lock2, MessageObjects::Lock2, [&](const Message& msg)->bool
    {
        switch (msg.Msg)
        {
        case MessageTypes::GetKey:
            lock2->SetDead(true);
            break;
        default:
            return false;
        }
        return true;
    }));


    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(Stage)->AddObject(string);

    objManager->FindLayer(LayerNames::Stage)->AddObject(key1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(lock1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(key2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(lock2);

}