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
private:
	const size_t maxVertexSize = 50;
	
public:
	String();

	void Update(float dt);

	[[nodiscard]] size_t GetVertexSize() const noexcept;

private:
	std::vector<vector2> vertices;
	int verticesCapacity;
};