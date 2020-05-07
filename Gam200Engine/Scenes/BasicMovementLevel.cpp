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
#include <thread>
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
#include <Object/Particles/ParticleEmitter.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>
#include <Object/Points/GoalPoint.hpp>
#include <Object/DepthStandard.hpp>


BasicMovementLevel::BasicMovementLevel(): background(nullptr)
{
}

BasicMovementLevel::~BasicMovementLevel()
{
}

void BasicMovementLevel::Load()
{
    fileIO* fileio = new fileIO();
	fileio->Input("../assets/fileIO/basic.txt", &player1, &player2, &string);

    BasicMovementLevel::InitObject();

    soundManager.Load_Sound();
    soundManager.Play_Sound(SOUNDS::BACKGROUND_SOUND);
    soundManager.SetVolume(BACKGROUND_SOUND, 0.2f);
  
    sceneStateManager->SetNameOfSelectedLevel("TutorialLevel");
}

void BasicMovementLevel::Update(float dt)
{
    BasicMovementLevel::Input();

	player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
	player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();

    BasicMovementLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(dt, player1, player2, 1.1f);
}

void BasicMovementLevel::GameRestart()
{
}

void BasicMovementLevel::Unload()
{
	//fileIO* a = 0;
	//a->Output("../assets/fileIO/saveloadFile.txt");
}

bool isPlaying = true;
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
    //Master Volume Test
    if (input.IsKeyTriggered(GLFW_KEY_0)) {
        soundManager.MASTER_VOLUME_DOWN();
    }
    if (input.IsKeyTriggered(GLFW_KEY_9)) {

        soundManager.MASTER_VOLUME_UP();
    }
}

void BasicMovementLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void BasicMovementLevel::InitObject() {

	auto objManager = ObjectManager::GetObjectManager();

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 1.f });
    background->SetScale(vector2{ 1000.f });
    background->AddComponent(new Sprite(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");
    background->SetDepth(Depth_Standard::Background);

    Transform g1;
    g1.SetScale(vector2{ 250.f });
    g1.SetTranslation(vector2{ 250.f, 500.f });
    Object* goal1 = new GoalPoint(g1, player1);
    Transform g2;
    g2.SetScale(vector2{ 250.f });
    g2.SetTranslation(vector2{ -250.f, 500.f });
    Object* goal2 = new GoalPoint(g2, player2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goal1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goal2);

    startPoint = new Object();
    startPoint->SetObjectType(Object::ObjectType::TEST);
    startPoint->SetObjectName("startPoint");
    startPoint->SetTranslation(vector2{ 0.f, -500.f });
    startPoint->SetScale(vector2{ 150.f });
    startPoint->AddComponent(new Sprite(startPoint));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
	startPoint->GetComponentByTemplate<Sprite>()->SetInstancingMode(Sprite::InstanceModes::ON);
    startPoint->SetDepth(-1.f);

	objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

	ParticleEmitter* emitter = new ParticleEmitter(1.f, 5.f, 500U, 
		[&]() -> Particle::ParticleObject
		{
			Particle::ParticleObject p;
			p.life = 5.f;
			float i = static_cast<float>((rand() % 2000) - 1000.f);
			float scale = static_cast<float>(rand() % 25);
			p.transform.SetTranslation(vector2{ i, 100.f });
			p.transform.SetScale(vector2{ scale });
			
			return p;
		},
		[&](Particle::ParticleObject& p, float /*dt*/) -> void
		{
			float X = static_cast<float>(rand() % 25);
			float Y = static_cast<float>(rand() % 25);
			p.transform.SetTranslation(p.transform.GetTranslation() - vector2{ X, Y });
		}
		);
	emitter->SetTranslation(vector2{ 0.f });
	emitter->SetDepth(-0.5f);
	emitter->SetObjectName("Particle Emitter");
	emitter->GetComponentByTemplate<Particle>()->SetImage("../assets/textures/circle.png");

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