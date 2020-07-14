/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  Level4.cpp
Author
    - Jiwon.Jung       jjwon6218@gmail.com
    - Jaemin Woo    wjm9932@gmail.com

Creation Date: 05.10.2020

    Source file for 4th level
******************************************************************************/
#include <Scenes/Level4.hpp>
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
#include <Object/Points/CheckPoint.hpp>
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
#include <Scenes/SceneManager.hpp>

Level4::Level4() : background(nullptr)
{
}

Level4::~Level4()
{
}

void Level4::Load()
{
    fileIO* fileio = new fileIO;
    fileio->Input("../assets/fileIO/Level4.txt", &player1, &player2, &string);
    Level4::InitObject();
    cameraManager.Init(player1, player2);
    sceneStateManager->SetNameOfSelectedLevel("TutorialLevel");

    //BGM
    SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(SOUNDS::BACKGROUND_SOUND2);
    SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(SOUNDS::BACKGROUND_SOUND2, 0.7f);

    current_scene_info = GameScenes::Level5;
}

void Level4::Update(float dt)
{
    player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
    player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();

    Level4::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(dt, player1, player2, 1.1f);
}

void Level4::GameRestart()
{
    button1->ReinitializeDoors();
    button2->ReinitializeDoors();
    button3->ReinitializeDoors();
    button4->ReinitializeDoors();
}

void Level4::Unload()
{
}

