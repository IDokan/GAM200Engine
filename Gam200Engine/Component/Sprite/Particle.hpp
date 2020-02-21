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
	// Struct of Individual single small localized object
	struct ParticleObject
	{
		Transform transform;
		vector2 velocity;
		Graphics::Color4f color;
		float life;

		ParticleObject()
			: velocity(0.f), color(1.f), life(0.f)
		{}

		ParticleObject& operator=(const ParticleObject& rhs)
		{
			transform = rhs.transform;
			velocity = rhs.velocity;
			color = rhs.color;
			life = rhs.life;

			return *this;
		}

		ParticleObject& operator+(const vector2& offset)
		{
			transform.SetTranslation(transform.GetTranslation() + offset);
			return *this;
		}
	};

	static const int ERROR_INDEX = -1;
public:
	Particle(Object* obj, vector2 speed, vector2 translation, float transparencyAdjustValue, size_t newInstancesEachFrame, float startLife, size_t maxParticles) noexcept;

	void Init() override;
	void Update(float dt) override;
	void Clear() override;

	const std::vector<Particle::ParticleObject>& GetParticles() const;

	// Setters
	void SetSpeed(vector2 speed_) noexcept;
	void SetTranslation(vector2 translation_) noexcept;
	void SetTransparencyAdjustValue(float transparencyAdjustValue_) noexcept;
	void SetNewInstancesEachFrame(size_t newInstancesEachFrame_) noexcept;
	void SetStartLife(float startLife_) noexcept;

	// Getters
	vector2 GetSpeed() const noexcept;
	vector2 GetTranslation() const noexcept;
	float GetTransparencyAdjustValue() const noexcept;
	size_t GetNewInstancesEachFrame() const noexcept;
	float GetStartLife() const noexcept;
	size_t GetMaxParticles() const noexcept;

private:
	void UpdateAllSingleParticles(float dt);
	void ReviveDeadParticle();
	long long FirstUnusedParticleObject() const;
	void RespawnParticleObject(ParticleObject& particleObject, ParticleObject& newObject, vector2 offset = vector2{0.f});	bool IsParticleObjectDead(const ParticleObject& particleObject) const;
	
private:
	vector2 speed;
	vector2 translation;

	float transparencyAdjustValue;
	
	size_t newInstancesEachFrame;

	float startLife;
	const size_t maxParticles;
	std::vector<ParticleObject> particles;
};