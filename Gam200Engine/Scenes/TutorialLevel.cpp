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
//lock and key
#include<Systems/MessageSystem/Message.hpp>
#include<Systems/MessageSystem/MessageDispatcher.hpp>
#include<Component/MessageCapable.hpp>

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

    wall1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    wall2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);

    cameraManager.Init(player1, player2);
}

void TutorialLevel::Update(float /*dt*/)
{
    player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
    player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();

    TutorialLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(player1, player2, 1.1f);

    TriggerButton(button, wall1, wall2);
}

void TutorialLevel::GameRestart()
{
}

void TutorialLevel::Unload()
{
    //fileIO* a = 0;
    //a->Output("../assets/fileIO/savedTutorial.txt");
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

    button = new Object();
    button->SetObjectType(Object::ObjectType::OBSTACLE);
    button->SetObjectName("button");
    button->SetTranslation(vector2{ 100.f });
    button->SetScale(vector2{ 100.f, 100.f });
    button->AddComponent(new Sprite(button));
    button->AddComponent(new Physics(button));
    button->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button, Physics::ObjectType::RECTANGLE);
    button->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
    button->SetDepth(-1.f);

   wall1 = new Object();
   wall1->SetObjectType(Object::ObjectType::OBSTACLE);
   wall1->SetObjectName("button");
   wall1->SetTranslation(vector2{ 0.f });
   wall1->SetScale(vector2{ 100.f, 100.f });
   wall1->AddComponent(new Sprite(wall1));
   wall1->AddComponent(new Physics(wall1));
   wall1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall1, Physics::ObjectType::RECTANGLE);
   wall1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
   wall1->SetDepth(-1.f);

   wall2 = new Object();
   wall2->SetObjectType(Object::ObjectType::OBSTACLE);
   wall2->SetObjectName("button");
   wall2->SetTranslation(vector2{ -100.f });
   wall2->SetScale(vector2{ 100.f, 100.f });
   wall2->AddComponent(new Sprite(wall2));
   wall2->AddComponent(new Physics(wall2));
   wall2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall2, Physics::ObjectType::RECTANGLE);
   wall2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
   wall2->SetDepth(-1.f);

    auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
	objManager->FindLayer(LayerNames::Stage)->AddObject(button);
	objManager->FindLayer(LayerNames::Stage)->AddObject(wall1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(wall2);

}

void TutorialLevel::TriggerButton(Object* button, Object* door_1, Object* door_2)
{
    if ((player1->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true || player2->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true))
    {
        if (button->GetDirtyFlag() == true)
        {
            if (wall1->GetComponentByTemplate<Physics>()->GetActiveGhostCollision() == true)
            {
                wall1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                wall2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
            }
            else
            {
                if (button->GetDirtyFlag() == true)
                {
                    wall1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                    wall2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                }
            }
            button->SetDirtyFlag(false);
        }
    }
    else
    {
        button->SetDirtyFlag(true);
    }
}
