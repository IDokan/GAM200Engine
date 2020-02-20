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

ParticleEmitter::ParticleEmitter(vector2 speed, vector2 speedOffset, vector2 translation, vector2 translationOffset,
	size_t numOfNewInstancesEachFrame)
	: speed(speed), speedOffset(speedOffset), translationOffset(translationOffset)
{
	Object::SetTranslation(translation);
	AddComponent(new Particle(this, 0.0f, 1.f, 5.f));
}

void ParticleEmitter::SetParticleImage(const std::filesystem::path& filePath)
{
	GetComponentByTemplate<Particle>()->SetImage(filePath);
}

const std::vector<Particle::ParticleObject>& ParticleEmitter::GetParticleObjectsContainer() const
{
	return GetComponentByTemplate<Particle>()->GetParticles();
}

void ParticleEmitter::SetSpeed(vector2 speed)
{
}

void ParticleEmitter::SetSpeedOffset(vector2 speedOffset)
{
}

void ParticleEmitter::SetTranslationOffset(vector2 translationOffset)
{
}

void ParticleEmitter::SetNumOfNewInstancesEachFrame(size_t numOfNewInstancesEachFrame)
{
}
