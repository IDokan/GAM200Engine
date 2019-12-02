/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringVertex.hpp
Author

Creation Date:

	Header file for the String Vertex Object
******************************************************************************/
#pragma once
#include "Vector2.hpp"

struct StringVertex
{
	StringVertex(vector2 pos, vector2 center = vector2{ 0.f })
		: position(pos), centerPositionOfCollidedObject(center)
	{}

	bool operator==(const StringVertex& rhs) const
	{
		return (position == rhs.position);
	}
	
	vector2 position;
	vector2 centerPositionOfCollidedObject;
};