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
#include <Object/Mouse/Mouse.hpp>
#include <Object/Points/GoalPoint.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>
#include<Systems/MessageSystem/Message.hpp>
#include<Systems/MessageSystem/MessageDispatcher.hpp>
#include<Component/MessageCapable.hpp>
#include <Component/Scripts/Hostage.hpp>

TutorialLevel::TutorialLevel() : background(nullptr), movingObject_1(nullptr), movingObject_2(nullptr)
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::Load()
{
    fileIO* fileio = new fileIO;
    fileio->Input("../assets/fileIO/savedTutorial.txt", &player1, &player2, &string);

	TutorialLevel::InitObject();
	
	cameraManager.Init(player1, player2);
	sceneStateManager->SetNameOfSelectedLevel("TutorialLevel2");


	soundManager.Load_Sound();
	soundManager.Play_Sound(SOUNDS::BACKGROUND_SOUND);
	soundManager.SetVolume(SOUNDS::BACKGROUND_SOUND, 0.1f);
}

void TutorialLevel::Update(float dt)
{
	if (input.IsKeyTriggered(GLFW_KEY_0))
	{
		Physics* player1Physics = player1->GetComponentByTemplate<Physics>();
		player1Physics->ActiveGhostCollision(!player1Physics->GetIsGhost());
		Physics* player2Physics = player2->GetComponentByTemplate<Physics>();
		player2Physics->ActiveGhostCollision(!player2Physics->GetIsGhost());
	}

	player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
	player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();

    TutorialLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

	cameraManager.CameraMove(dt, player1, player2, 1.1f);
}

void TutorialLevel::GameRestart()
{
}

void TutorialLevel::Unload()
{
	//fileIO* a = 0;
	//a->Output("../assets/fileIO/savedTutorial.txt");

	soundManager.Stop_Sound(SOUNDS::BACKGROUND_SOUND);
}

void TutorialLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void TutorialLevel::InitObject() {
	Object* ground = new Object();
	ground->SetObjectName("Ground");
	ground->SetTranslation(vector2{ 150.f, 780.f });
	ground->SetScale(vector2{2350.f, 2500.f});
	Sprite* groundSprite = new Sprite(ground);
	groundSprite->SetImage("../assets/textures/Ground_Background.png");
	ground->AddComponent(groundSprite);
	groundSprite->ExpandTextureCoordinate(3.f);
	ground->SetDepth(Depth_Standard::Background);
	ObjectManager::GetObjectManager()->FindLayer(BackGround)->AddObject(ground);


	background = new Object();
	background->SetObjectName("background1");
	background->SetTranslation(vector2{ 1.f });
	background->SetScale(vector2{ 10000.f });
	background->AddComponent(new Sprite(background));
	background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(50.f);
	background->AddComponent(new Physics(background));
	background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/background.png");
	background->SetDepth(Depth_Standard::FurtherBackground);

	movingObject_1 = new Object();
	movingObject_1->SetObjectType(Object::ObjectType::MOVING_OBJECT);
	movingObject_1->SetObjectName("movingObject_1");
	movingObject_1->SetTranslation(vector2{ 340.f, 850.f });
	movingObject_1->SetScale(vector2{ 100.f, 100.f });
	movingObject_1->AddComponent(new Sprite(movingObject_1));
	movingObject_1->AddComponent(new Physics(movingObject_1));
	movingObject_1->GetComponentByTemplate<Physics>()->SetObjectCollidingSide(Physics::ObjectSide::LEFT_SIDE);
	movingObject_1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(movingObject_1, Physics::ObjectType::RECTANGLE);
	movingObject_1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/moving_object.png");
	movingObject_1->SetDepth(-1.f);

	movingObject_2 = new Object();
	movingObject_2->SetObjectType(Object::ObjectType::MOVING_OBJECT);
	movingObject_2->SetObjectName("movingObject_2");
	movingObject_2->SetTranslation(vector2{ 340.f, 1140.f });
	movingObject_2->SetScale(vector2{ 100.f, 100.f });
	movingObject_2->AddComponent(new Sprite(movingObject_2));
	movingObject_2->AddComponent(new Physics(movingObject_2));
	movingObject_2->GetComponentByTemplate<Physics>()->SetObjectCollidingSide(Physics::ObjectSide::LEFT_SIDE);
	movingObject_2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(movingObject_2, Physics::ObjectType::RECTANGLE);
	movingObject_2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/moving_object.png");
	movingObject_2->SetDepth(-1.f);

    //==================================================== YELLOW ==================================================================
    button1 = new DoorSystem(player1, player2, vector2{ -870.f, 255 }, vector2{ 100.f, 100.f }, vector2{ -870.f, 500.f }, vector2{ 100.f, 100.f }, vector2{ -730.f, 705.f }, vector2{ 50.f, 245.f }, vector2{ -360.f, -292.f }, vector2{ 50.f, 315.f });
    button1->SetButtonAndDoorColor({ 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 0.2f }, { 1.0f, 1.0f, 0.0f, 1.0f });
    button1->SetButtonAndDoorName("button1", "cooperate button1","door_1", "door_2");

    //==================================================== RED ==================================================================

    button2 = new DoorSystem(player1, player2, vector2{ -345.f, 100.f }, vector2{ 100.f, 100.f }, vector2{ -600.f, 350.f }, vector2{ 100.f, 100.f } ,vector2{ -595.f, 869.f }, vector2{ 215.f, 50.f }, vector2{ -480.f, -292.f }, vector2{ 50.f, 315.f });
    button2->SetButtonAndDoorColor({ 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 0.2f }, { 1.0f, 0.0f, 0.0f, 1.0f });
    button2->SetButtonAndDoorName("button2", "cooperate button 2","door_3", "door_4");

    //==================================================== ORANGE ================================================================

    button3 = new DoorSystem(player1, player2, vector2{ -630.f, 1750.f }, vector2{ 100.f, 100.f }, vector2{ 520.f, 1775.f }, vector2{ 50.f, 185.f }, vector2{ 675.f, 450.f }, vector2{ 175.f, 50.f });
    button3->SetButtonAndDoorColor({ 0.50f, 0.5f, 0.f, 1.0f }, { 0.5f, 0.5f, 0.0f, 0.2f }, { 0.5f, 0.5f, 0.0f, 1.0f });
    button3->SetButtonAndDoorName("button3", "door_5", "door_6");

    //==================================================== WHITE ==================================================================

    button4 = new DoorSystem(player1, player2, vector2{ 650.f, 1350.f }, vector2{ 100.f, 100.f }, vector2{ -80.f, 1130.f }, vector2{ 100.f, 100.f },vector2{ 190.f, 1225.f }, vector2{ 100.f, 10.f }, vector2{ -527.f, 1925.f }, vector2{ 50.f, 150.f }, true);
    button4->SetButtonAndDoorColor({ 1.f,1.f ,1.f,1.0f }, { 1.f,1.f ,1.f,1.0f }, { 1.f,1.f, 1.f,0.2f }, { 1.f, 1.f, 1.f, 1.0f });
    button4->SetButtonAndDoorName("button4", "button5","door_7", "door_8");

    //==================================================== PurPle ==================================================================

    button5 = new DoorSystem(player1, player2, vector2{ 1230.f, -360.f }, vector2{ 100.f, 100.f }, vector2{ 1000.f, 1074.f }, vector2{ 50.f, 116.f }, false);
    button5->SetButtonAndDoorColor({ 1.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    button5->SetButtonAndDoorName("button6", "door_9");

	//==================================================== GREEN ==================================================================

	button5 = new DoorSystem(player1, player2, vector2{ -630.f, 1925.f }, vector2{ 100.f, 100.f }, vector2{ -211.f, 1105.f }, vector2{ 50.f, 200.f }, false);
	button5->SetButtonAndDoorColor({ 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
	button5->SetButtonAndDoorName("shotcutButton", "shotcutDoor");

    cheese = new Object();
    cheese->SetObjectType(Object::ObjectType::SavedCheese);
    cheese->SetObjectName("cheese");
    cheese->SetTranslation(vector2{ 860.f, 100.f });
    cheese->SetScale(vector2{ 50.f, 50.f });
    Animation* getAnimationComponenet = new Animation(cheese);
    getAnimationComponenet->SetFrame(6);
    getAnimationComponenet->SetSpeed(5.f);
    cheese->AddComponent(getAnimationComponenet);
    cheese->AddComponent(new Physics(cheese));
    cheese->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    cheese->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(cheese, Physics::ObjectType::RECTANGLE);
    cheese->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/SavedCheese.png");
    cheese->SetDepth(Depth_Standard::SavedCheese);

    jail = new CrushableObject(vector2{ 860.f,100.f }, vector2{ 100.f,100.f }, Physics::ObjectType::RECTANGLE, string);
    jail->SetDepth(Depth_Standard::Jail);
    jail->SetObjectName("jail");


    // Mouse
    Mouse* mouse1 = new Mouse(vector2{ -88.f, 405.f }, vector2{ -88.f, -290.f }, vector2{ -88.f, 1100.f }, player1, player2);
    Mouse* mouse2 = new Mouse(vector2{ 820.f, 630.f }, vector2{ 445.f, 630.f }, vector2{ 1200.f, 630.f }, player1, player2);

    Transform goalTransform;
    goalTransform.SetTranslation(vector2{ 1050.f, 1750.f });
    goalTransform.SetScale(vector2{ 350.f });
    GoalPoint* goalPoint1 = new GoalPoint(goalTransform, player1);
    GoalPoint* goalPoint2 = new GoalPoint(goalTransform, player2);

    auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
	objManager->FindLayer(LayerNames::Stage)->AddObject(mouse1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(mouse2);
	objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint2);
	objManager->FindLayer(LayerNames::Stage)->AddObject(movingObject_1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(movingObject_2);
	objManager->FindLayer(LayerNames::Stage)->AddObject(button1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(button2);
	objManager->FindLayer(LayerNames::Stage)->AddObject(button3);
	objManager->FindLayer(LayerNames::Stage)->AddObject(button4);
	objManager->FindLayer(LayerNames::Stage)->AddObject(button5);
	
    objManager->FindLayer(LayerNames::Stage)->AddObject(cheese);
    objManager->FindLayer(LayerNames::Stage)->AddObject(jail);
}