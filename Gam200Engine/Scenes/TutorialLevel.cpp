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

TutorialLevel::TutorialLevel() : background(nullptr), button(nullptr), button1(nullptr), wall1(nullptr), wall2(nullptr), wall3(nullptr), wall4(nullptr)
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
    TriggerButton(button1, wall3, wall4);
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

    movingObject_1 = new Object();
    movingObject_1->SetObjectType(Object::ObjectType::MOVING_OBJECT);
    movingObject_1->SetObjectName("movingObject_1");
    movingObject_1->SetTranslation(vector2{ 340.f, 850.f });
    movingObject_1->SetScale(vector2{ 100.f, 100.f });
    movingObject_1->AddComponent(new Sprite(movingObject_1));
    movingObject_1->AddComponent(new Physics(movingObject_1));
    movingObject_1->GetComponentByTemplate<Physics>()->SetObjectCollidingSide(Physics::ObjectSide::LEFT_SIDE);
    movingObject_1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(movingObject_1, Physics::ObjectType::RECTANGLE);
    movingObject_1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
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
    movingObject_2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    movingObject_2->SetDepth(-1.f);

    button = new Object();
    button->SetObjectType(Object::ObjectType::OBSTACLE);
    button->SetObjectName("button");
    button->SetTranslation(vector2{ -870.f, 255 });
    button->SetScale(vector2{ 100.f, 100.f });
    button->AddComponent(new Sprite(button));
    button->AddComponent(new Physics(button));
    button->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button, Physics::ObjectType::RECTANGLE);
    button->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
    button->SetDepth(-1.f);

    wall1 = new Object();
    wall1->SetObjectType(Object::ObjectType::DOOR);
    wall1->SetObjectName("wall1");
    wall1->SetTranslation(vector2{ -725.f, 695.f });
    wall1->SetScale(vector2{ 10.f, 100.f });
    wall1->AddComponent(new Sprite(wall1));
    wall1->AddComponent(new Physics(wall1));
    wall1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    color = wall1->GetComponentByTemplate<Sprite>()->GetColor();
    color.alpha = 0.f;
    wall1->GetComponentByTemplate<Sprite>()->SetColor(color);
    wall1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall1, Physics::ObjectType::RECTANGLE);
    wall1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall1->SetDepth(-1.f);

    wall2 = new Object();
    wall2->SetObjectType(Object::ObjectType::DOOR);
    wall2->SetObjectName("wall2");
    wall2->SetTranslation(vector2{ -360.f, -300.f });
    wall2->SetScale(vector2{ 10.f, 200.f });
    wall2->AddComponent(new Sprite(wall2));
    wall2->AddComponent(new Physics(wall2));
    wall2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
    wall2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall2, Physics::ObjectType::RECTANGLE);
    wall2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall2->SetDepth(-1.f);

    button1 = new Object();
    button1->SetObjectType(Object::ObjectType::OBSTACLE);
    button1->SetObjectName("button1");
    button1->SetTranslation(vector2{ -345.f, -5.f });
    button1->SetScale(vector2{ 100.f, 100.f });
    button1->AddComponent(new Sprite(button1));
    button1->AddComponent(new Physics(button1));
    button1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button1, Physics::ObjectType::RECTANGLE);
    button1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
    button1->SetDepth(-1.f);

    wall3 = new Object();
    wall3->SetObjectType(Object::ObjectType::DOOR);
    wall3->SetObjectName("wall3");
    wall3->SetTranslation(vector2{ -600.f, 860.f });
    wall3->SetScale(vector2{ 100.f, 10.f });
    wall3->AddComponent(new Sprite(wall3));
    wall3->AddComponent(new Physics(wall3));
    wall3->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    color = wall3->GetComponentByTemplate<Sprite>()->GetColor();
    color.alpha = 0.f;
    wall3->GetComponentByTemplate<Sprite>()->SetColor(color);
    wall3->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall3, Physics::ObjectType::RECTANGLE);
    wall3->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall3->SetDepth(-1.f);

    wall4 = new Object();
    wall4->SetObjectType(Object::ObjectType::DOOR);
    wall4->SetObjectName("wall4");
    wall4->SetTranslation(vector2{ -480.f, -300.f });
    wall4->SetScale(vector2{ 10.f, 200.f });
    wall4->AddComponent(new Sprite(wall4));
    wall4->AddComponent(new Physics(wall4));
    wall4->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
    wall4->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall4, Physics::ObjectType::RECTANGLE);
    wall4->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall4->SetDepth(-1.f);

    auto objManager = ObjectManager::GetObjectManager();

    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    objManager->FindLayer(LayerNames::Stage)->AddObject(movingObject_1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(movingObject_2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall4);
}

void TutorialLevel::TriggerButton(Object* button_, Object* door_1, Object* door_2)
{
    if ((player1->GetComponentByTemplate<Physics>()->IsCollideWith(button_) == true || player2->GetComponentByTemplate<Physics>()->IsCollideWith(button_) == true))
    {
        if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false && player1->GetComponentByTemplate<Physics>()->IsCollideWith(door_2) == false && player2->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false && player2->GetComponentByTemplate<Physics>()->IsCollideWith(door_2) == false)
        {
            Graphics::Color4f color = door_1->GetComponentByTemplate<Sprite>()->GetColor();
            Graphics::Color4f color2 = door_2->GetComponentByTemplate<Sprite>()->GetColor();
            if (button_->GetDirtyFlag() == true)
            {

                if (door_1->GetComponentByTemplate<Physics>()->GetActiveGhostCollision() == true)
                {
                    color.alpha = 1.f;
                    door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                    door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));

                    color2.alpha = 0.f;
                    door_2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                    door_2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color2));
                }
                else
                {
                    if (button_->GetDirtyFlag() == true)
                    {
                        color.alpha = 0.f;
                        door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                        door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));

                        color2.alpha = 1.f;
                        door_2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                        door_2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color2));
                    }
                }
                button_->SetDirtyFlag(false);
            }
        }
        else
        {
            button_->SetDirtyFlag(false);
        }
    }
    else
    {
        button_->SetDirtyFlag(true);
    }
}

void TutorialLevel::TriggerButton(Object* button_, Object* door_1)
{
    if ((player1->GetComponentByTemplate<Physics>()->IsCollideWith(button_) == true || player2->GetComponentByTemplate<Physics>()->IsCollideWith(button_) == true))
    {
        if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false && player2->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false)
        {
            if (button_->GetDirtyFlag())
            {
                Graphics::Color4f color = door_1->GetComponentByTemplate<Sprite>()->GetColor();
                if (door_1->GetComponentByTemplate<Physics>()->GetActiveGhostCollision() == true)
                {
                    color.alpha = 1.f;
                    door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                    door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));
                }
                else
                {
                    color.alpha = 0.f;
                    door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                    door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));
                }
                button_->SetDirtyFlag(false);
            }
        }
        else
        {
            button_->SetDirtyFlag(false);
        }
    }
    else
    {
        button_->SetDirtyFlag(true);
    }
}
