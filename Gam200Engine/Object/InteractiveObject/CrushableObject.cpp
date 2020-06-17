/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CrushableObject.cpp
Author: dbsqhd106@gmail.com

Creation Date: DEC/11st/2019

    Header file for the test object whether interact work or not
******************************************************************************/

#include <Object/InteractiveObject/CrushableObject.hpp>
#include <Component/Sprite/CrushableObjectAnimation.hpp>
#include <Component/Physics.hpp>
#include <Scenes/Scene.hpp>//
#include <Scenes/SceneManager.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/Scripts/Accumulating.hpp>

#include <Object/Particles/ParticleEmitter.hpp>
#include <Object/DepthStandard.hpp>
#include <Object/ObjectManager.hpp>

#include <Scenes/SceneManager.hpp>

CrushableObject::CrushableObject(vector2 _objPos, vector2 _objScale,
    Physics::ObjectType _objType, String  *_currentString ) : InteractiveObject(),
    objPos(_objPos), objScale(_objScale), objType(_objType),currentString(_currentString)
{
	Object::AddComponent(new Accumulating(this, 5.f));
    Object::AddComponent(new CrushableObjectAnimation(this));
    SetTranslation(objPos);
    SetScale(objScale);
    Object::AddComponent(new Physics(this));
    SetObjectType(Object::ObjectType::JAIL);
    GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, objType);
    SetDepth(-0.1f);


	// From confetti, have to change into dust..
	destructiveParticle = new ParticleEmitter(12, 5.f, 12, [&]() ->Particle::ParticleObject
		{
			Particle::ParticleObject p;
			p.color = Graphics::Color4f(0.65f);
			p.transform.SetScale(vector2{ 10.f });
			float rotation = (rand() % 314) / 100.f;
			p.transform.SetRotation(rotation);
			float x = ((rand() % 200) / 100.f) - 1.f;
			float y = ((rand() % 200) / 100.f) - 1.f;

			p.transform.SetTranslation((vector2{ x * GetScale().x, y * GetScale().y } + GetTranslation()));

			p.velocity = vector2{ 5.f * x, 5.f * y };
			p.life = rand() % 5;

			float scalar = rand() % 100 / 200.f;
			p.textureCoordinateScalar = vector2(scalar);

			return p;
		},
		[&](Particle::ParticleObject& p, float dt)
		{
			p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * 50.f * dt));
		}
		);
	destructiveParticle->SetObjectName("Destructive particle Emitter");
	destructiveParticle->SetParticleImage("../assets/textures/destructedJailSprite.png");
	destructiveParticle->SetShouldReviveLikeTrigger(true);
	destructiveParticle->SetDepth(Depth_Standard::Jail);

	ObjectManager::GetObjectManager()->FindLayer(Stage)->AddObject(destructiveParticle);
  /*
     SoundManager soundManager = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
     soundManager.Load_Sound();
     soundManager.Play_Sound(CRUSH_SOUND);
     soundManager.SetVolume(CRUSH_SOUND,1);*/
}

CrushableObject::~CrushableObject()
{
}

void CrushableObject::DoSomethingWhenAttached()
{
    if (attachedNum - detachedNum > 4)
    {
		GetComponentByTemplate<Accumulating>()->SetIsAccumulating(true);
    }
}

void CrushableObject::DoSomethingWhenDetached()
{
	if (attachedNum - detachedNum <= 4)
	{
		GetComponentByTemplate<Accumulating>()->SetIsAccumulating(false);
	}
}

void CrushableObject::Crushed() noexcept
{
    SoundManager sm = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
	sm.Play_Sound(SOUNDS::CRUSH_SOUND);

    SceneManager::GetSceneManager()->GetCurrentScene()->GetCameraManager().StartShakingCamera(0.6f, 6.f);
	currentString->GetComponentByTemplate<StringPhysics>()->DeletePositionsWithObject(this);
	destructiveParticle->SetTriggerFlag(true);
	SetDead(true);
	
}
