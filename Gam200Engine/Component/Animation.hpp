/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Animation.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 10.27.2019

	Header file for Animation Component
******************************************************************************/
#pragma once
#include "Component/Sprite.hpp"

class Animation : public Sprite
{
public:
	Animation(Object* obj) noexcept;
	virtual ~Animation() noexcept = default;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual	void Clear() override;

	int GetFrame() const noexcept;
	void SetFrame(int frame) noexcept;

	float GetSpeed() const noexcept;
	void SetSpeed(float speed) noexcept;
protected:
	void SendIndex() const noexcept;
	int frame;
	float speed;
	float index;
};
