/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   CrushableObjectAnimation.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.28.2019

	Header file for Animation Component in CrushableObject
		The only difference is Update() function.
******************************************************************************/
#include <Component/Sprite/CrushableObjectAnimation.hpp>
#include <Component/Scripts/Accumulating.hpp>
#include <Object/InteractiveObject/CrushableObject.hpp>

CrushableObjectAnimation::CrushableObjectAnimation(Object* obj) noexcept
	:Animation(obj)
{
}

void CrushableObjectAnimation::Init()
{
	Animation::Init();

	constexpr int numOfStateInCrushableImage = 5;
	SetNumOfState(numOfStateInCrushableImage);
	SetImage("../assets/textures/Jail.png");
}

void CrushableObjectAnimation::Update(float dt)
{
	Animation::Update(dt);

	const float maximum = owner->GetComponentByTemplate<Accumulating>()->GetMaximum();
	const float accumulation = owner->GetComponentByTemplate<Accumulating>()->GetAccumulation();

	// If accumulation is accumulated enough, crush owner!
	if (accumulation > maximum)
	{
		if (CrushableObject* obj = dynamic_cast<CrushableObject*>(owner);
			obj != nullptr)
		{
			obj->Crushed();
		}
	}

	// Set State with given accumulation
	SetState(static_cast<int>(accumulation*numOfState / maximum));
}
