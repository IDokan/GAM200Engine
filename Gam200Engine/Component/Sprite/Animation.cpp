/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Animation.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 10.27.2019

	Header file for Animation Component
******************************************************************************/
#include <Component/Sprite/Animation.hpp>
#include <Graphics/StockShaders.hpp>

Animation::Animation(Object* obj) noexcept
	: Sprite(obj), frame(1), speed(0.f), index(0.f), animationState(0), numOfState(1)
{
	// Animation Stuffs
	material->intUniform[Graphics::SHADER::Uniform_Frame] = frame;
	material->intUniform[Graphics::SHADER::Uniform_State] = animationState;
	material->intUniform[Graphics::SHADER::Uniform_Max_State] = numOfState;
}

void Animation::Init()
{
	Sprite::Init();
	material->shader = &Graphics::SHADER::animated();
}

void Animation::Update(float dt)
{
	Sprite::Update(dt);

	index += dt * speed;
	SendIndex();
}

void Animation::Clear()
{
	Sprite::Clear();
}

int Animation::Clamp(int targetValue, int maxValue, int minValue) const noexcept
{
	if (targetValue > maxValue)
	{
		return maxValue;
	}
	else if (targetValue < minValue)
	{
		return minValue;
	}
	else
	{
		return targetValue;
	}
}

void Animation::SendIndex() const noexcept
{
	material->intUniform[Graphics::SHADER::Uniform_Index] = static_cast<int>(ceil(int(index) % frame));
}

int Animation::GetFrame() const noexcept
{
	return frame;
}

void Animation::SetFrame(int frame_) noexcept
{
	frame = frame_;
	material->intUniform[Graphics::SHADER::Uniform_Frame] = frame;
}

float Animation::GetSpeed() const noexcept
{
	return speed;
}

int Animation::GetState() const noexcept
{
	return animationState;
}

int Animation::GetNumOfState() const noexcept
{
	return numOfState;
}

void Animation::SetSpeed(float speed_) noexcept
{
	speed = speed_;
}

void Animation::SetState(int state_) noexcept
{
	state_ = Clamp(state_, numOfState - 1);

	animationState = state_;
	material->intUniform[Graphics::SHADER::Uniform_State] = animationState;
}

void Animation::SetNumOfState(int numOfState_) noexcept
{
	numOfState = numOfState_;
	material->intUniform[Graphics::SHADER::Uniform_Max_State] = numOfState;
}
