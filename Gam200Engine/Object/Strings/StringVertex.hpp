/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringVertex.hpp
Author: Sinil.gang

Creation Date:
	01.01.2020
	Header file for the String Vertex Object
******************************************************************************/
#pragma once
#include <Vector2.hpp>
#include <Object/Object.hpp>

struct StringVertex
{
	StringVertex(vector2 pos, vector2 center = vector2{ 0.f }, Object* objPtr = nullptr)
		: position(pos), centerPositionOfCollidedObject(center), attachedObject(objPtr)
	{}

	bool operator==(const StringVertex& rhs) const
	{
		return (position == rhs.position);
	}
	
	vector2 position;
	vector2 centerPositionOfCollidedObject;
	Object* attachedObject;
};