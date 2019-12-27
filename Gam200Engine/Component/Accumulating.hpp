/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Accumulating.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.27.2019

	Header file for accumulating.
******************************************************************************/

#include <Component/Component.hpp>

class Accumulating : public Component
{
public:
	Accumulating(Object* obj, bool turnOn = false);
	virtual ~Accumulating();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Clear();

	// Getters
	bool IsAccumulating() const noexcept;
	float GetAccumulation() const noexcept;

	// Setters
	void SetIsAccumulating(bool isAccumulating_) noexcept;
private:
	bool isAccumulating;
	float accumulation;
};