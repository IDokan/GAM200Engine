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
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <Object/ObjectManager.hpp>
#include <Input.hpp>
#include <Graphics/GL.hpp>
#include <Graphics/Parallax scrolling/Layer.hpp>
#include "Sounds/SoundManager.hpp"

SoundManager test;
void TestLevel::Load()
{
	test.Load_Sound();
	// Set Layer
	auto objManager = ObjectManager::GetObjectManager();

	background = new Object();
	background->SetObjectName("background");
	background->SetTranslation(vector2{ 0.f });
	background->SetScale(vector2{ 700000 });
	background->AddComponent(new Sprite(background));
	background->AddComponent(new Physics(background));
	background->GetComponentByTemplate<Sprite>()->SetImage("../texture/background.png");
	background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(1000);
	
	object2 = new Object();
	object2->SetObjectName("Player2");
	object2->SetTranslation(vector2{ 250.f });
	object2->SetScale(vector2{ 250.f });
	object2->AddComponent(new Sprite(object2));
	object2->AddComponent(new Physics(object2));
	object2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 1.f, 0.f });
	object2->SetDepth(-0.1f);
    object2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object2, ObjectType::CIRCLE);
	objManager->FindLayer(LayerNames::Stage)->AddObject(object2);

	/*object4 = new Object();
	object4->SetObjectName("Object4");
	object4->SetTranslation(vector2{ 500.f });
	object4->SetScale(vector2{ 200.f });
	object4->AddComponent(new Sprite(object4));
	object4->AddComponent(new Physics(object4));
	object4->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object4, ObjectType::CIRCLE);
	objManager->FindLayer(LayerNames::Stage)->AddObject(object4);*/

	numbers = new Object();
	numbers->SetObjectName("numbers");
	numbers->SetTranslation(vector2{ -100.f });
	numbers->SetScale(vector2{ 200.f });
	numbers->AddComponent(new Sprite(numbers));
	numbers->AddComponent(new Physics(numbers));
	numbers->GetComponentByTemplate<Sprite>()->SetImage("../texture/numbers.png");
	numbers->GetComponentByTemplate<Sprite>()->SetFrame(10);
	numbers->GetComponentByTemplate<Sprite>()->SetIsAnimated(true);
	numbers->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(numbers, ObjectType::CIRCLE);
	numbers->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
	numbers->SetDepth(-0.5f);

	object1 = new Object();
	object1->SetObjectName("Player1");
	object1->SetTranslation(vector2{ 0.f });
	object1->SetScale(vector2{ 200.f });
	object1->AddComponent(new Sprite(object1));
	object1->AddComponent(new Physics(object1));
	object1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object1, ObjectType::CIRCLE, vector2{0.f}, vector2{-50.f});
	objManager->FindLayer(LayerNames::Stage)->AddObject(object1);

	string = new Object();
	string->SetObjectName("Rectangle");
	string->SetTranslation(vector2{ (object2->GetTranslation() + object1->GetTranslation())/2 });
	string->SetScale(vector2{object2->GetTranslation().x - object1->GetTranslation().x, 5.f});
	//string->SetRotation(vector2{})
	string->AddComponent(new Sprite(string));
	string->SetDepth(-0.7f);
	//string->AddComponent(new Physics(string));
	//string->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(string, ObjectType::RECTANGLE, vector2{ 0.f }, vector2{ -50.f });
	objManager->FindLayer(LayerNames::Stage)->AddObject(string);
	//string->SetDepth(-1.f);

	cameraManager.Init();

}

Object* collisionBox;
Object* cB2;
bool isCollisionBoxShown = false;
void AddCollisionBox(Object* obj, Physics* physics, bool tmp = false)
{
	if (isCollisionBoxShown == true)
	{
		return;
	}

	Layer* hudLayer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD);
	if (hudLayer != nullptr)
	{
		// Toggle Show var
		isCollisionBoxShown = true;

		if (!tmp)
		{
			// Make Collision Box Object and Add to Object Manager
			collisionBox = new Object();
			collisionBox->AddComponent(new Sprite(collisionBox));
			collisionBox->SetObjectName(obj->GetObjectName() + " CollisionBox");
			const CollsionBox positionOfCollisionBox = physics->GetCollisionBox();
			collisionBox->SetTranslation(positionOfCollisionBox.Translation);
			collisionBox->SetScale(positionOfCollisionBox.Scale);
			collisionBox->SetDepth(-1.f);

			// If type of collision type is circle, make image as circle.
			if (physics->GetObjectType() == ObjectType::CIRCLE)
			{
				collisionBox->GetComponentByTemplate<Sprite>()->SetImage("../texture/circle.png");
			}

			hudLayer->AddObjectDynamically(collisionBox);
		}
		else
		{
			// Make Collision Box Object and Add to Object Manager
			cB2 = new Object();
			cB2->AddComponent(new Sprite(cB2));
			cB2->SetObjectName(obj->GetObjectName() + " CollisionBox2");
			const CollsionBox positionOfCollisionBox = physics->GetCollisionBox();
			cB2->SetTranslation(positionOfCollisionBox.Translation);
			cB2->SetScale(positionOfCollisionBox.Scale);
			cB2->SetDepth(-1.f);

			// If type of collision type is circle, make image as circle.
			if (physics->GetObjectType() == ObjectType::CIRCLE)
			{
				cB2->GetComponentByTemplate<Sprite>()->SetImage("../texture/circle.png");
			}

			hudLayer->AddObjectDynamically(cB2);
		}
	}
}

