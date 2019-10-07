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
#include "TestLevel.hpp"
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <Object/ObjectManager.hpp>
#include <Input.hpp>
#include <Graphics/GL.hpp>

void TestLevel::Load()
{
	// Set Layer
	auto objManager = ObjectManager::GetObjectManager();
	
	object2 = new Object();
	object2->SetObjectName("Object2");
	object2->SetTranslation(vector2{ 250.f });
	object2->SetScale(vector2{ 250.f });
	object2->AddComponent(new Sprite(object2));
	object2->AddComponent(new Physics(object2));
	object2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 0.f, 0.f, 1.f });
	object2->GetComponentByTemplate<Sprite>()->SetImage("../texture/circle.png");
	object2->SetDepth(-0.1f);
    object2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object2, ObjectType::CIRCLE);
	objManager->FindLayer(LayerNames::Stage)->AddObject(object2);


	object1 = new Object();
	object1->SetObjectName("Object1");
	object1->SetTranslation(vector2{ 0.f });
	object1->SetScale(vector2{ 200.f });
	object1->AddComponent(new Sprite(object1));
	object1->AddComponent(new Physics(object1));
	object1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object1, ObjectType::RECTANGLE);
	objManager->FindLayer(LayerNames::Stage)->AddObject(object1);


	object3 = new Object();
	object3->SetObjectName("Object3");
	object3->SetTranslation(vector2{ 100.f });
	object3->SetScale(vector2{ 200.f });
	object3->AddComponent(new Sprite(object3));
	object3->AddComponent(new Physics(object3));
	object3->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object3, ObjectType::CIRCLE);
	objManager->FindLayer(LayerNames::Stage)->AddObject(object3);

	object4 = new Object();
	object4->SetObjectName("Object4");
	object4->SetTranslation(vector2{ 500.f });
	object4->SetScale(vector2{ 200.f });
	object4->AddComponent(new Sprite(object4));
	object4->AddComponent(new Physics(object4));
	object4->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object4, ObjectType::CIRCLE);
	objManager->FindLayer(LayerNames::Stage)->AddObject(object4);

	object5 = new Object();
	object5->SetObjectName("Object5");
	object5->SetTranslation(vector2{ -100.f });
	object5->SetScale(vector2{ 200.f });
	object5->AddComponent(new Sprite(object5));
	object5->AddComponent(new Physics(object5));
	object5->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object5, ObjectType::CIRCLE);
	objManager->FindLayer(LayerNames::Stage)->AddObject(object5);

    
	cameraManager.Init();
}

bool isCollisionBoxShown = false;
void AddCollisionBox(Object* obj, Physics* physics)
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

		// Make Collision Box Object and Add to Object Manager
		Object* collisionBox = new Object();
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

		hudLayer->AddObject(collisionBox);
	}
}

void DeleteCollisionBox(Object* obj, Physics* physics)
{
	if (isCollisionBoxShown == false)
	{
		return;
	}
	Layer* hudLayer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD);
	// Toggle Show Var
	isCollisionBoxShown = false;
	hudLayer->DeleteObject(obj->GetObjectName() + " CollisionBox");
}

void TestLevel::Update(float dt)
{
    TestLevel::Input();
    
	// Code for test Physics thing by Woo
    if (object1->GetComponentByTemplate<Physics>()->IsCollideWith(object2) == true)
    {
        std::cout << "colliding!!" << std::endl;
    }
   
	cameraManager.CameraMove(1.1f);

	if (input.IsKeyTriggered(GLFW_KEY_Q))
	{
		AddCollisionBox(object1, object1->GetComponentByTemplate<Physics>());
	}
	if (input.IsKeyTriggered(GLFW_KEY_Z))
	{
		DeleteCollisionBox(object1, object1->GetComponentByTemplate<Physics>());
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
		}
	}

	Graphics::GL::end_drawing();
}

void TestLevel::Input()
{

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
}