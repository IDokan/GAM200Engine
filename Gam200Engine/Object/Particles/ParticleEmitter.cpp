/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ParticleEmitter.cpp
Author
		Il
		rtd99062@gmail.com
Creation Date: 02.17.2020

	Source file for Particle system interface
******************************************************************************/
#include <Object/Particles/ParticleEmitter.hpp>

ParticleEmitter::ParticleEmitter(size_t newInstancesEachFrame, float life, size_t maxParticles,
	std::function<Particle::ParticleObject(void)> reviveFunc, std::function<void(Particle::ParticleObject&)> updateFunc)
{
	AddComponent(new Particle(this, newInstancesEachFrame, life, maxParticles, reviveFunc, updateFunc));

	particle = GetComponentByTemplate<Particle>();
}

void ParticleEmitter::SetParticleImage(const std::filesystem::path& filePath)
{
	GetComponentByTemplate<Particle>()->SetImage(filePath);
}

const std::vector<Particle::ParticleObject>& ParticleEmitter::GetParticleObjectsContainer() const
{
	return GetComponentByTemplate<Particle>()->GetParticles();
}

void ParticleEmitter::SetNewInstancesEachFrame(size_t newInstancesEachFrame) noexcept
{
	particle->SetNewInstancesEachFrame(newInstancesEachFrame);
}

void ParticleEmitter::SetStartLife(float startLife) noexcept
{
	particle->SetStartLife(startLife);
}

size_t ParticleEmitter::GetNewInstancesEachFrame() const noexcept
{
	return particle->GetNewInstancesEachFrame();
}

float ParticleEmitter::GetStartLife() const noexcept
{
	return 0.0f;
}

size_t ParticleEmitter::GetMaxParticles() const noexcept
{
	return particle->GetMaxParticles();
}
