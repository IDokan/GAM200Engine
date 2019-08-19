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
#include "TestLevel.hpp"
#include <Component/Sprite.hpp>
#include "Physics.hpp"
#include <Object/ObjectManager.hpp>
#include "Input.hpp"

void TestLevel::Load()
{
	obj.SetTranslation(vector2{ 0.f });
	obj.SetScale(vector2{ 200.f });
	obj.AddComponent(new Sprite(&obj));
    obj.AddComponent(new Physics(&obj));
    obj.GetComponentByTemplate<Physics>()->SetGravity(0.f, -1.f);
    //obj.GetComponentByTemplate<Physics>()->SetVelocity(5.f, 0.f);
	ObjectManager::GetObjectManager()->AddObject(&obj);
}

void TestLevel::Update(float dt)
{
    obj.GetComponentByTemplate<Physics>()->Update(dt);
	if (input.IsKeyTriggered(GLFW_KEY_A))
	{
		if (flag)
		{
			obj.GetComponentByTemplate<Sprite>()->SetImage("../texture/circle.png");
			flag = !flag;
		}
		else
		{
			obj.GetComponentByTemplate<Sprite>()->SetImage("../texture/rect.png");
			flag = !flag;
		}
	}
}

void TestLevel::Unload()
{
}
