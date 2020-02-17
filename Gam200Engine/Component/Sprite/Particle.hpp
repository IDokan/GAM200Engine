/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Particle.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 02.17.2020

	Header file for Particle System..

	1. Respawn particle
	2. Update each particles values
******************************************************************************/
#pragma once

#include <Component/Sprite/Sprite.hpp>

class Object;

class Particle : public Sprite
{
public:
	Particle(Object* obj) noexcept;

	void Init() override;
	void Update(float dt) override;
	void Clear() override;
	
private:
};