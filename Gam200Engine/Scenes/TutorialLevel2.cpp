/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TutorialLevel2.cpp
Author
    - Jaemin Woo wjm9932@gmail.com 

Creation Date: 05.06.2020
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
#include <Object/DepthStandard.hpp>
#include <Object/InteractiveObject/CrushableObject.hpp>
#include <Component/Sprite/TextComponent.hpp>
#include <Graphics/StockBitmapFonts.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>
#include <Component/Scripts/Hostage.hpp>
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
    sceneStateManager->SetNameOfSelectedLevel("Level3");
}

void TutorialLevel2::Update(float dt)
{
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

}

void TutorialLevel2::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void TutorialLevel2::InitObject() 
{
    jailText = new Object();
    jailText->SetObjectName("JailText");
    jailText->SetTranslation(vector2{ 1800.f, -150.f });
    jailText->SetScale(vector2{1.f,1.f });
    jailText->AddComponent(new TextComponent(jailText));
    jailText->GetComponentByTemplate<TextComponent>()->SetString(L"Wrapping up the Jail with string!!");
    jailText->SetDepth(Depth_Standard::SavedCheese);


    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 1165.f, 0.f });
    background->SetScale(vector2{ 5600.f,800.f });
    background->AddComponent(new Sprite(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/Ground_Background.png");
    vector2 scale = background->GetScale();
    background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(vector2{ scale.x / 780.f, scale.y / 800.f });
    background->SetDepth(Depth_Standard::Background);

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

    cheese = new Object();
    cheese->SetObjectType(Object::ObjectType::SavedCheese);
    cheese->SetObjectName("cheese");
    cheese->SetTranslation(vector2{ 2100, 0.f });
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

    jail = new CrushableObject(vector2{ 2100.f, 0.f }, vector2{ 100.f, 100.f }, Physics::ObjectType::RECTANGLE, string);
    jail->SetDepth(Depth_Standard::Jail);
    jail->SetObjectName("jail");

    button1 = new DoorSystem(player1, player2, vector2{ -660.f, -230.f }, vector2{ 100.f, 100.f }, vector2{ -975, 0.f }, vector2{ 100.f, 180.f }, vector2{ -400.f, 0.f }, vector2{ 100.f, 180.f });
    button1->SetButtonAndDoorColor({ 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f });
    button1->SetButtonAndDoorName("button1", "door_1", "door_2");

    button2 = new DoorSystem(player1, player2, vector2{ 680.f, -230.f }, vector2{ 100.f, 100.f }, vector2{1350.f, -230.f}, vector2{ 100.f, 100.f }, vector2{ 550, 0.f }, vector2{ 100.f, 180.f }, vector2{ 1500.f, 0.f }, vector2{ 100.f, 180.f });
    button2->SetButtonAndDoorColor({ 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f });
    button2->SetButtonAndDoorName("button2", "button3", "door_3", "door_4");

    button3 = new DoorSystem(player1, player2, vector2{ 2850.f, 260.f }, vector2{ 100.f, 100.f }, vector2{ 3050.f, 0.f }, vector2{ 100.f, 180.f }, false);
    button3->SetButtonAndDoorColor({ 1.0f, 1.0f, 1.0f, 1.0f }, {1.0f, 1.0f, 1.0f, 1.0f });
    button3->SetButtonAndDoorName("button4", "door_5");
    
    button4 = new DoorSystem(player1, player2, vector2{ -155.f, -230.f }, vector2{ 100.f, 100.f }, vector2{ 310.f, -230.f }, vector2{ 100.f, 100.f }, vector2{ -300, 0.f }, vector2{ 100.f, 180.f }, vector2{ 450.f, 0.f }, vector2{ 100.f, 180.f }, true);
    button4->SetButtonAndDoorColor({ 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f });
    button4->SetButtonAndDoorName("button5", "button6", "door_6", "door_7");


    Transform goalTransform;
    goalTransform.SetTranslation(vector2{ 3550.f, 0.f });
    goalTransform.SetScale(vector2{ 400.f });
    GoalPoint* goalPoint1 = new GoalPoint(goalTransform, player1, player2);

    
    auto objManager = ObjectManager::GetObjectManager();



    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(outGround);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button4);
    //objManager->FindLayer(LayerNames::Stage)->AddObject(movingObject_1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(cheese);
    objManager->FindLayer(LayerNames::Stage)->AddObject(jail);
    objManager->FindLayer(LayerNames::Stage)->AddObject(jailText);
}