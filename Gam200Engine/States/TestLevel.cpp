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
	object1 = new Object();
	object1->SetTranslation(vector2{ 150.f,150.f });
	object1->SetScale(vector2{ 200.f });
	object1->AddComponent(new Sprite(object1));
	object1->AddComponent(new Physics(object1));
    //object1->GetComponentByTemplate<Physics>()->SetGravity(0.f, -1.f);
    //object1->GetComponentByTemplate<Physics>()->SetPosition(vector2(300.f, 300.f));
	ObjectManager::GetObjectManager()->AddObject(object1);

	object2 = new Object();
	object2->SetTranslation(vector2{ 250.f });
	object2->SetScale(vector2{ 250.f });
	object2->AddComponent(new Sprite(object2));
	object2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 0.f, 0.f, 1.f });
	ObjectManager::GetObjectManager()->AddObject(object2);

	cameraManager.Init();
}

void TestLevel::Update(float dt)
{
	// Code for test Physics thing by Woo
    if (object1->GetComponentByTemplate<Physics>()->IsCollideWith(object2) == true)
    {
        std::cout << "colliding!!" << std::endl;
    }
    if (input.IsKeyPressed(GLFW_KEY_W))
    {
		object1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
    }
    if (input.IsKeyPressed(GLFW_KEY_A))
    {
		object1->GetComponentByTemplate<Physics>()->SetDirection(-3.f, 0.f);
    }
    if (input.IsKeyPressed(GLFW_KEY_S))
    {
		object1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);
    }
    if (input.IsKeyPressed(GLFW_KEY_D))
    {
		object1->GetComponentByTemplate<Physics>()->SetDirection(3.f, 0.f);
    }
    if (input.IsKeyReleased(GLFW_KEY_W) && input.IsKeyReleased(GLFW_KEY_S))
    {
        object1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }
    if (input.IsKeyReleased(GLFW_KEY_A) && input.IsKeyReleased(GLFW_KEY_D) )
    {
		object1->GetComponentByTemplate<Physics>()->SetDirection(0.f, 0.f);
    }
    if (input.IsKeyTriggered(GLFW_KEY_SPACE))
    {
        object1->GetComponentByTemplate<Physics>()->AddForce(0.f, 0.1f);
    }
	cameraManager.CameraMove(1.1f);
}

void TestLevel::Unload()
{
}

void TestLevel::Draw() const noexcept
{
	Graphics::GL::begin_drawing();

	for (const auto & obj: ObjectManager::GetObjectManager()->GetObjectManagerContainer())
	{
		// I know there is efficient grammar in c++11
		if (const auto & sprite = obj.get()->GetComponentByTemplate<Sprite>())
		{
			// is it located in a right place?
			sprite->UpdateUniforms(cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld(), 
				obj.get()->GetTransform().CalculateWorldDepth());
			Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());
		}
	}

	Graphics::GL::end_drawing();
}
