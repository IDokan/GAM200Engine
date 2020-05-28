/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  AlphaTutorialLevel1.cpp
Author
    - Jiwon.Jung       jjwon6218@gmail.com
    - Doyoung Lee

Creation Date: 05.10.2020

	Source file for level that player learned how to move player
******************************************************************************/
#include <Scenes/AlphaTutorialLevel1.hpp>
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

AlphaTutorialLevel1::AlphaTutorialLevel1() : background(nullptr)
{
}

AlphaTutorialLevel1::~AlphaTutorialLevel1()
{
}

void AlphaTutorialLevel1::Load()
{
    fileIO* fileio = new fileIO;
    fileio->Input("../assets/fileIO/alphaTutorialLevel1.txt", &player1, &player2, &string);

    AlphaTutorialLevel1::InitObject();

    cameraManager.Init(player1, player2);
    sceneStateManager->SetNameOfSelectedLevel("TutorialLevel2");
}

void AlphaTutorialLevel1::Update(float dt)
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

	AlphaTutorialLevel1::Collision();

	vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
	vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

	player1->SetTranslation(obj1Position);
	player2->SetTranslation(obj2Position);

	cameraManager.CameraMove(dt, player1, player2, 1.1f);
}

void AlphaTutorialLevel1::GameRestart()
{
}

void AlphaTutorialLevel1::Unload()
{

}

void AlphaTutorialLevel1::Collision()
{
	player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void AlphaTutorialLevel1::InitObject()
{
	Object* ground = new Object();
	ground->SetObjectName("Ground");
	ground->SetTranslation(vector2{ 712.f, 20.f });
	ground->SetScale(vector2{ 2770.f, 630.f });
	Sprite* groundSprite = new Sprite(ground);
	groundSprite->SetImage("../assets/textures/Ground_Background.png");
	ground->AddComponent(groundSprite);
	vector2 scale = ground->GetScale();
	groundSprite->ExpandTextureCoordinate(vector2{ scale.x / 783.f, scale.y / 833.f });
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

	movingObject = new Object();
	movingObject->SetObjectType(Object::ObjectType::MOVING_OBJECT);
	movingObject->SetObjectName("movingObject");
	movingObject->SetTranslation(vector2{ 505.f, -245.f });
	movingObject->SetScale(vector2{ 50.f, 50.f });
	movingObject->AddComponent(new Sprite(movingObject));
	movingObject->AddComponent(new Physics(movingObject));
	movingObject->GetComponentByTemplate<Physics>()->SetObjectCollidingSide(Physics::ObjectSide::LEFT_SIDE);
	movingObject->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(movingObject, Physics::ObjectType::RECTANGLE);
	movingObject->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/moving_object.png");
	movingObject->SetDepth(-1.f);

	Mouse* mouse = new Mouse(vector2{ 652, 217 }, vector2{ 602, 217 }, vector2{ 1600, 217 }, player1, player2);

	Transform goalTransform;
	goalTransform.SetTranslation(vector2{ 1330.f, -85.f });
	goalTransform.SetScale(vector2{ 400, 400 });
	GoalPoint* goalPoint1 = new GoalPoint(goalTransform, player1, player2);

	cheese = new Object();
	cheese->SetObjectType(Object::ObjectType::SavedCheese);
	cheese->SetObjectName("cheese");
	cheese->SetTranslation(vector2{ 1920.f, 180.f });
	cheese->SetScale(vector2{ 50.f, 50.f });
	Animation* getAnimationComponent = new Animation(cheese);
	getAnimationComponent->SetFrame(6);
	getAnimationComponent->SetSpeed(5.f);
	cheese->AddComponent(getAnimationComponent);
	cheese->AddComponent(new Physics(cheese));
	cheese->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
	cheese->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(cheese, Physics::ObjectType::RECTANGLE);
	cheese->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/SavedCheese.png");
	cheese->AddComponent(new Hostage(cheese, player1, player2));
	cheese->SetDepth(Depth_Standard::SavedCheese);

	Object* p1Indicator = new Object();
	p1Indicator->SetObjectName("p1Indicator");
	p1Indicator->SetTranslation(vector2{ -380.f, 440.f });
	p1Indicator->SetScale(vector2{ 300.f, 300.f });
	p1Indicator->AddComponent(new Sprite(p1Indicator));
	p1Indicator->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/wasdSign.png");
	p1Indicator->SetObjectType(Object::ObjectType::TEST);
	p1Indicator->SetDepth(Depth_Standard::WoodSign);

	Object* p2Indicator = new Object();
	p2Indicator->SetObjectName("p2Indicator");
	p2Indicator->SetTranslation(vector2{ 0.f, 440.f });
	p2Indicator->SetScale(vector2{ 300.f, 300.f });
	p2Indicator->AddComponent(new Sprite(p2Indicator));
	p2Indicator->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/arrowSign.png");
	p2Indicator->SetObjectType(Object::ObjectType::TEST);
	p2Indicator->SetDepth(Depth_Standard::WoodSign);

	Object* sizeSign = new Object();
	sizeSign->SetObjectName("sizeSign");
	sizeSign->SetTranslation(vector2{ 500.f, 460.f });
	sizeSign->SetScale(vector2{ 380.f, 380.f });
	Animation* animation = new Animation(sizeSign);
	sizeSign->AddComponent(animation);
	animation->SetImage("../assets/textures/sizeSign.png");
	animation->SetNumOfState(1);
	animation->SetSpeed(2.5f);
	animation->SetFrame(6);
	sizeSign->SetObjectType(Object::ObjectType::TEST);
	sizeSign->SetDepth(Depth_Standard::WoodSign);

	auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
	objManager->FindLayer(LayerNames::Stage)->AddObject(movingObject);
	objManager->FindLayer(LayerNames::Stage)->AddObject(mouse);
	objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(cheese);
	objManager->FindLayer(LayerNames::Stage)->AddObject(p1Indicator);
	objManager->FindLayer(LayerNames::Stage)->AddObject(p2Indicator);
	objManager->FindLayer(LayerNames::Stage)->AddObject(sizeSign);
}
