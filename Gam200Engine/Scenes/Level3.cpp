/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Level3.cpp
Author
    -  jaemin.woo wjm9932@gmail.com
Creation Date: 03.13.2020

    Header file for scene which works as Level3
******************************************************************************/

#include <Scenes/Level3.hpp>
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
#include <Object/DepthStandard.hpp>
#include <Object/InteractiveObject/CrushableObject.hpp>
#include <Component/Sprite/TextComponent.hpp>
#include <Graphics/StockBitmapFonts.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>
#include <Component/Scripts/Hostage.hpp>
#include <Object/Mouse/Mouse.hpp>

Level3::Level3() : background(nullptr)
{
}

Level3::~Level3()
{
}

void Level3::Load()
{
    fileIO* fileio = new fileIO;
    fileio->Input("../assets/fileIO/Level3.txt", &player1, &player2, &string);

    Level3::InitObject();
    cameraManager.Init(player1, player2);
    sceneStateManager->SetNameOfSelectedLevel("Level4");
}

void Level3::Update(float dt)
{

    player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
    player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();

    Level3::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(dt, player1, player2, 1.1f);
}

void Level3::GameRestart()
{
}


void Level3::Unload()
{
}

void Level3::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void Level3::InitObject()
{
    Object* ground = new Object();
    ground->SetObjectName("Ground");
    ground->SetTranslation(vector2{ 950.f, 1150.f });
    ground->SetScale(vector2{ 3900.f, 1800.f });
    Sprite* groundSprite = new Sprite(ground);
    groundSprite->SetImage("../assets/textures/Ground_Background.png");
    ground->AddComponent(groundSprite);
    vector2 scale = ground->GetScale();
    groundSprite->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground->SetDepth(Depth_Standard::Background);

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 1140.f,1000.f });
    background->SetScale(vector2{ 10000.f });
    background->AddComponent(new Sprite(background));
    background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(50.f);
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/background.png");
    background->SetDepth(Depth_Standard::FurtherBackground);

    Mouse* mouse = new Mouse(vector2{ 180, 900 }, vector2{ 180, 1250 }, vector2{ 180, 384 }, player1, player2);
    mouse->SetSpeed(1.5f);
    Mouse* mouse1 = new Mouse(vector2{ 1800, 1260 }, vector2{ 1300, 1260 }, vector2{ 2457, 1260 }, player1, player2);
    Mouse* mouse2 = new Mouse(vector2{ 1800, 350 }, vector2{ 1300, 350 }, vector2{ 2457, 350 }, player1, player2);

    cheese = new Object();
    cheese->SetObjectType(Object::ObjectType::SavedCheese);
    cheese->SetObjectName("cheese");
    cheese->SetTranslation(vector2{ 650.f, 1700.f });
    cheese->SetScale(vector2{ 80.f, 80.f });
    Animation* getAnimationComponenet = new Animation(cheese);
    getAnimationComponenet->SetFrame(6);
    getAnimationComponenet->SetSpeed(5.f);
    cheese->AddComponent(getAnimationComponenet);
    cheese->AddComponent(new Physics(cheese));
    cheese->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    cheese->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(cheese, Physics::ObjectType::RECTANGLE);
    cheese->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/SavedCheese.png");
    cheese->AddComponent(new Hostage(cheese, player1, player2));
    cheese->SetDepth(Depth_Standard::SavedCheese);

    jail = new CrushableObject(vector2{ 650.f, 1700.f }, vector2{ 120.f, 120.f }, Physics::ObjectType::RECTANGLE, string);
    jail->SetDepth(Depth_Standard::Jail);
    jail->SetObjectName("jail");

    Transform goalTransform;
    goalTransform.SetTranslation(vector2{ 2650, 1810 });
    goalTransform.SetScale(vector2{ 200, 200 });
    GoalPoint* goalPoint1 = new GoalPoint(goalTransform, player1, player2);

    button1 = new DoorSystem(player1, player2, vector2{ -790.f, 500.f }, vector2{ 100.f, 100.f }, vector2{ -790.f, 910.f }, vector2{ 100.f, 100.f }, vector2{ -2795.f,1655.f }, vector2{ 250.f,100.f }, vector2{ -615.f, 1208.f }, vector2{ 100.f,275.f });
    button1->SetButtonAndDoorColor({ 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f });
    button1->SetButtonAndDoorName("button1", "button2,", "door1", "door2");

    button2 = new DoorSystem(player1, player2, vector2{ 180.f, 600.f }, vector2{ 100.f, 100.f }, vector2{ 550.f, 600.f }, vector2{ 100.f, 100.f }, vector2{ 415.f,815.f }, vector2{ 100.f, 260.f }, vector2{ 798.f, 360.f }, vector2{ 100.f, 180.f }, true);
    button2->SetButtonAndDoorColor({ 0.31f, 0.73f, 0.87f, 1.0f }, { 0.31f, 0.73f, 0.87f, 1.0f }, { 0.31f, 0.73f, 0.87f, 0.2f }, { 0.31f, 0.73f, 0.87f, 1.0f });
    button2->SetButtonAndDoorName("button3", "button4", "door3", "door4");

    button3 = new DoorSystem(player1, player2, vector2{ 1060.f, 720.f }, vector2{ 100.f, 100.f }, vector2{ 1340.f, 500.f }, vector2{ 100.f, 100.f }, vector2{ 899.f,360.f }, vector2{ 100.f,175.f }, vector2{ 1405.f, 1400.f }, vector2{ 280.f, 100.f });
    button3->SetButtonAndDoorColor({ 0.3f, 0.3f, 0.3f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f }, { 0.3f, 0.3f, 0.3f, 0.2f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    button3->SetButtonAndDoorName("button5", "button6,", "door5", "door6");

    button4 = new DoorSystem(player1, player2, vector2{ 1890.f, 1570.f }, vector2{ 100.f, 100.f }, vector2{ 2447.f, 1400.f }, vector2{ 380.f, 100.f }, false);
    button4->SetButtonAndDoorColor({ 0.6f, 0.0f, 0.0f, 1.0f }, { 0.6f, 0.0f, 0.0f, 1.0f });
    button4->SetButtonAndDoorName("button7", "door7");

    movingObject1 = new Object();
    movingObject1->SetObjectType(Object::ObjectType::MOVING_OBJECT);
    movingObject1->SetObjectName("movingObject1");
    movingObject1->SetTranslation(vector2{ -790.f, 500.f });
    movingObject1->SetScale(vector2{ 100.f, 100.f });
    movingObject1->AddComponent(new Sprite(movingObject1));
    movingObject1->AddComponent(new Physics(movingObject1));
    movingObject1->GetComponentByTemplate<Physics>()->SetObjectCollidingSide(Physics::ObjectSide::UP_SIDE);
    movingObject1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(movingObject1, Physics::ObjectType::RECTANGLE);
    movingObject1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/moving_object_DOWN.png");
    movingObject1->SetDepth(Depth_Standard::Obstacle);

    auto objManager = ObjectManager::GetObjectManager();


    objManager->FindLayer(BackGround)->AddObject(ground);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button4);
    objManager->FindLayer(LayerNames::Stage)->AddObject(movingObject1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(jail);
    objManager->FindLayer(LayerNames::Stage)->AddObject(cheese);
}
