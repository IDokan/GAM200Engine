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

String::String()
{
	AddComponent(new StringSprite(this));
	// should ctor need three pointers?
	//string->AddComponent(new StringPhysics(string, object1, object2));
	//AddComponent(new StringPhyscis(this));


	vertices.push_back(vector2{0.f});
	vertices.push_back(vector2{ 100.f});
	vertices.push_back(vector2{ 200.f, 200.f });
}

void String::Update(float dt)
{
	// Check -> collision
	// vertices draw - Il
}

std::vector<vector2>& String::GetVertices() noexcept
{
	return vertices;
}
