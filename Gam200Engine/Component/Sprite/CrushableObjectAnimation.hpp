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
#pragma once
#include <Component/Sprite/Animation.hpp>

class CrushableObjectAnimation : public Animation
{
public:
	CrushableObjectAnimation(Object* obj) noexcept;
	virtual ~CrushableObjectAnimation() noexcept = default;
	// No Clear()
	// It can be dangerous..
	// Currently, I do not know..
	virtual void Init();
	virtual void Update(float dt);
};