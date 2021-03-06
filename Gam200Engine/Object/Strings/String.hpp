/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   String.hpp
Author: sinil.gang

Creation Date:
01.01.2020
	Header file for the String Object
******************************************************************************/
#pragma once
#include <deque>
#include "Object/Object.hpp"
#include "Object/Strings/StringVertex.hpp"

class StringPhysics;
class StringSprite;

class String : public Object
{
    friend StringPhysics;
    friend StringSprite;
public:
    static constexpr const size_t maxVertexSize = 60;
	static constexpr const float String_Stretching_Length = 500.f;
	static constexpr const float String_Max_Length = 800.f;
	
public:
	String(Object* player1, Object* player2);


	void InitString();
	void Update(float dt);

	float GetStringLength();
	const std::deque<StringVertex>& GetVertices() const noexcept;
private:
	std::deque<StringVertex> vertices;
	Object* player1;
	Object* player2;
};