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

class Object;

class TestLevel : public State
{
public:
	TestLevel() = default;
	~TestLevel() = default;

	virtual void Load() override;
	virtual void Update(float dt) override;
	virtual void Unload() override;

private:
	Object obj;
};
