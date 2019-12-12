/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   WallSpawner.hpp
Author
	- Sinil.Kang rtd99062@gmail.com

Creation Date: 12.12.2019

	Header file for object that make add object
******************************************************************************/
#pragma once
#include <Object/Object.hpp>

class WallSpawner : public Object
{
public:
	WallSpawner();
	virtual ~WallSpawner();

	void SpawnWall();
	
private:
	size_t counter;
};