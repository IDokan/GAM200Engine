/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Level2.cpp
Author
    - Jiwon Jung jjwon6218@gmail.com
    - Jaemin woo wjm9932@gmail.com

Creation Date: 07.11.2020
******************************************************************************/

#include <Scenes/Level2.hpp>
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

Level2::Level2() : background(nullptr)
{
}

Level2::~Level2()
{
}

void Level2::Load()
{
    fileIO* fileio = new fileIO;
    fileio->Input("../assets/fileIO/Level2.txt", &player1, &player2, &string);

    Level2::InitObject();

    cameraManager.Init(player1, player2);
    sceneStateManager->SetNameOfSelectedLevel("Level3");

    SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(SOUNDS::BACKGROUND_SOUND);
    SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(SOUNDS::BACKGROUND_SOUND, 0.2f);
    current_scene_info = GameScenes::Level2;
}

void Level2::Update(float dt)
{
    player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
    player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();

    Level2::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(dt, player1, player2, 1.1f);
}

void Level2::GameRestart()
{
    button1->ReinitializeDoors();
    button2->ReinitializeDoors();
}

void Level2::Unload()
{
    SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().UnLoad_Sound();
}

void Level2::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void Level2::InitObject()
{
    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ -260.f, 0.f });
    background->SetScale(vector2{ 2700.f,950.f });
    background->AddComponent(new Sprite(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/Ground_Background.png");
    vector2 scale = background->GetScale();
    background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(vector2{ scale.x / 780.f, scale.y / 800.f });
    background->SetDepth(Depth_Standard::Background);

    background1 = new Object();
    background1->SetObjectName("background2");
    background1->SetTranslation(vector2{ 210.f, 850.f });
    background1->SetScale(vector2{ 1800.f,750.f });
    background1->AddComponent(new Sprite(background1));
    background1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/Ground_Background.png");
    vector2 scale1 = background1->GetScale();
    background1->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(vector2{ scale1.x / 780.f, scale1.y / 800.f });
    background1->SetDepth(Depth_Standard::Background);

    Object* outGround;
    outGround = new Object();
    outGround->SetObjectName("outGround");
    outGround->SetTranslation(vector2{ 1.f });
    outGround->SetScale(vector2{ 10000.f });
    outGround->AddComponent(new Sprite(outGround));
    outGround->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(50.f);
    outGround->AddComponent(new Physics(outGround));
    outGround->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/background.png");
    outGround->SetDepth(Depth_Standard::FurtherBackground);

    button1 = new DoorSystem(player1, player2, vector2{ -220.f, 230.f }, vector2{ 100.f, 100.f }, vector2{ -220.f, -230.f }, vector2{ 100.f, 100.f }, vector2{ -660.f, 0.f }, vector2{ 100.f, 120.f }, vector2{ 175.f, 0.f }, vector2{ 50.f, 120.f }, true);
    button1->SetButtonAndDoorColor({ 0.31f, 0.73f, 0.87f, 1.0f }, { 0.31f, 0.73f, 0.87f, 1.0f }, { 0.31f, 0.73f, 0.87f, 0.2f }, { 0.31f, 0.73f, 0.87f, 1.0f });
    button1->SetButtonAndDoorName("button1", "button2", "door1", "door2");

    button2 = new DoorSystem(player1, player2, vector2{ 925.f, 210.f }, vector2{ 100.f, 100.f }, vector2{ 925.f, -210.f }, vector2{ 100.f, 100.f }, vector2{ 225.f, 0.f }, vector2{ 50.f, 120.f }, vector2{ 580.f, 440.f }, vector2{ 230.f, 100.f });
    button2->SetButtonAndDoorColor({ 1.f, 0.f, 0.f, 1.0f }, { 1.f, 0.f, 0.f, 1.0f }, { 1.f, 0.f, 0.f, 0.2f }, { 1.f, 0.f, 0.f, 1.0f });
    button2->SetButtonAndDoorName("button3", "button4", "door3", "door4");

    Mouse* mouse = new Mouse(vector2{ -540, 0 }, vector2{ -540, 0 }, vector2{ 70, 0 }, player1, player2);
    Mouse* mouse1 = new Mouse(vector2{ 360, 1040 }, vector2{ 360, 1040 }, vector2{ 360, 610 }, player1, player2);

    CheckPoint* checkPoint1 = new CheckPoint((player1->GetTranslation() + player2->GetTranslation()) / 2.f, player1, player2);
    checkPoint1->SetObjectName("CheckPoint1");
    lastCheckPoint = checkPoint1;

    CheckPoint* checkPoint2 = new CheckPoint(vector2{ 500.f, 0.f }, player1, player2);
    checkPoint2->SetObjectName("CheckPoint2");

    Transform goalTransform;
    goalTransform.SetTranslation(vector2{ 640, 840 });
    goalTransform.SetScale(vector2{ 200, 200 });
    GoalPoint* goalPoint1 = new GoalPoint(goalTransform, player1, player2);

    cheese = new Object();
    cheese->SetObjectType(Object::ObjectType::SavedCheese);
    cheese->SetObjectName("cheese");
    cheese->SetTranslation(vector2{ -230.f, 750.f });
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

    Object* jail = new CrushableObject(vector2{ -230.f, 750.f }, vector2{ 120.f, 120.f }, Physics::ObjectType::RECTANGLE, string);
    jail->SetDepth(Depth_Standard::Jail);
    jail->SetObjectName("jail");

    auto objManager = ObjectManager::GetObjectManager();

    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background1);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(outGround);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse);
    objManager->FindLayer(LayerNames::Stage)->AddObject(mouse1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(cheese);
    objManager->FindLayer(LayerNames::Stage)->AddObject(checkPoint1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(checkPoint2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(jail);
}
