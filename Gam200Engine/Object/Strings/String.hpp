/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   String.hpp
Author

Creation Date:

	Header file for the String Object
******************************************************************************/
#pragma once
#include "Object/Object.hpp"
#include "Object/Strings/StringVertex.hpp"
#include <deque>

class StringPhysics;
class StringSprite;

class String : public Object
{
    friend StringPhysics;
    friend StringSprite;
public:
    static constexpr const size_t maxVertexSize = 60;
	
public:
	String(Object* player1, Object* player2);

	void Update(float dt);

	float GetStringLength();
private:
	std::deque<StringVertex> vertices;
};