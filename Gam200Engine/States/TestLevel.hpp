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
#include <Graphics/CameraManager.hpp>

class TestLevel final : public State
{
public:
	TestLevel() = default;

	virtual ~TestLevel()
	{
	};

	virtual void Load() override;
	virtual void Update(float dt) override;
	virtual void Unload() override;

	void Draw() const noexcept override;

    void Input();
    void Collision();
private:
	Graphics::CameraManager cameraManager;

	Object* object1;
	Object* object2;
	Object* background;
	Object* object4;
	Object* numbers;
	Object* testObject; // test for jaemin
	Object* string;
	bool flag = false;

	Object* cameraDEBUGdrawing;
};
