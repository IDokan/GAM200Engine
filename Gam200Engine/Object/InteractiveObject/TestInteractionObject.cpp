/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TestInteractionObject.hpp
Author
		rtd99062@gmail.com
Creation Date: 12.09.2019

	Source file for the test object whether interact work or not
******************************************************************************/
#include <Object/InteractiveObject/TestInteractionObject.hpp>
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>

TestInteractionObject::TestInteractionObject()
	: InteractiveObject()
{
	Object::AddComponent(new Sprite(this));
	SetTranslation(vector2{ 500.f, 200.f });
	SetScale(100.f);
	Object::AddComponent(new Physics(this));
	GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, Physics::ObjectType::RECTANGLE);
}

TestInteractionObject::~TestInteractionObject()
{
}

void TestInteractionObject::DoSomethingWhenAttached()
{
	GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 0.f, 0.f });

	if (attachedNum - detachedNum > 4)
	{
		SetDead(true);
	}
}

void TestInteractionObject::DoSomethingWhenDetached()
{
	GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f });
}