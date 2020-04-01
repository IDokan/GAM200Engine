/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TutorialLevel1.cpp
Author
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 03.15.2020
******************************************************************************/

#include <Scenes/TutorialLevel1.hpp>
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


TutorialLevel1::TutorialLevel1() : background(nullptr)
{
}

TutorialLevel1::~TutorialLevel1()
{
}

void TutorialLevel1::Load()
{
    fileIO* fileio = new fileIO;
    fileio->Input("../assets/fileIO/tutorialLevelFile1.txt", &player1, &player2, &string);

    TutorialLevel1::InitObject();

    cameraManager.Init(player1, player2);
}

void TutorialLevel1::Update(float /*dt*/)
{
    player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
    player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();

    TutorialLevel1::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);
    
    cameraManager.CameraMove(player1, player2, 1.1f);
}

void TutorialLevel1::GameRestart()
{
}

void TutorialLevel1::Unload()
{
    fileIO* a = 0;
    a->Output("../assets/fileIO/savedTutorial1.txt");
}

void TutorialLevel1::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void TutorialLevel1::InitObject() {
    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 1.f });
    background->SetScale(vector2{ 960.f,800.f });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

    goalPoint = new Object();
    goalPoint->SetObjectType(Object::ObjectType::TEST);
    goalPoint->SetObjectName("goalPoint");
    goalPoint->SetTranslation(vector2{ 480.f, -400.f });
    goalPoint->SetScale(vector2{ 150.f });
    goalPoint->AddComponent(new Sprite(goalPoint));
    goalPoint->AddComponent(new Physics(goalPoint));
    goalPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(goalPoint, Physics::ObjectType::RECTANGLE);
    goalPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
    goalPoint->SetDepth(-1.f);

    startPoint = new Object();
    startPoint->SetObjectType(Object::ObjectType::TEST);
    startPoint->SetObjectName("startPoint");
    startPoint->SetTranslation(vector2{ -480.f, -400.f });
    startPoint->SetScale(vector2{ 150.f });
    startPoint->AddComponent(new Sprite(startPoint));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
    startPoint->SetDepth(-1.f);

    Object* pushingObj = new Object();
    pushingObj->SetObjectName("pushing Test");
    pushingObj->SetTranslation(vector2{ 0.f, 200.f });
    pushingObj->SetScale(vector2{ 150.f });
    pushingObj->AddComponent(new Physics(pushingObj));
    pushingObj->SetObjectType(Object::ObjectType::MOVING_OBJECT);
    Physics* pushingPhysics = pushingObj->GetComponentByTemplate<Physics>();
    pushingPhysics->SetObjectCollidingSide(Physics::ObjectSide::LEFT_SIDE);
    pushingPhysics->SetCollisionBoxAndObjectType(pushingObj, Physics::ObjectType::RECTANGLE);
    pushingObj->AddComponent(new Sprite(pushingObj));
    pushingObj->SetDepth(-0.5f);

    auto objManager = ObjectManager::GetObjectManager();

    objManager->FindLayer(LayerNames::Stage)->AddObject(pushingObj);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);

}