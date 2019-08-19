/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TestLevel.hpp
Author
	- Sinil.Kang rtd99062@gmail.com

Creation Date: 08.15.2019

	Header file for First Level to Test Sprite Component
******************************************************************************/
#pragma once
#include <States/State.hpp>
#include <Object/Object.hpp>

class TestLevel : public State
{
public:
	TestLevel() = default;
	~TestLevel() = default;

	virtual void Load() override;
	virtual void Update(float dt) override;
	virtual void Unload() override;

	void Draw() const noexcept override;

private:
	Object obj;
	Object obj2;
	bool flag = false;
};
