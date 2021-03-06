/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   String.cpp
Author: Sinil.gang
		
Creation Date:
01.01.2020
	Source file for the String Object
******************************************************************************/
#include <algorithm>
#include <numeric>
#include <Object/Strings/String.hpp>
#include <Component/Sprite/StringSprite.hpp>
#include <Component/StringPhysics.hpp>
#include <Object/ObjectManager.hpp>
#include <Component/Physics.hpp>
#include <Component/StateMachine.hpp>
#include <States/StringStates/StringIdle.hpp>
#include <Component/MessageCapable.hpp>
#include <Object/DepthStandard.hpp>

String::String(Object* player1, Object* player2)
	: player1(player1), player2(player2)
{
	Object::AddComponent(new StringSprite(this));
	// should ctor need three pointers?
	//string->AddComponent(new StringPhysics(string, object1, object2));
	Object::AddComponent(new StringPhysics(this, player1, player2));
	Object::AddComponent(new StateMachine<String>(this));
	GetComponentByTemplate<StateMachine<String>>()->SetCurrentState(StringIdle::Get());
	Object::AddComponent(new MessageCapable(this, MessageObjects::String_Object));

	
	vertices.emplace_back(player1->GetComponentByTemplate<Physics>()->GetCollisionBox().Translation);
	vertices.emplace_back(player2->GetComponentByTemplate<Physics>()->GetCollisionBox().Translation);

	// Basic property initialize
	SetObjectName("String");
	SetObjectType(Object::ObjectType::STRING);
	SetDepth(Depth_Standard::String);
}

void String::InitString()
{
    GetComponentByTemplate<StringPhysics>()->SetShouldClear(true);
}

void String::Update(float /*dt*/)
{
}

float String::GetStringLength()
{
	float totalLength = 0.f;
	for (size_t i = 0; i < vertices.size() - 1; ++i)
	{
		totalLength += distance_between(vertices.at(i).position, vertices.at(i + 1).position);
	}
	return totalLength;
}

const std::deque<StringVertex>& String::GetVertices() const noexcept
{
	return vertices;
}

