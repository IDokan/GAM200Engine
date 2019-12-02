/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TestLevel.cpp
Author
    - Sinil.Kang rtd99062@gmail.com

Creation Date: 08.15.2019

    Source file for First Level to Test Sprite Component
******************************************************************************/
#include <iostream>
#include <cmath>
#include "TestLevel.hpp"
#include <Object/ObjectManager.hpp>
#include <Input.hpp>
#include <Graphics/GL.hpp>
#include <Graphics/Parallax scrolling/Layer.hpp>
#include "Sounds/SoundManager.hpp"
// Include Components
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <Component/Animation.hpp>
#include <Component/TextComponent.hpp>
#include <Component/StringSprite.hpp>
#include <Component/StringPhysics.hpp>

SoundManager test;
void TestLevel::Load()
{
    test.Load_Sound();
    // Set Layer
    auto objManager = ObjectManager::GetObjectManager();
    //Player* player = new Player( , ,,);


    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 0.f });
    background->SetScale(vector2{ 700000 });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/background.png");
    background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(1000);


    testObject = new Object();
    testObject->SetObjectName("test");
    testObject->SetObjectType(Object::ObjectType::OBSTACLE);
    testObject->SetTranslation(vector2{ 600 });
    testObject->SetScale(vector2{ 100.f });
    testObject->AddComponent(new Sprite(testObject));
    testObject->AddComponent(new Physics(testObject));
    testObject->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 1.f, 1.f });
    testObject->SetDepth(-0.1f);
    testObject->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(testObject, Physics::ObjectType::CIRCLE);
    objManager->FindLayer(LayerNames::Stage)->AddObject(testObject);

    object1 = new Object();
    object1->SetObjectType(Object::ObjectType::PLAYER_1);
    object1->SetObjectName("Player1");
    object1->SetTranslation(vector2{ -800.f});
    object1->SetScale(vector2{ 150.f });
    object1->AddComponent(new Sprite(object1));
    object1->AddComponent(new Physics(object1));
    object1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object1, Physics::ObjectType::CIRCLE, vector2{ 0.f }, vector2{ -50.f });
    object1->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object1);

	object2 = new Object();
	object2->SetObjectName("Player2");
	object2->SetObjectType(Object::ObjectType::PLAYER_2);
	object2->SetTranslation(vector2{ 250.f});
	object2->SetScale(vector2{ 250.f });
	object2->AddComponent(new Sprite(object2));
	object2->AddComponent(new Physics(object2));
	object2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 1.f, 0.f });
	object2->SetDepth(-0.1f);
	object2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object2, Physics::ObjectType::CIRCLE);
	objManager->FindLayer(LayerNames::Stage)->AddObject(object2);
	
	string = new String(object1, object2);
	string->SetObjectType(Object::ObjectType::STRING);
	string->SetObjectName("String");
	string->SetTranslation(vector2{ 0.f });
	string->SetScale(vector2{1.f});
	string->SetDepth(-0.1f);
	objManager->FindLayer(LayerNames::Stage)->AddObject(string);


    button = new Object();
    //button->SetObjectType(Object::ObjectType::RECTANGLE);
    button->SetObjectName("Button");
    button->SetTranslation(vector2{ 400.f, -350.f });
    button->SetScale(vector2{ 50.f });
    button->AddComponent(new Sprite(button));
    button->SetDepth(-0.1f);
    button->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 0.5f, 0.5f, 1.f });
    button->AddComponent(new Physics(button));
    objManager->FindLayer(LayerNames::HUD)->AddObject(button);


    goalPoint = new Object();
    goalPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    goalPoint->SetObjectName("goalPoint");
    goalPoint->SetTranslation(vector2{ 2000.f });
    goalPoint->SetScale(vector2{ 50.f });
    goalPoint->AddComponent(new Sprite(goalPoint));
    goalPoint->AddComponent(new Physics(goalPoint));
    goalPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(goalPoint, Physics::ObjectType::RECTANGLE, vector2{ 0.f }, vector2{ -50.f });
    goalPoint->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);










	cameraManager.Init();


    cameraManager.Init();

    cameraDEBUGdrawing = new Object();
    cameraDEBUGdrawing->SetObjectName("camera Debug drawing object");
    cameraDEBUGdrawing->SetTranslation(cameraManager.GetPosition());
    cameraDEBUGdrawing->SetScale(vector2{ 1000, 600 });
    cameraDEBUGdrawing->AddComponent(new Sprite(cameraDEBUGdrawing));
    cameraDEBUGdrawing->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 1.f, 1.f, 0.5 });
    objManager->FindLayer(HUD)->AddObject(cameraDEBUGdrawing);

}

