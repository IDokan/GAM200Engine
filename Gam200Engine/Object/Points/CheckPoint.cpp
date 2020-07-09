/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   CheckPoint.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 06.29.2020

	Source file for Check Point
		When player is on this (Check Point), save progress
******************************************************************************/
#include <Object/Points/CheckPoint.hpp>
#include <Object/DepthStandard.hpp>

#include <Component/Sprite/Animation.hpp>
#include <Component/Scripts/CheckPointComponent.hpp>

#include <Object/Particles/ParticleEmitter.hpp>
#include <Object/ObjectManager.hpp>

CheckPoint::CheckPoint(const vector2& translation, Player* ptrToPlayer1, Player* ptrToPlayer2)
{
	SetTranslation(translation);
	SetScale(vector2{ 300.f, 270.f });
	SetDepth(Depth_Standard::Points);

	// TODO: Have to add Refrigerator image
	Animation* checkAnimation = new Animation(this);
	checkAnimation->SetImage("../assets/textures/Refrigerator.png");
	checkAnimation->SetNumOfState(2);
	checkAnimation->SetState(0);
	checkAnimation->SetSpeed(0.f);
	AddComponent(checkAnimation);

	SetObjectName("CheckPoint");

	coldEmitter = new ParticleEmitter(6.f, 12.5f, 100.f, [&]() -> Particle::ParticleObject
		{
			Particle::ParticleObject p;
			p.color = Graphics::Color4f(0.f, 1.f, 1.f, 0.65f);
			p.transform.SetScale(vector2{ 10.f });
			vector2 ownerScale = GetScale();
			float x = ((rand() % static_cast<int>(ownerScale.x)) - (ownerScale.x / 2.f)) * 0.6f;
			float ty = rand() % 10 - 5.f;
			p.transform.SetTranslation(GetTranslation() + vector2{x, -(ownerScale.y / 8.f) + ty});


			float y = rand() % 20;
			p.velocity = vector2{ x / 10.f, y };
			p.life = 12.5f;

			return p;
		},
		[&](Particle::ParticleObject& p, float dt)
		{
			float yBound = GetTranslation().y - (GetScale().y / 3.f);
			p.velocity.y -= 9.8 * dt;
			p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * dt));

			if (p.transform.GetTranslation().y < yBound)
			{
				p.transform.SetTranslation(vector2{ p.transform.GetTranslation().x, yBound });
				p.velocity.y = -p.velocity.y / 2.f;
				p.color.alpha /= 2.f;
				if (p.color.alpha <= 0.1f)
				{
					p.life = -1.f;
				}
			}
		}
		);
	coldEmitter->SetParticleImage("../assets/textures/circle.png");
	coldEmitter->SetDepth(Depth_Standard::ColdVFX);
	coldEmitter->SetShouldReviveParticle(false);
	ObjectManager::GetObjectManager()->FindLayer(Stage)->AddObject(coldEmitter);

	AddComponent(new CheckPointComponent(this, ptrToPlayer1, ptrToPlayer2));
}

void CheckPoint::SetEmitterOn(bool isOn)
{
	coldEmitter->SetShouldReviveParticle(isOn);
}
