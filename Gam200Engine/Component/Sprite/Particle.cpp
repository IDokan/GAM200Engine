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

Particle::Particle(Object* obj, float life, size_t numOfParticleObjects) noexcept
	: Sprite(obj), sizeOfParticles(numOfParticleObjects), defaultLife(life)
{
}

void Particle::Init()
{
	Sprite::SetInstancingMode(true);

	particles.reserve(sizeOfParticles);
	for (size_t i = 0; i < sizeOfParticles; ++i)
	{
		particles.emplace_back();
	}
}

void Particle::Update(float dt)
{
	Sprite::Update(dt);

	ReviveDeadParticle();

	UpdateAllSingleParticles(dt);
}

void Particle::Clear()
{
}

const std::vector<Particle::ParticleObject>& Particle::GetParticles() const
{
	return particles;
}

void Particle::UpdateAllSingleParticles(float dt)
{
	for (size_t i = 0; i < sizeOfParticles; ++i)
	{
		ParticleObject& p = particles[i];
		p.life -= dt;
		if (!IsParticleObjectDead(p))
		{
			p.transform.SetTranslation(p.transform.GetTranslation() + p.velocity * dt);
			p.color.alpha -= dt * transparencyAdjustValue;
		}
	}
}

void Particle::ReviveDeadParticle()
{
	// Revive dead particle into new Alive Particle
	for (unsigned int i = 0; i < numOfNewInstancesEachFrame; ++i)
	{
		const long long unusedParticleIndex = FirstUnusedParticleObject();
		if (unusedParticleIndex == ERROR_INDEX)
		{
			break;
		}
		/*	Set position, velocity required
		 *
		 */
		ParticleObject newObj;
		RespawnParticleObject(particles[unusedParticleIndex], newObj);
	}
}

long long Particle::FirstUnusedParticleObject() const
{
	static size_t lastUsedParticleObject = 0;

	// Search from last used particle, this will usually return almost instantly
	for (size_t i = lastUsedParticleObject; i < sizeOfParticles; ++i)
	{
		if (IsParticleObjectDead(particles[i]))
		{
			lastUsedParticleObject = i;
			return i;
		}
	}
	// Otherwise, do a linear search
	for (size_t i = 0; i < lastUsedParticleObject; ++i)
	{
		if (IsParticleObjectDead(particles[i]))
		{
			lastUsedParticleObject = i;
			return i;
		}
	}

	// Otherwise, return -1
	return ERROR_INDEX;
}

void Particle::RespawnParticleObject(ParticleObject& particleObject, ParticleObject& newObject, vector2 offset)
{
	particleObject = newObject + offset;
}

bool Particle::IsParticleObjectDead(const ParticleObject& particleObject) const
{
	return particleObject.life <= 0.f;
}
