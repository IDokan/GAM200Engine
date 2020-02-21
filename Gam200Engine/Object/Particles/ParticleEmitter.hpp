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
	ParticleEmitter(vector2 speed, vector2 translation, float transparencyAdjustValue = 0.f, size_t newInstancesEachFrame = 1U, float life = 5.f, size_t maxParticles = 500U);

	void SetParticleImage(const std::filesystem::path& filePath);

	const std::vector<Particle::ParticleObject>& GetParticleObjectsContainer() const;

	//  Setters
	void SetSpeed(vector2 speed) noexcept;
	void SetTranslation(vector2 translation) noexcept;
	void SetTransparencyAdjustValue(float transparencyAdjustValue) noexcept;
	void SetNewInstancesEachFrame(size_t newInstancesEachFrame) noexcept;
	void SetStartLife(float startLife) noexcept;
	
	// Getters
	vector2 GetSpeed() const noexcept;
	vector2 GetTranslation() const noexcept;
	float GetTransparencyAdjustValue() const noexcept;
	size_t GetNewInstancesEachFrame() const noexcept;
	float GetStartLife() const noexcept;
	size_t GetMaxParticles() const noexcept;
	
private:
	Particle* particle;
};