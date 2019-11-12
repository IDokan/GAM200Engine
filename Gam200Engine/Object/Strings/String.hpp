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
#include "Object/Strings/StringPiece.hpp"
#include "Object/Strings/StringVertex.hpp"
#include <list>

class String : public Object
{
public:
	String() = default;
	// Ctor should get a position of both players. How can it be?
	String(Transform position1, Transform position2);

private:
	std::vector<StringPiece> strings;
	std::list<StringVertex> vertices;
};