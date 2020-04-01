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
    TriggerButton(button2, wall6, wall9);
    TriggerButton(button4, wall5, wall7);
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


    //==================================================== YELLOW ==================================================================

    button = new Object();
    button->SetObjectType(Object::ObjectType::BUTTON);
    button->SetObjectName("button");
    button->SetTranslation(vector2{ -870.f, 255 });
    button->SetScale(vector2{ 100.f, 100.f });
    button->AddComponent(new Sprite(button));
    button->AddComponent(new Physics(button));
    button->GetComponentByTemplate<Sprite>()->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
    button->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button, Physics::ObjectType::RECTANGLE);
    button->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button->SetDepth(-1.f);

    wall1 = new Object();
    wall1->SetObjectType(Object::ObjectType::DOOR);
    wall1->SetObjectName("wall1");
    wall1->SetTranslation(vector2{ -725.f, 695.f });
    wall1->SetScale(vector2{ 10.f, 100.f });
    wall1->AddComponent(new Sprite(wall1));
    wall1->AddComponent(new Physics(wall1));
    wall1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    wall1->GetComponentByTemplate<Sprite>()->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
    color = wall1->GetComponentByTemplate<Sprite>()->GetColor();
    color.alpha = 0.5f;
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
    wall2->GetComponentByTemplate<Sprite>()->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
    wall2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    wall2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall2, Physics::ObjectType::RECTANGLE);
    wall2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall2->SetDepth(-1.f);


    //==================================================== RED ==================================================================

    button1 = new Object();
    button1->SetObjectType(Object::ObjectType::BUTTON);
    button1->SetObjectName("button1");
    button1->SetTranslation(vector2{ -345.f, -5.f });
    button1->SetScale(vector2{ 100.f, 100.f });
    button1->AddComponent(new Sprite(button1));
    button1->AddComponent(new Physics(button1));
    button1->GetComponentByTemplate<Sprite>()->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
    button1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button1, Physics::ObjectType::RECTANGLE);
    button1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button1->SetDepth(-1.f);

    wall3 = new Object();
    wall3->SetObjectType(Object::ObjectType::DOOR);
    wall3->SetObjectName("wall3");
    wall3->SetTranslation(vector2{ -600.f, 860.f });
    wall3->SetScale(vector2{ 100.f, 10.f });
    wall3->AddComponent(new Sprite(wall3));
    wall3->AddComponent(new Physics(wall3));
    wall3->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    wall3->GetComponentByTemplate<Sprite>()->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
    color = wall3->GetComponentByTemplate<Sprite>()->GetColor();
    color.alpha = 0.5f;
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
    wall4->GetComponentByTemplate<Sprite>()->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
    wall4->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    wall4->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall4, Physics::ObjectType::RECTANGLE);
    wall4->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall4->SetDepth(-1.f);



    //==================================================== ORANGE ==================================================================

    button2 = new Object();
    button2->SetObjectType(Object::ObjectType::BUTTON);
    button2->SetObjectName("button2");
    button2->SetTranslation(vector2{ -630.f, 1750.f });
    button2->SetScale(vector2{ 100.f, 100.f });
    button2->AddComponent(new Sprite(button2));
    button2->AddComponent(new Physics(button2));
    button2->GetComponentByTemplate<Sprite>()->SetColor({ 0.50f, 0.5f, 0.f, 1.0f });
    button2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button2, Physics::ObjectType::RECTANGLE);
    button2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button2->SetDepth(-1.f);

    wall6 = new Object();
    wall6->SetObjectType(Object::ObjectType::DOOR);
    wall6->SetObjectName("wall6");
    wall6->SetTranslation(vector2{ 520.f, 1775.f });
    wall6->SetScale(vector2{ 10.f, 150.f });
    wall6->AddComponent(new Sprite(wall6));
    wall6->AddComponent(new Physics(wall6));
    wall6->GetComponentByTemplate<Sprite>()->SetColor({ 0.5f, 0.5f, 0.0f, 1.0f });
    color = wall6->GetComponentByTemplate<Sprite>()->GetColor();
    color.alpha = 0.5f;
    wall6->GetComponentByTemplate<Sprite>()->SetColor(color);
    wall6->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
    wall6->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall6, Physics::ObjectType::RECTANGLE);
    wall6->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall6->SetDepth(-1.f);

    wall9 = new Object();
    wall9->SetObjectType(Object::ObjectType::DOOR);
    wall9->SetObjectName("wall9");
    wall9->SetTranslation(vector2{ 670.f, 555.f });
    wall9->SetScale(vector2{ 150.f, 10.f });
    wall9->AddComponent(new Sprite(wall9));
    wall9->AddComponent(new Physics(wall9));
    wall9->GetComponentByTemplate<Sprite>()->SetColor({ 0.5f, 0.5f, 0.0f, 1.0f });
    wall9->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
    wall9->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall9, Physics::ObjectType::RECTANGLE);
    wall9->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall9->SetDepth(-1.f);


    //==================================================== WHITE ==================================================================
    button4 = new Object();
    button4->SetObjectType(Object::ObjectType::BUTTON);
    button4->SetObjectName("button4");
    button4->SetTranslation(vector2{ 650.f, 1350.f });
    button4->SetScale(vector2{ 100.f, 100.f });
    button4->AddComponent(new Sprite(button4));
    button4->AddComponent(new Physics(button4));
    button4->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button4, Physics::ObjectType::RECTANGLE);
    button4->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button4->SetDepth(-1.f);

    wall5 = new Object();
    wall5->SetObjectType(Object::ObjectType::DOOR);
    wall5->SetObjectName("wall5");
    wall5->SetTranslation(vector2{ -530.f, 1935.f });
    wall5->SetScale(vector2{ 10.f, 100.f });
    wall5->AddComponent(new Sprite(wall5));
    wall5->AddComponent(new Physics(wall5));
    wall5->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
    wall5->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall5, Physics::ObjectType::RECTANGLE);
    wall5->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall5->SetDepth(-1.f);

    wall7 = new Object();
    wall7->SetObjectType(Object::ObjectType::DOOR);
    wall7->SetObjectName("wall7");
    wall7->SetTranslation(vector2{ 190.f, 1225.f });
    wall7->SetScale(vector2{ 100.f, 10.f });
    wall7->AddComponent(new Sprite(wall7));
    wall7->AddComponent(new Physics(wall7));
    color = wall7->GetComponentByTemplate<Sprite>()->GetColor();
    color.alpha = 0.5f;
    wall7->GetComponentByTemplate<Sprite>()->SetColor(color);
    wall7->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
    wall7->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall7, Physics::ObjectType::RECTANGLE);
    wall7->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall7->SetDepth(-1.f);



    //==================================================== PurPle ==================================================================

    button3 = new Object();
    button3->SetObjectType(Object::ObjectType::BUTTON);
    button3->SetObjectName("button3");
    button3->SetTranslation(vector2{ 1230.f, -360.f });
    button3->SetScale(vector2{ 100.f, 100.f });
    button3->AddComponent(new Sprite(button3));
    button3->AddComponent(new Physics(button3));
    button3->GetComponentByTemplate<Sprite>()->SetColor({ 1.0f, 0.0f, 1.0f, 1.0f });
    button3->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button3, Physics::ObjectType::RECTANGLE);
    button3->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button3->SetDepth(-1.f);

    wall8 = new Object();
    wall8->SetObjectType(Object::ObjectType::DOOR);
    wall8->SetObjectName("wall8");
    wall8->SetTranslation(vector2{ 1000.f, 1075.f });
    wall8->SetScale(vector2{ 10.f, 100.f });
    wall8->AddComponent(new Sprite(wall8));
    wall8->AddComponent(new Physics(wall8));
    wall8->GetComponentByTemplate<Sprite>()->SetColor({ 1.0f, 0.0f, 1.0f, 1.0f });
    wall8->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
    wall8->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(wall8, Physics::ObjectType::RECTANGLE);
    wall8->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    wall8->SetDepth(-1.f);





    auto objManager = ObjectManager::GetObjectManager();

    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    objManager->FindLayer(LayerNames::Stage)->AddObject(movingObject_1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(movingObject_2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(button4);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall4);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall5);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall6);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall7);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall8);
    objManager->FindLayer(LayerNames::Stage)->AddObject(wall9);
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

                    color2.alpha = 0.5f;
                    door_2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                    door_2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color2));
                }
                else
                {
                    if (button_->GetDirtyFlag() == true)
                    {
                        color.alpha = 0.5f;
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
    }
    else
    {
        button_->SetDirtyFlag(true);
    }
}
