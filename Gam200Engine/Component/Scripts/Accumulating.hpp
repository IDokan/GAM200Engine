/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Accumulating.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.27.2019

	Header file for accumulating.
******************************************************************************/
#pragma once
#include <Component/Component.hpp>

class Accumulating : public Component
{
public:
	Accumulating(Object* obj, float maximum = 100.f, bool turnOn = false) noexcept;
	virtual ~Accumulating() noexcept = default;

	virtual void Init();
	virtual void Update(float dt);
	virtual void Clear();

	// Getters
	bool IsAccumulating() const noexcept;
	float GetAccumulation() const noexcept;
	float GetMaximum() const noexcept;

	// Setters
	void SetIsAccumulating(bool isAccumulating_) noexcept;
	void SetMaximum(float maximum_) noexcept;
private:
	float maximum;
	bool isAccumulating;
	float accumulation;
};