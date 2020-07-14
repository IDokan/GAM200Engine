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
#include <Component/Scripts/Accumulating.hpp>
#include <Scenes/SceneManager.hpp>

Accumulating::Accumulating(Object* obj, float maximum, bool turnOn) noexcept
	:Component(obj), maximum(maximum), isAccumulating(turnOn), accumulation(0.f)
{
}

void Accumulating::Init()
{
}


void Accumulating::Update(float dt)
{
	if (accumulation > maximum)
	{
		return;
	}

	if (isAccumulating == false)
	{
		accumulation = 0.f;
		return;
	}

	accumulation += dt;
	SceneManager::GetSceneManager()->GetCurrentScene()->GetCameraManager().StartZoomFromOutside(true, accumulation / maximum);
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

float Accumulating::GetMaximum() const noexcept
{
	return maximum;
}

void Accumulating::SetIsAccumulating(bool isAccumulating_) noexcept
{
	isAccumulating = isAccumulating_;
}

void Accumulating::SetMaximum(float maximum_) noexcept
{
	maximum = maximum_;
}
