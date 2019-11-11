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
    testObject->SetTranslation(vector2{ -300 });
    testObject->SetScale(vector2{ 100.f });
    testObject->AddComponent(new Sprite(testObject));
    testObject->AddComponent(new Physics(testObject));
    testObject->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 1.f, 1.f });
    testObject->SetDepth(-0.1f);
    testObject->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(testObject, Physics::ObjectType::CIRCLE);
    objManager->FindLayer(LayerNames::Stage)->AddObject(testObject);

    object2 = new Object();
    object2->SetObjectName("Player2");
    object2->SetObjectType(Object::ObjectType::PLAYER_2);
    object2->SetTranslation(vector2{ 250.f });
    object2->SetScale(vector2{ 250.f });
    object2->AddComponent(new Sprite(object2));
    object2->AddComponent(new Physics(object2));
    object2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 1.f, 0.f });
    object2->SetDepth(-0.1f);
    object2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object2, Physics::ObjectType::CIRCLE);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object2);

    

    object1 = new Object();
    object1->SetObjectType(Object::ObjectType::PLAYER_1);
    object1->SetObjectName("Player1");
    object1->SetTranslation(vector2{ 0.f });
    object1->SetScale(vector2{ 200.f });
    object1->AddComponent(new Sprite(object1));
    object1->AddComponent(new Physics(object1));
    object1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object1, Physics::ObjectType::CIRCLE, vector2{ 0.f }, vector2{ -50.f });
    object1->SetDepth(-1.f);
    objManager->FindLayer(LayerNames::Stage)->AddObject(object1);
	string = new Object();
	string->SetObjectName("Rectangle");
	string->SetTranslation(vector2{ (object2->GetTranslation() + object1->GetTranslation())/2 });
	string->SetScale(vector2{object2->GetTranslation().x - object1->GetTranslation().x, 5.f});
	//string->SetRotation(vector2{})
	string->AddComponent(new Sprite(string));
	string->SetDepth(-0.7f);
	string->AddComponent(new Physics(string));
	//string->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(string, ObjectType::RECTANGLE, vector2{ 0.f }, vector2{ -50.f });
	objManager->FindLayer(LayerNames::Stage)->AddObject(string);
	//string->SetDepth(-1.f);

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




	cameraManager.Init();

}

