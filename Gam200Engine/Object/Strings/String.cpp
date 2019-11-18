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
	:verticesCapacity(0)
{
	AddComponent(new StringSprite(this));
	// should ctor need three pointers?
	//string->AddComponent(new StringPhysics(string, object1, object2));
	AddComponent(new StringPhysics(this));

	
	vertices.push_back(vector2{0.f});
}

void String::Update(float dt)
{
	// Check -> collision
	// vertices draw - Il
}

size_t String::GetVertexSize() const noexcept
{
	return maxVertexSize;
}