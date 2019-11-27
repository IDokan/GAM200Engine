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
	StringVertex(vector2 pos, float d = 0.f)
		: position(pos), distanceWhenAdded(d)
	{}
	
	vector2 position;
	float distanceWhenAdded;
};