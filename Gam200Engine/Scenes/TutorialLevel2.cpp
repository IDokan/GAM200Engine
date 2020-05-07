/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TutorialLevel2.cpp
Author
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 03.15.2020
******************************************************************************/

#include <Scenes/TutorialLevel2.hpp>
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
#include <Object/Points/GoalPoint.hpp>
//lock and key
#include<Systems/MessageSystem/Message.hpp>
#include<Systems/MessageSystem/MessageDispatcher.hpp>
#include<Component/MessageCapable.hpp>

TutorialLevel2::TutorialLevel2() : background(nullptr)
{
}

TutorialLevel2::~TutorialLevel2()
{
}

void TutorialLevel2::Load()
{
    fileIO* fileio = new fileIO;
    fileio->Input("../assets/fileIO/tutorialLevelFile2.txt", &player1, &player2, &string);

    TutorialLevel2::InitObject();

    cameraManager.Init(player1, player2);
}

void TutorialLevel2::Update(float dt)
{
    static bool unLock1 = false;
    static bool unLock2 = false;
    if (!unLock1)
        if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(key1)
            || player2->GetComponentByTemplate<Physics>()->IsCollideWith(key1))
        {
            MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Key1, MessageObjects::Lock1, MessageTypes::GetKey, 0, 0);
            key1->SetDead(true);
            unLock1 = true;
        }
    if (!unLock2)
        if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(key2)
            || player2->GetComponentByTemplate<Physics>()->IsCollideWith(key2))
        {
            MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Key2, MessageObjects::Lock2, MessageTypes::GetKey, 0, 0);
            key2->SetDead(true);
            unLock2 = true;
        }

    player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
    player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();

    TutorialLevel2::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(dt, player1, player2, 1.1f);
}

void TutorialLevel2::GameRestart()
{
}

void TutorialLevel2::Unload()
{
        //fileIO* a = 0;
        //a->Output("../assets/fileIO/tutorialLevelFile2.txt");
}

void TutorialLevel2::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void TutorialLevel2::InitObject() {
    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 1.f });
    background->SetScale(vector2{ 960.f,800.f });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");


    Transform goalTransform;
    goalTransform.SetTranslation(vector2{ 480.f, 400.f });
    goalTransform.SetScale(vector2{ 200.f });
    goalPoint = new GoalPoint(goalTransform, player1);
    Object* goalPoint2 = new GoalPoint(goalTransform, player2);

    startPoint = new Object();
    startPoint->SetObjectType(Object::ObjectType::TEST);
    startPoint->SetObjectName("startPoint");
    startPoint->SetTranslation(vector2{ -480.f, 400.f });
    startPoint->SetScale(vector2{ 100.f });
    startPoint->AddComponent(new Sprite(startPoint));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
    startPoint->SetDepth(-1.f);

    key1 = new Object();
    key1->SetObjectName("key1");
    key1->SetTranslation(vector2{ -300.f,-50.f });
    key1->SetObjectType(Object::ObjectType::KEY_1);
    key1->SetScale(vector2{ 75.f });
    key1->AddComponent(new Sprite(key1));
    key1->AddComponent(new Physics(key1));
    key1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/key1.png");
    key1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(key1, Physics::ObjectType::CIRCLE);
    key1->SetDepth(-1.f);

    key2 = new Object();
    key2->SetObjectName("key2");
    key2->SetTranslation(vector2{-50.f, 50.f });
    key2->SetObjectType(Object::ObjectType::KEY_2);
    key2->SetScale(vector2{ 75.f });
    key2->AddComponent(new Sprite(key2));
    key2->AddComponent(new Physics(key2));
    key2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/key2.png");
    key2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(key2, Physics::ObjectType::CIRCLE);
    key2->SetDepth(-1.f);

    lock1 = new Object();
    lock1->SetObjectName("lock1");
    lock1->SetTranslation(vector2{ -100.f, -250.f });
    lock1->SetObjectType(Object::ObjectType::LOCK_1);
    lock1->SetScale(85.f);
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
    lock2->SetTranslation(vector2{ 240.f, 300.f });
    lock2->SetObjectType(Object::ObjectType::LOCK_2);
    lock2->SetScale(85.f);
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

    objManager->FindLayer(LayerNames::Stage)->AddObject(key1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(lock1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(key2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(lock2);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint2);

}