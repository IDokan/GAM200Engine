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

/**
 * \brief parameter input:
 * speed : vector2 - speed vector that particle would move.
 * translation : vector2 - translation of particles (Specific purpose & description are TBD)
 * transparencyAdjustValue : float - how fast particles going to be invisible. (particle.alpha -= dt * transparencyAdjustValue)
 * newInstancesEachFrame : size_t - how many instances respawn in each frame.
 * life : float - start life of each particle objects
 * numParticles : size_t - maximum size of particle.
 */
Particle::Particle(Object* obj, vector2 speed, vector2 translation, float transparencyAdjustValue, size_t newInstancesEachFrame, float startLife, size_t maxParticles) noexcept
	: Sprite(obj), speed(speed), translation(translation), transparencyAdjustValue(transparencyAdjustValue), newInstancesEachFrame(newInstancesEachFrame), startLife(startLife), maxParticles(maxParticles)
{
}

void Particle::Init()
{
	Sprite::SetInstancingMode(true);

	particles.reserve(maxParticles);
	for (size_t i = 0; i < maxParticles; ++i)
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

void Particle::SetSpeed(vector2 speed_) noexcept
{
	speed = speed_;
}

void Particle::SetTranslation(vector2 translation_) noexcept
{
	translation = translation_;
}

void Particle::SetTransparencyAdjustValue(float transparencyAdjustValue_) noexcept
{
	transparencyAdjustValue = transparencyAdjustValue_;
}

void Particle::SetNewInstancesEachFrame(size_t newInstancesEachFrame_) noexcept
{
	newInstancesEachFrame = newInstancesEachFrame_;
}

void Particle::SetStartLife(float startLife_) noexcept
{
	startLife = startLife_;
}

vector2 Particle::GetSpeed() const noexcept
{
	return speed;
}

vector2 Particle::GetTranslation() const noexcept
{
	return translation;
}

float Particle::GetTransparencyAdjustValue() const noexcept
{
	return transparencyAdjustValue;
}

size_t Particle::GetNewInstancesEachFrame() const noexcept
{
	return newInstancesEachFrame;
}

float Particle::GetStartLife() const noexcept
{
	return startLife;
}

size_t Particle::GetMaxParticles() const noexcept
{
	return maxParticles;
}

void Particle::UpdateAllSingleParticles(float dt)
{
	for (size_t i = 0; i < maxParticles; ++i)
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
	for (unsigned int i = 0; i < newInstancesEachFrame; ++i)
	{
		const long long unusedParticleIndex = FirstUnusedParticleObject();
		if (unusedParticleIndex == ERROR_INDEX)
		{
			break;
		}

		// TODO: Set position, velocity required

		ParticleObject newObj;
		RespawnParticleObject(particles[unusedParticleIndex], newObj);
	}
}

long long Particle::FirstUnusedParticleObject() const
{
	static size_t lastUsedParticleObject = 0;

	// Search from last used particle, this will usually return almost instantly
	for (size_t i = lastUsedParticleObject; i < maxParticles; ++i)
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
