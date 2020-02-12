/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.cpp
Author
    - Hyerin.Jung       junghl0621@gmail.com

Creation Date: 02.11.2019

    Source file for level that player learned how to move player
******************************************************************************/
#include <States/TutorialLevel.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>

SoundManager TestBGMSoundForDebugMode;
TutorialLevel::TutorialLevel() : background(nullptr)
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::Load()
{
    fileIO* a = 0;
    a->Input("../assets/fileIO/tutorialLevelFile.txt");

    TutorialLevel::InitObject();

    cameraManager.Init();
    TestBGMSoundForDebugMode.Load_Sound();
    TestBGMSoundForDebugMode.Play_Sound(SOUNDS::BACKGROUND_SOUND);
    TestBGMSoundForDebugMode.SetVolume(BACKGROUND_SOUND, 0.2f);

}

void TutorialLevel::Update(float /*dt*/)
{
    TutorialLevel::Input();
    TutorialLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(obj1Position, obj2Position, 1.1f);
}

void TutorialLevel::GameRestart()
{
}

void TutorialLevel::Unload()
{
    fileIO* a = 0;
    a->Output();
}

void TutorialLevel::Input()
{
    /**********************Moving Object 1*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_W))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_D))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_A))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_A))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_S))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_A))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_D))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_D))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_W) && input.IsKeyReleased(GLFW_KEY_A) && input.IsKeyReleased(GLFW_KEY_S) && input.IsKeyReleased(GLFW_KEY_D))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }




    /**********************Moving Object 2*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_UP))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_LEFT))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_DOWN))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_RIGHT))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_UP) && input.IsKeyReleased(GLFW_KEY_LEFT) && input.IsKeyReleased(GLFW_KEY_DOWN) && input.IsKeyReleased(GLFW_KEY_RIGHT))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }
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

void TutorialLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void TutorialLevel::InitObject() {


    //=================================   BASIC  = ===================================
    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(string);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);

    //================================   BLOCKS   ===================================
    objManager->FindLayer(LayerNames::Stage)->AddObject(block1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block3);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block4);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block5);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block6);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block7);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block8);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block9);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block10);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block11);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block12);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block13);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block14);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block15);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block16);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block17);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block18);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block19);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block20);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block21);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block22);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block23);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block24);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block25);
    objManager->FindLayer(LayerNames::Stage)->AddObject(block26);

    //=============================   OBJECTS   ======================================
    objManager->FindLayer(LayerNames::Stage)->AddObject(moveBox1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(lock1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(lock2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(key1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(key2);

    //===========================================================================
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

}