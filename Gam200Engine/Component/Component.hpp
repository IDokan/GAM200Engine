/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
        dbsqhd106@gmail.com
Creation Date: 08.12.2019

    Header file for the Application.cpp
******************************************************************************/
#pragma once

class Object;

class Component
{
public:
	explicit Component(Object*) noexcept;
	virtual ~Component() noexcept = default;

public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clear() = 0;

protected:
	Object* owner;
};