bool check_haha = false;
void TestLevel::Update(float dt)
{
    vector2 obj1Position = object1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = object2->GetComponentByTemplate<Physics>()->GetPosition();

    object1->SetTranslation(obj1Position);
    object2->SetTranslation(obj2Position);

    TestLevel::Collision();
    TestLevel::Input();

	// DEBUG object should be updated after camera Update()
	cameraManager.CameraMove(obj1Position, obj2Position, 1.1f);
	cameraDEBUGdrawing->SetTranslation(cameraManager.GetPosition());
	vector2 cameraRect = cameraManager.GetDEBUGCameraRectSize() * 2;
	cameraDEBUGdrawing->SetScale(cameraRect);
	ObjectManager* objManager = ObjectManager::GetObjectManager();




    //Collision Check with goalPoint and Player 1
    //object1->GetComponentByTemplate<Physics>()->GetPosition() == goalPoint-> GetComponentByTemplate<Physics>()->GetPosition()
    if (goalPoint->GetComponentByTemplate<Physics>()->IsCollideWith(object1) && isCheck_Clear == false)
    {
        gameClearPopUp = new Object();
        gameClearPopUp->SetObjectName("gameClearPopUp");
        gameClearPopUp->SetObjectType(Object::ObjectType::OBSTACLE);
        gameClearPopUp->SetTranslation(vector2{  cameraManager.GetPosition().x,cameraManager.GetPosition().y });
        gameClearPopUp->SetScale(vector2{ 1500.f,1200.f });
        gameClearPopUp->AddComponent(new Sprite(gameClearPopUp));
        gameClearPopUp->AddComponent(new Physics(gameClearPopUp));
        gameClearPopUp->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/GameClear.png");
        gameClearPopUp->SetDepth(-2.f);
        objManager->FindLayer(LayerNames::HUD)->AddObject(gameClearPopUp);
        isCheck_Clear = true;
    }


	// Background show up
	if (input.IsKeyTriggered(GLFW_KEY_1))
	{
		objManager->FindLayer(LayerNames::BackGround)->AddObjectDynamically(background);
	}
	// Sprite show up
	if (input.IsKeyTriggered(GLFW_KEY_2))
	{
		object2->GetComponentByTemplate<Animation>()->SetImage("../assets/textures/playerSprite2.png");
		object1->GetComponentByTemplate<Animation>()->SetImage("../assets/textures/playerSprite1.png");
	}
	// Animation Works

    if (input.IsKeyTriggered(GLFW_KEY_3))
    {
        object1->GetComponentByTemplate<Animation>()->SetFrame(6);
        object1->GetComponentByTemplate<Animation>()->SetSpeed(6);
        object2->GetComponentByTemplate<Animation>()->SetFrame(6);
        object2->GetComponentByTemplate<Animation>()->SetSpeed(10);
    }
    //Bgm Sounds
    if (input.IsKeyTriggered(GLFW_KEY_4))
    {
        //	test.Load_Sound();
        if (check_haha == false) {
            test.Play_Sound(SOUNDS::JAMJAMTEST_SOUND);
            test.SetVolume(JAMJAMTEST_SOUND, 1);
            check_haha = true;
        }
        else if (check_haha == true)
        {
            test.Stop_Sound(JAMJAMTEST_SOUND);
        }
    }

    //Mouse Imputs for deleting all.
    if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        objManager->FindLayer(LayerNames::Stage)->DeleteObject(testObject);
    }


    //stage transition
    is_next = false;
    if (input.IsMouseDoubleClicked(GLFW_MOUSE_BUTTON_LEFT))
    {
        is_next = true;
        //change the level 
        LevelChangeTo("protoLevel");
    }
    //collision check with player 1 or 2 and goal Point
}

void TestLevel::Unload()
{
}

void TestLevel::Draw() const noexcept
{
    Graphics::GL::begin_drawing();

    for (const auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
    {
        for (const auto& obj : element->GetObjContainer())
        {
            if (const auto& stringSprite = obj.get()->GetComponentByTemplate<StringSprite>())
            {
                // Incomplete one
                const auto matrix = cameraManager.GetWorldToNDCTransform();
                stringSprite->UpdateUniforms(matrix,
                    obj.get()->GetTransform().CalculateWorldDepth());
                Graphics::GL::draw(*stringSprite->GetVertices(), *stringSprite->GetMaterial());
            }
            else if (const auto& sprite = obj.get()->GetComponentByTemplate<Sprite>())
            {
                const auto matrix = cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld();
                sprite->UpdateUniforms(matrix,
                    obj.get()->GetTransform().CalculateWorldDepth());
                Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());
            }
            if (const auto& text = obj.get()->GetComponentByTemplate<TextComponent>())
            {
                const auto matrix = cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld();
                text->Draw(matrix,
                    obj.get()->GetTransform().CalculateWorldDepth());
            }
        }
    }
    Graphics::GL::end_drawing();
}

void TestLevel::Input()
{
    /**********************Moving Object 1*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_W))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_D))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_A))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_A))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_S))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_A))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_D))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_D))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            object1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_W) && input.IsKeyReleased(GLFW_KEY_A) && input.IsKeyReleased(GLFW_KEY_S) && input.IsKeyReleased(GLFW_KEY_D))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }




    /**********************Moving Object 2*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_UP))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_LEFT))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_DOWN))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_RIGHT))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            object2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_UP) && input.IsKeyReleased(GLFW_KEY_LEFT) && input.IsKeyReleased(GLFW_KEY_DOWN) && input.IsKeyReleased(GLFW_KEY_RIGHT))
    {
        object2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }
    if (input.IsKeyTriggered(GLFW_KEY_SPACE))
    {
        object1->GetComponentByTemplate<Physics>()->AddForce(vector2{ object1->GetComponentByTemplate<Physics>()->GetVelocity().x * 30.f, object1->GetComponentByTemplate<Physics>()->GetVelocity().y * 30.f });

        test.Play_Sound(SOUNDS::DASH_SOUND);
        test.SetVolume(DASH_SOUND, 1);
    }
    if (input.IsKeyTriggered(GLFW_KEY_G))
    {
        if (object1->GetComponentByTemplate<Physics>()->GetIsGhost() == true)
        {
            object1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
        }
        else
        {
            object1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
        }
    }


}

void TestLevel::Collision()
{
    object1->GetComponentByTemplate<Physics>()->ManageCollision();
}