bool check_haha = false;
void TestLevel::Update(float dt)
{
    vector2 obj1Position = object1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = object2->GetComponentByTemplate<Physics>()->GetPosition();
    

    TestLevel::Input();
    
	TestLevel::Collision();
   
	cameraManager.CameraMove(1.1f);
	ObjectManager* objManager = ObjectManager::GetObjectManager();
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
    object2->SetTranslation(obj2Position);
    object1->SetTranslation(obj1Position);
    if (input.IsKeyTriggered(GLFW_KEY_3))
    {
		object1->GetComponentByTemplate<Animation>()->SetFrame(6);
		object1->GetComponentByTemplate<Animation>()->SetSpeed(6);
		object2->GetComponentByTemplate<Animation>()->SetFrame(6);
		object2->GetComponentByTemplate<Animation>()->SetSpeed(10);
    }
	//Bgm Sounds
	if (input.IsKeyTriggered(GLFW_KEY_4) )
	{
	//	test.Load_Sound();
		if (check_haha == false) {
			test.Play_Sound(SOUNDS::JAMJAMTEST_SOUND);
			test.SetVolume(JAMJAMTEST_SOUND, 1);
			check_haha = true;
		}
		else if(check_haha == true)
		{
			test.Stop_Sound(JAMJAMTEST_SOUND);
		}
		
	}

    //Mouse Imputs for deleting all.
    //if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
    //    objManager->FindLayer(LayerNames::Stage)->DeleteObject(object1);
    //    objManager->FindLayer(LayerNames::Stage)->DeleteObject(object2);
    //    objManager->FindLayer(LayerNames::Stage)->DeleteObject(testObject);
    //    objManager->FindLayer(LayerNames::BackGround)->DeleteObject(background);
    //}

	/*************************************UPDATE STRING****************************************************/

	const float dx = (object1->GetTranslation().x - object2->GetTranslation().x);
	const float dy = (object1->GetTranslation().y - object2->GetTranslation().y);
	float stringSize = sqrt(dx * dx + dy * dy);
	float stringAngle = (dx) / stringSize;
	
	string->SetTranslation(vector2{ (object2->GetTranslation() + object1->GetTranslation()) / 2 });
	string->SetScale(vector2{ stringSize, string->GetScale().y });
	if(object1->GetTranslation().y < object2->GetTranslation().y)
		string->SetRotation(acos(-stringAngle));
	else
		string->SetRotation(acos(stringAngle));

    /*******************Level Change Button***************************JJW***********************************/
    if (input.IsMouseDoubleClicked(GLFW_MOUSE_BUTTON_LEFT))
    {
        //When mouse click position is in the range of x range of button
        if ((input.GetMousePosition().x <= (button->GetTranslation().x + button->GetScale().x / 2))
            && (input.GetMousePosition().x >= (button->GetTranslation().x - button->GetScale().x / 2)))
        {
            //When mouse click position is in the range of y range of button
            if ((input.GetMousePosition().y <= (button->GetTranslation().y + button->GetScale().y / 2))
                && (input.GetMousePosition().y >= (button->GetTranslation().y - button->GetScale().y / 2)))
            {
                is_next = true;
                //change the level
                LevelChangeTo("protoLevel");
            }
        }
    }


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
			if (const auto& sprite = obj.get()->GetComponentByTemplate<Sprite>())
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
        object1->GetComponentByTemplate<Physics>()->AddForce(vector2{ object1->GetComponentByTemplate<Physics>()->GetVelocity().x *  30.f, object1->GetComponentByTemplate<Physics>()->GetVelocity().y * 30.f });

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
    vector2 obj1OldPosition = object1->GetComponentByTemplate<Physics>()->GetOldPosition();
    vector2 obj2OldPosition = object2->GetComponentByTemplate<Physics>()->GetOldPosition();

    if (object1->GetComponentByTemplate<Physics>()->IsCollideWith() == true)
    {
        if (object1->GetComponentByTemplate<Physics>()->GetIsGhost() != true)
        {
            object1->GetComponentByTemplate<Physics>()->SetIsCollide(true);
            object1->SetTranslation(obj1OldPosition);
            std::cout << "collision\n";
        }
       /* else
        {
            object1->SetTranslation(obj1Position);
        }*/
    }
    if (object2->GetComponentByTemplate<Physics>()->IsCollideWith() == true)
    {
        if (object2->GetComponentByTemplate<Physics>()->GetIsGhost() != true)
        {
            object2->GetComponentByTemplate<Physics>()->SetIsCollide(true);
            object2->SetTranslation(obj2OldPosition);
        }
        /* else
         {
             object1->SetTranslation(obj1Position);
         }*/
    }
  /*  else
    {
        object1->SetTranslation(obj1Position);
    }*/

    //if (object1->GetComponentByTemplate<Physics>()->IsCollideWith(object2) == true)
    //{
    //    if (object1->GetComponentByTemplate<Physics>()->GetIsGhost() != true)
    //    {
    //        object1->GetComponentByTemplate<Physics>()->SetIsCollide(true);
    //        object2->GetComponentByTemplate<Physics>()->SetIsCollide(true);
    //        object1->SetTranslation(obj1OldPosition);
    //        object2->SetTranslation(obj2OldPosition);
    //    }
    //    else
    //    {
    //        object1->SetTranslation(obj1Position);
    //        object2->SetTranslation(obj2Position);
    //    }
    //}
    //else
    //{
    //    object1->SetTranslation(obj1Position);
    //    object2->SetTranslation(obj2Position);
    //}
}
