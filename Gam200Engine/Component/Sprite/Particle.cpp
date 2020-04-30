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
Particle::Particle(Object* obj, float newInstancesEachFrame, float startLife, size_t maxParticles, std::function<ParticleObject(void)> reviveFunc, std::function<void(ParticleObject&, float)> updateFunc) noexcept
	: Sprite(obj), shouldReviveLikeTrigger(false), triggerFlag(false), newInstancesEachFrame(newInstancesEachFrame), startLife(startLife), maxParticles(maxParticles), ReviveFunc(reviveFunc), UpdateFunc(updateFunc), timer(0.f)
{
}

void Particle::Init()
{
	Sprite::Init();
	Sprite::SetInstancingMode(Sprite::InstanceModes::ADVANCED);

	particles.reserve(maxParticles);
	for (size_t i = 0; i < maxParticles; ++i)
	{
		particles.emplace_back();
	}
}

void Particle::Update(float dt)
{

	Sprite::Update(dt);
	
	if (shouldReviveLikeTrigger == true)
	{
		ReviveDeadParticle(triggerFlag);
	}
	else
	{
		ReviveDeadParticle(dt);
	}

	UpdateAllSingleParticles(dt);
}

void Particle::Clear()
{
}

const std::vector<Particle::ParticleObject>& Particle::GetParticles() const
{
	return particles;
}

void Particle::SetNewInstancesEachFrame(float newInstancesEachFrame_) noexcept
{
	newInstancesEachFrame = newInstancesEachFrame_;
}

void Particle::SetStartLife(float startLife_) noexcept
{
	startLife = startLife_;
}

void Particle::SetShouldReviveLikeTrigger(bool should) noexcept
{
	shouldReviveLikeTrigger = should;
}

void Particle::SetTriggerFlag(bool flag) noexcept
{
	triggerFlag = flag;
}

float Particle::GetNewInstancesEachFrame() const noexcept
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
		if (IsParticleObjectDead(p))
		{
			p.color.alpha = 0.f; 
		}
		else
		{
			UpdateFunc(p, dt);
		}
	}
}

void Particle::ReviveDeadParticle(float dt)
{
	// Revive dead particle into new Alive Particle

	timer += dt;

	std::size_t newInstances = static_cast<int>(timer);

	for (unsigned int i = 0; i < newInstancesEachFrame * newInstances; ++i)
	{
		const long long unusedParticleIndex = FirstUnusedParticleObject();
		if (unusedParticleIndex == ERROR_INDEX)
		{
			break;
		}

		ParticleObject newObj = ReviveFunc();
		RespawnParticleObject(particles[unusedParticleIndex], newObj, owner->GetTranslation());
	}

	if (timer >= 1.f)
	{
		timer = timer - static_cast<int>(timer);
	}
}

void Particle::ReviveDeadParticle(bool& flag)
{
	if (flag == false)
	{
		return;
	}

	// Revive dead particle into new Alive Particle
	for (unsigned int i = 0; i < newInstancesEachFrame; ++i)
	{
		const long long unusedParticleIndex = FirstUnusedParticleObject();
		if (unusedParticleIndex == ERROR_INDEX)
		{
			break;
		}

		ParticleObject newObj = ReviveFunc();
		RespawnParticleObject(particles[unusedParticleIndex], newObj, owner->GetTranslation());
	}

	flag = false;
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
