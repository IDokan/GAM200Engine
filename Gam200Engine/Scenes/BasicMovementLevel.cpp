/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.cpp
Author
    - Sinil.Kang            rtd99062@gmail.com
    - Hyerin.Jung       junghl0621@gmail.com

Creation Date: 12.10.2019

    Source file for level that player learned how to move player
******************************************************************************/
#include <Scenes/BasicMovementLevel.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/StateMachine.hpp>
#include <States/Walking.hpp>
#include <Object/Players/Player.h>


SoundManager TestBGMSoundForDebugMode;
BasicMovementLevel::BasicMovementLevel(): background(nullptr)
{
}

BasicMovementLevel::~BasicMovementLevel()
{
}

void BasicMovementLevel::Load()
{
    fileIO* a = 0;
    a->Input("../assets/fileIO/saveloadFile.txt");

    BasicMovementLevel::InitObject();

    cameraManager.Init();
    TestBGMSoundForDebugMode.Load_Sound();
    TestBGMSoundForDebugMode.Play_Sound(SOUNDS::BACKGROUND_SOUND);
    TestBGMSoundForDebugMode.SetVolume(BACKGROUND_SOUND, 0.2f);

}

void BasicMovementLevel::Update(float /*dt*/)
{
    BasicMovementLevel::Input();
    BasicMovementLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(player1, player2, 1.1f);
}

void BasicMovementLevel::GameRestart()
{
}

void BasicMovementLevel::Unload()
{
	fileIO* a = 0;
	a->Output("../assets/fileIO/saveloadFile.txt");
}

void BasicMovementLevel::Input()
{
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

void BasicMovementLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void BasicMovementLevel::InitObject() {

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 1.f });
    background->SetScale(vector2{ 1000.f });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

	player1 = new Player(Player::Identifier::Player1);

	player2 = new Player(Player::Identifier::Player2);

    string = new String(player1, player2);

    goalPoint = new Object();
    goalPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    goalPoint->SetObjectName("goalPoint");
    goalPoint->SetTranslation(vector2{ 0.f, 500.f });
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
    startPoint->SetTranslation(vector2{ 0.f, -500.f });
    startPoint->SetScale(vector2{ 150.f });
    startPoint->AddComponent(new Sprite(startPoint));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
    startPoint->SetDepth(-1.f);



    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(string);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
	objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

}

void AddStateTestObject()
{
	Object* obj = new Object();
	obj->SetObjectName("FSM test object");
	obj->SetDepth(-20.f);
	obj->AddComponent(new Sprite(obj));
	obj->AddComponent(new StateMachine<Object>(obj));
	obj->GetComponentByTemplate<StateMachine<Object>>()->SetGlobalState(new Walking());
	obj->SetScale(100.f);
	ObjectManager::GetObjectManager()->FindLayer(Stage)->AddObject(obj);
}