void Level4::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void Level4::InitObject()
{
    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 330.f,1880.f });
    background->SetScale(vector2{ 10000.f });
    background->AddComponent(new Sprite(background));
    background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(50.f);
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/background.png");
    background->SetDepth(Depth_Standard::FurtherBackground);

    Object* ground = new Object();
    ground->SetObjectName("Ground");
    ground->SetTranslation(vector2{ -100.f, 2970.f });
    ground->SetScale(vector2{ 1500.f, 800.f });
    Sprite* groundSprite = new Sprite(ground);
    groundSprite->SetImage("../assets/textures/Ground_Background.png");
    ground->AddComponent(groundSprite);
    vector2 scale = ground->GetScale();
    groundSprite->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground->SetDepth(Depth_Standard::Background);

    Object* ground1 = new Object();
    ground1->SetObjectName("Ground1");
    ground1->SetTranslation(vector2{ -155.f, 1486.f });
    ground1->SetScale(vector2{ 1210.f, 1550.f });
    Sprite* groundSprite1 = new Sprite(ground1);
    groundSprite1->SetImage("../assets/textures/Ground_Background.png");
    ground1->AddComponent(groundSprite1);
    scale = ground1->GetScale();
    groundSprite1->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground1->SetDepth(Depth_Standard::Background);

    Object* ground2 = new Object();
    ground2->SetObjectName("Ground2");
    ground2->SetTranslation(vector2{ 1180.f, 1770.f });
    ground2->SetScale(vector2{ 600.f, 1000.f });
    Sprite* groundSprite2 = new Sprite(ground2);
    groundSprite2->SetImage("../assets/textures/Ground_Background.png");
    ground2->AddComponent(groundSprite2);
    scale = ground2->GetScale();
    groundSprite2->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground2->SetDepth(Depth_Standard::Background);

    Object* ground3 = new Object();
    ground3->SetObjectName("Ground3");
    ground3->SetTranslation(vector2{ 700.f, 2160.f });
    ground3->SetScale(vector2{ 600.f, 225.f });
    Sprite* groundSprite3 = new Sprite(ground3);
    groundSprite3->SetImage("../assets/textures/Ground_Background.png");
    ground3->AddComponent(groundSprite3);
    scale = ground3->GetScale();
    groundSprite3->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground3->SetDepth(Depth_Standard::Background);

    Object* ground4 = new Object();
    ground4->SetObjectName("Ground4");
    ground4->SetTranslation(vector2{ 1370.f, 900.f });
    ground4->SetScale(vector2{ 875.f, 365.f });
    Sprite* groundSprite4 = new Sprite(ground4);
    groundSprite4->SetImage("../assets/textures/Ground_Background.png");
    ground4->AddComponent(groundSprite4);
    scale = ground4->GetScale();
    groundSprite4->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground4->SetDepth(Depth_Standard::Background);

    Object* ground5 = new Object();
    ground5->SetObjectName("Ground5");
    ground5->SetTranslation(vector2{ 1000.f, 1170.f });
    ground5->SetScale(vector2{ 200.f, 230.f });
    Sprite* groundSprite5 = new Sprite(ground5);
    groundSprite5->SetImage("../assets/textures/Ground_Background.png");
    ground5->AddComponent(groundSprite5);
    scale = ground5->GetScale();
    groundSprite5->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground5->SetDepth(Depth_Standard::Background);

    Object* ground6 = new Object();
    ground6->SetObjectName("Ground6");
    ground6->SetTranslation(vector2{ -1350.f, 1660.f });
    ground6->SetScale(vector2{ 800.f, 2500.f });
    Sprite* groundSprite6 = new Sprite(ground6);
    groundSprite6->SetImage("../assets/textures/Ground_Background.png");
    ground6->AddComponent(groundSprite6);
    scale = ground6->GetScale();
    groundSprite6->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground6->SetDepth(Depth_Standard::Background);

    Object* ground7 = new Object();
    ground7->SetObjectName("Ground7");
    ground7->SetTranslation(vector2{ -900.f, 1600.f });
    ground7->SetScale(vector2{ 300.f, 100.f });
    Sprite* groundSprite7 = new Sprite(ground7);
    groundSprite7->SetImage("../assets/textures/Ground_Background.png");
    ground7->AddComponent(groundSprite7);
    scale = ground7->GetScale();
    groundSprite7->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground7->SetDepth(Depth_Standard::Background);

    Object* ground8 = new Object();
    ground8->SetObjectName("Ground8");
    ground8->SetTranslation(vector2{ -780.f, 2300.f });
    ground8->SetScale(vector2{ 360.f, 1150.f });
    Sprite* groundSprite8 = new Sprite(ground8);
    groundSprite8->SetImage("../assets/textures/Ground_Background.png");
    ground8->AddComponent(groundSprite8);
    scale = ground8->GetScale();
    groundSprite8->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
    ground8->SetDepth(Depth_Standard::Background);

    button1 = new DoorSystem(player1, player2, vector2{ 390.f, 1610.f }, vector2{ 70.f, 70.f }, vector2{ 418.f, 1260.f }, vector2{ 50.f, 50.f }, vector2{ 500.f,2175.f }, vector2{ 100.f,145.f }, vector2{ -680.f, 1255.f }, vector2{ 135.f,100.f });
    button1->SetButtonAndDoorColor({ 1.0f, 0.f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 0.2f }, { 1.0f, 0.0f, 0.0f, 1.0f });
    button1->SetButtonAndDoorName("button1", "button2,", "door1", "door2");

    button2 = new DoorSystem(player1, player2, vector2{ -160.f, 935.f }, vector2{ 70.f,70.f }, vector2{ -680.f, 2300.f }, vector2{ 135.f, 100.f }, false);
    button2->SetButtonAndDoorColor({ 0.54f, 0.f, 1.0f, 1.0f }, { 0.54f, 0.f, 1.0f, 1.0f });
    button2->SetButtonAndDoorName("button3", "door3");

    jail1 = new CrushableObject(vector2{ -160.f, 935.f }, vector2{ 100.f, 100.f }, Physics::ObjectType::RECTANGLE, string);
    jail1->SetDepth(Depth_Standard::Jail);
    jail1->SetObjectName("jail1");

    button3 = new DoorSystem(player1, player2, vector2{ -80.f, 3030.f }, vector2{ 70.f,70.f }, vector2{ 1000.f, 1240.f }, vector2{ 110.f, 100.f }, false);
    button3->SetButtonAndDoorColor({ 0.f, 1.f, 0.0f, 1.0f }, { 0.f, 1.f, 0.0f, 1.0f });
    button3->SetButtonAndDoorName("button4", "door4");

    jail2 = new CrushableObject(vector2{ -80.f, 3030.f }, vector2{ 100.f, 100.f }, Physics::ObjectType::RECTANGLE, string);
    jail2->SetDepth(Depth_Standard::Jail);
    jail2->SetObjectName("jail2");

    button4 = new DoorSystem(player1, player2, vector2{ -1410.f, 750.f }, vector2{ 70.f, 70.f }, vector2{ -1695.f, 2075.f }, vector2{ 100.f, 90.f }, false);
    button4->SetButtonAndDoorColor({ 0.58f, 0.29f, 0.0f, 1.0f }, { 0.58f, 0.29f, 0.0f, 1.0f });
    button4->SetButtonAndDoorName("button5", "door5");

    jail3 = new CrushableObject(vector2{ -1410.f, 750.f }, vector2{ 100.f, 100.f }, Physics::ObjectType::RECTANGLE, string);
    jail3->SetDepth(Depth_Standard::Jail);
    jail3->SetObjectName("jail3");

    cheese = new Object();
    cheese->SetObjectType(Object::ObjectType::SavedCheese);
    cheese->SetObjectName("cheese");
    cheese->SetTranslation(vector2{ 1390.f, 890.f });
    cheese->SetScale(vector2{ 50.f, 50.f });
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

    jail4 = new CrushableObject(vector2{ 1390.f, 890.f }, vector2{ 100.f, 100.f }, Physics::ObjectType::RECTANGLE, string);
    jail4->SetDepth(Depth_Standard::Jail);
    jail4->SetObjectName("jail4");

    Transform goalTransform;
    goalTransform.SetTranslation(vector2{ -1310, 2500 });
    goalTransform.SetScale(vector2{ 200, 200 });
    GoalPoint* goalPoint1 = new GoalPoint(goalTransform, player1, player2);

    Mouse* mouse1 = new Mouse(vector2{ -665, 1465 }, vector2{ -665, 1465 }, vector2{ 375, 1465 }, player1, player2);
    Mouse* mouse2 = new Mouse(vector2{ 375, 2165 }, vector2{ 375, 2165 }, vector2{ -665, 2165 }, player1, player2);
    Mouse* mouse3 = new Mouse(vector2{ -665, 1075 }, vector2{ -665, 1075 }, vector2{ 375, 1075 }, player1, player2);
    Mouse* mouse4 = new Mouse(vector2{ 500, 2745 }, vector2{ 500, 2745 }, vector2{ -665, 2745 }, player1, player2);
    Mouse* mouse5 = new Mouse(vector2{ 1000, 2050 }, vector2{ 1000, 2050 }, vector2{ 1000, 1360 }, player1, player2);
    Mouse* mouse6 = new Mouse(vector2{ -1120, 1960 }, vector2{ -1120, 1960 }, vector2{ -1120, 1220 }, player1, player2);
    Mouse* mouse7 = new Mouse(vector2{ -1660, 1220 }, vector2{ -1660, 1220 }, vector2{ -1660, 1960 }, player1, player2);

    CheckPoint* checkPoint1 = new CheckPoint((player1->GetTranslation() + player2->GetTranslation()) / 2.f, player1, player2);
    checkPoint1->SetObjectName("CheckPoint1");
    lastCheckPoint = checkPoint1;

    CheckPoint* checkPoint2 = new CheckPoint(vector2{ 1000.f }, player1, player2);
    checkPoint2->SetObjectName("CheckPoint2");

    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(ground);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(ground1);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(ground2);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(ground3);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(ground4);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(ground5);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(ground6);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(ground7);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(ground8);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button4);
    objManager->FindLayer(LayerNames::Stage)->AddObject(cheese);
    objManager->FindLayer(LayerNames::Stage)->AddObject(jail1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(jail2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(jail3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(jail4);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse4);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse5);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse6);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse7);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(checkPoint1);
}
