/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   String.cpp
Author
		
Creation Date:

	Source file for the String Object
******************************************************************************/
#include <Object/Strings/String.hpp>
#include "Component/StringSprite.hpp"
#include <Component/StringPhysics.hpp>
#include <Object/ObjectManager.hpp>
#include "Component/Physics.hpp"

String::String(Object* player1, Object* player2)
{
	Object::AddComponent(new StringSprite(this));
	// should ctor need three pointers?
	//string->AddComponent(new StringPhysics(string, object1, object2));
	Object::AddComponent(new StringPhysics(this, player1, player2));

	
	vertices.emplace_back(player1->GetTranslation());
	vertices.emplace_back(player2->GetTranslation());
}

void String::Update(float dt)
{
}

