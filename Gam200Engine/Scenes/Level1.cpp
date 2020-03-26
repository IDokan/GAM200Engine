/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Author
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 03.25.2020
******************************************************************************/

#include <Scenes/Level1.hpp>
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


Level1::Level1() : background(nullptr)
{
}

Level1::~Level1()
{
}

void Level1::Load()
{
    fileIO* fileio = new fileIO;
    fileio->Input("../assets/fileIO/Level_one_file.txt", &player1, &player2, &string);

    Level1::InitObject();

    cameraManager.Init(player1, player2);
}

void Level1::Update(float /*dt*/)
{
    player1->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();
    player2->GetComponentByTemplate<Physics>()->IsCollideWithMovedObject();

    Level1::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(player1, player2, 1.1f);
}

void Level1::GameRestart()
{
}

void Level1::Unload()
{
    fileIO* a = 0;
    a->Output("../assets/fileIO/savedTutorial1.txt");
}

void Level1::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void Level1::InitObject() {
    auto objManager = ObjectManager::GetObjectManager();

}