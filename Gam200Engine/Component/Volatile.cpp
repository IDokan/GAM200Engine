#include "Volatile.hpp"
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
#include <Object/Object.hpp>
#include <Component/Physics.hpp>
#include <assert.h>

Volatile::Volatile(Object* obj) noexcept
	:Component(obj)
{
}

void Volatile::Init()
{
	assert(owner->GetComponentByTemplate<Physics>() != nullptr && "Owner should have Physics Component!");
}

void Volatile::Update(float /*dt*/)
{
	if (owner->GetComponentByTemplate<Physics>()->IsCollided())
	{
		owner->SetDead(true);
	}
}

void Volatile::Clear()
{

}
