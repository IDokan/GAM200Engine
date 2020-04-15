/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ParticleEmitter.hpp
Author
		Il
		rtd99062@gmail.com
Creation Date: 02.17.2020

	Header file for particle emitter.
		It is emitter of particle. Thus, it have to use make a conversation with particle system.
******************************************************************************/
#pragma once

#include <Object/Object.hpp>
#include <Component/Sprite/Particle.hpp>

class ParticleEmitter : public Object
{
public:
	// TODO: Add comment that what each parameters meant to.
	ParticleEmitter(float newInstancesEachFrame, float life, size_t maxParticles, std::function<Particle::ParticleObject(void)> reviveFunc, std::function<void(Particle::ParticleObject&, float)> updateFunc);

	void SetParticleImage(const std::filesystem::path& filePath);

	const std::vector<Particle::ParticleObject>& GetParticleObjectsContainer() const;

	//  Setters
	void SetNewInstancesEachFrame(float newInstancesEachFrame) noexcept;
	void SetStartLife(float startLife) noexcept;
	
	// Getters
	float GetNewInstancesEachFrame() const noexcept;
	float GetStartLife() const noexcept;
	size_t GetMaxParticles() const noexcept;
	
private:
	Particle* particle;
};