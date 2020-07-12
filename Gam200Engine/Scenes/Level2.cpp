/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Level2.cpp
Author
    - Jiwon Jung jjwon6218@gmail.com

Creation Date: 07.11.2020
******************************************************************************/

#include <Scenes/Level2.hpp>
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
#include <Object/Points/CheckPoint.hpp>
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
#include <Scenes/SceneManager.hpp>

Level2::Level2() : background(nullptr)
{
}

Level2::~Level2()
{
}

void Level2::Load()
{
    fileIO* fileio = new fileIO;
    fileio->Input("../assets/fileIO/Level2.txt", &player1, &player2, &string);

    Level2::InitObject();

    cameraManager.Init(player1, player2);
    sceneStateManager->SetNameOfSelectedLevel("Level3");
}

void Level2::Update(float dt)
{
    player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
    player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();


    Level2::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(dt, player1, player2, 1.1f);
}

void Level2::GameRestart()
{
}

void Level2::Unload()
{
}

void Level2::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void Level2::InitObject()
{
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

    auto objManager = ObjectManager::GetObjectManager();

    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(outGround);
}
