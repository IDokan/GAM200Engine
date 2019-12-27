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
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/Accumulating.hpp>

SoundManager TestSoundforCrush;

CrushableObject::CrushableObject(vector2 _objPos, vector2 _objScale,
    Physics::ObjectType _objType, String  *_currentString ) : InteractiveObject(),
    objPos(_objPos), objScale(_objScale), objType(_objType),currentString(_currentString)
{
    Object::AddComponent(new Sprite(this));
    SetTranslation(objPos);
    SetScale(objScale);
    Object::AddComponent(new Physics(this));
    SetObjectType(Object::ObjectType::OBSTACLE);
    GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, objType);
    SetDepth(-0.1f);
	Object::AddComponent(new Accumulating(this));

    /////
    TestSoundforCrush.Load_Sound();
    TestSoundforCrush.SetVolume(CRUSH_SOUND, 1);
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
	TestSoundforCrush.Play_Sound(SOUNDS::CRUSH_SOUND);
	SetDead(true);
	currentString->GetComponentByTemplate<StringPhysics>()->DeletePositionsWithObject(this);
}
