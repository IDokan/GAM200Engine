/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  Level4.cpp
Author
    - Jiwon.Jung       jjwon6218@gmail.com
    - Jaemin Woo

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
#include <Object/Mouse/Mouse.hpp>
#include <Object/Points/GoalPoint.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>
#include<Systems/MessageSystem/Message.hpp>
#include<Systems/MessageSystem/MessageDispatcher.hpp>
#include<Component/MessageCapable.hpp>
#include <Component/Scripts/Hostage.hpp>

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

    cameraManager.Init(player1, player2);
    sceneStateManager->SetNameOfSelectedLevel("TutorialLevel1");

    //BGM
    soundManager.Play_Sound(SOUNDS::BACKGROUND_SOUND);
    soundManager.SetVolume(BACKGROUND_SOUND, 0.1f);
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
    background->SetTranslation(vector2{ 1.f });
    background->SetScale(vector2{ 10000.f });
    background->AddComponent(new Sprite(background));
    background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(50.f);
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/background.png");
    background->SetDepth(Depth_Standard::FurtherBackground);
}
