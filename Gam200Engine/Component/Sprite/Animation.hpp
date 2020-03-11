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
#include <Component/Sprite/Sprite.hpp>

class Animation : public Sprite
{
public:
	Animation(Object* obj) noexcept;
	virtual ~Animation() noexcept = default;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual	void Clear() override;

	// Getters
	int GetFrame() const noexcept;
	float GetSpeed() const noexcept;
	int GetState() const noexcept;
	int GetNumOfState() const noexcept;

	// Setters
	void SetFrame(int frame_) noexcept;
	void SetSpeed(float speed_) noexcept;
	void SetState(int state_) noexcept;
	void SetNumOfState(int numOfState_) noexcept;

protected:
	int Clamp(int targetValue, int maxValue, int minValue = 0) const noexcept;
	void SendIndex() const noexcept;
	int frame;
	float speed;
	float index;
	int animationState;
	int numOfState;
};
