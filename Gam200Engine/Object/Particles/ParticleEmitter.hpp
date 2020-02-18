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
	ParticleEmitter(vector2 speed, vector2 speedOffset, vector2 translation, vector2 translationOffset, size_t numOfNewInstancesEachFrame = 1);

	void SetParticleImage();

	const std::vector<Particle::ParticleObject>& GetParticleObjectsContainer() const;

	//  Setters
	void SetSpeed(vector2 speed);
	void SetSpeedOffset(vector2 speedOffset);
	void SetTranslationOffset(vector2 translationOffset);
	void SetNumOfNewInstancesEachFrame(size_t numOfNewInstancesEachFrame);
	
private:
	vector2 speed;
	vector2 speedOffset;
	vector2 translationOffset;
};