void DeleteCollisionBox(Object* obj, Physics* physics, bool tmp = false)
{
	if (isCollisionBoxShown == false)
	{
		return;
	}
	Layer* hudLayer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD);
	// Toggle Show Var
	isCollisionBoxShown = false;
	if (tmp)
	{
		cB2->SetDead(true);
	}
	else
	{
		
		collisionBox->SetDead(true);
	}
	//hudLayer->DeleteObject(obj->GetObjectName() + " CollisionBox");
}
bool check_haha = false;
void TestLevel::Update(float dt)
{
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
		object2->GetComponentByTemplate<Sprite>()->SetImage("../texture/playerSprite2.png");
		object1->GetComponentByTemplate<Sprite>()->SetImage("../texture/playerSprite1.png");
	}
	// Animation Works
    if (input.IsKeyTriggered(GLFW_KEY_3))
    {
		object1->GetComponentByTemplate<Sprite>()->SetIsAnimated(true);
		object1->GetComponentByTemplate<Sprite>()->SetFrame(6);
		object1->GetComponentByTemplate<Sprite>()->SetSpeed(6);
		object2->GetComponentByTemplate<Sprite>()->SetFrame(6);
		object2->GetComponentByTemplate<Sprite>()->SetSpeed(10);
		object2->GetComponentByTemplate<Sprite>()->SetIsAnimated(true);
		objManager->FindLayer(LayerNames::Stage)->AddObject(numbers);
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
	if (input.IsKeyTriggered(GLFW_KEY_5))
	{
		
	}
	if (input.IsKeyTriggered(GLFW_KEY_Q))
	{
		AddCollisionBox(object1, object1->GetComponentByTemplate<Physics>());
	}
	if (input.IsKeyTriggered(GLFW_KEY_Z))
	{
		DeleteCollisionBox(object1, object1->GetComponentByTemplate<Physics>());
	}
	if (input.IsKeyTriggered(GLFW_KEY_E))
	{
		AddCollisionBox(object1, object1->GetComponentByTemplate<Physics>(), true);
	}
	if (input.IsKeyTriggered(GLFW_KEY_C))
	{
		DeleteCollisionBox(object1, object1->GetComponentByTemplate<Physics>(), true);
	}

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
		}
	}
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

bool is_collisionTest = false;
void TestLevel::Collision()
{
    vector2 obj1OldPosition = object1->GetComponentByTemplate<Physics>()->GetOldPosition();
    vector2 obj2OldPosition = object2->GetComponentByTemplate<Physics>()->GetOldPosition();
    vector2 obj1Position = object1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = object2->GetComponentByTemplate<Physics>()->GetPosition();
    float distance = std::sqrt((obj1Position.x - obj2Position.x) * (obj1Position.x - obj2Position.x) + (obj1Position.y - obj2Position.y) * (obj1Position.y - obj2Position.y));

    if (object1->GetComponentByTemplate<Physics>()->IsCollideWith(object2) == true)
    {
		if (is_collisionTest == false) {
			test.Play_Sound(SOUNDS::COLLISION_SOUND);
			test.SetVolume(COLLISION_SOUND, 1);
			is_collisionTest = true;
		}
        if (object1->GetComponentByTemplate<Physics>()->GetIsGhost() != true)
        {
            object1->GetComponentByTemplate<Physics>()->SetIsCollide(true);
            object2->GetComponentByTemplate<Physics>()->SetIsCollide(true);
            object1->SetTranslation(obj1OldPosition);
            object2->SetTranslation(obj2OldPosition);
        }
		else
		{
			object1->SetTranslation(obj1Position);
			object2->SetTranslation(obj2Position);
		}
    }
	else if (distance > 700.f)
	{
		object1->GetComponentByTemplate<Physics>()->SetIsCollide(true);
		object2->GetComponentByTemplate<Physics>()->SetIsCollide(true);
		object1->SetTranslation(obj1OldPosition);
		object2->SetTranslation(obj2OldPosition);
		is_collisionTest = false;
	}
    else
    {
        object1->SetTranslation(obj1Position);
        object2->SetTranslation(obj2Position);
    }
}