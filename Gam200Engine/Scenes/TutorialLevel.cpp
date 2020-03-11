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


TutorialLevel::TutorialLevel() : background(nullptr)
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

    cameraManager.Init();
}

void TutorialLevel::Update(float /*dt*/)
{
    TutorialLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(player1, player2, 1.1f);
}

void TutorialLevel::GameRestart()
{
}

void TutorialLevel::Unload()
{
    /*fileIO* a = 0;
    a->Output("../assets/fileIO/savedTutorial.txt");*/
}

void TutorialLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void TutorialLevel::InitObject() {
	background = new Object();
	background->SetObjectName("background1");
	background->SetTranslation(vector2{ 1.f });
	background->SetScale(vector2{ 2000.f, 4000.f });
	background->AddComponent(new Sprite(background));
	background->AddComponent(new Physics(background));
	background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

	auto objManager = ObjectManager::GetObjectManager();
	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

}