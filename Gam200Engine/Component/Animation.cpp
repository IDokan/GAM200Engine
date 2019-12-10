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
#include "Component/Animation.hpp"
#include "Graphics/StockShaders.hpp"

Animation::Animation(Object* obj) noexcept
	: Sprite(obj), frame(1), speed(1.f), index(0.f)
{

	// Animation Stuffs
	material->intUniform[Graphics::SHADER::Uniform_Frame] = frame;
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
	material->intUniform[Graphics::SHADER::Uniform_Frame] = frame = frame_;
}

float Animation::GetSpeed() const noexcept
{
	return speed;
}

void Animation::SetSpeed(float speed_) noexcept
{
	speed = speed_;
}