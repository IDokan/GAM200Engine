/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Accumulating.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.27.2019

	Header file for accumulating.
******************************************************************************/
#include <Component/Accumulating.hpp>

Accumulating::Accumulating(Object* obj, bool turnOn)
	:Component(obj), isAccumulating(turnOn), accumulation(0.f)
{
}

Accumulating::~Accumulating()
{
}

void Accumulating::Init()
{
}

void Accumulating::Update(float dt)
{
	if (isAccumulating == true)
	{
		accumulation += dt;
	}
}

void Accumulating::Clear()
{
}

bool Accumulating::IsAccumulating() const noexcept
{
	return isAccumulating;
}

float Accumulating::GetAccumulation() const noexcept
{
	return accumulation;
}

void Accumulating::SetIsAccumulating(bool isAccumulating_) noexcept
{
	isAccumulating = isAccumulating_;
}
