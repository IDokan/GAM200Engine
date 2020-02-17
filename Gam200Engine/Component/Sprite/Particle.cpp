/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Particle.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 02.17.2020

	Source file for Particle System..

	1. Respawn particle
	2. Update each particles values
******************************************************************************/

#include <Component/Sprite/Particle.hpp>

Particle::Particle(Object* obj) noexcept
	: Sprite(obj)
{
}

void Particle::Init()
{
}

void Particle::Update(float dt)
{
	Sprite::Update(dt);
}

void Particle::Clear()
{
}
