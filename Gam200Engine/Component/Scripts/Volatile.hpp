/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Volatile.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.04.2019

	Header file for Volatile Component Implementation
		that when collided with something become dead
******************************************************************************/
#pragma once

#include <Component/Component.hpp>

class Volatile : public Component
{
public:
	Volatile(Object* obj) noexcept;
	virtual ~Volatile() noexcept = default;

	virtual void Init();
	virtual void Update(float dt);
	virtual void Clear();

	
private:

};