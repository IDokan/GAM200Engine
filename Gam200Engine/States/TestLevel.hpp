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
#include <Player.h>
#include <Graphics/CameraManager.hpp>
#include <Object/Strings/String.hpp>

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
	void PlayerScaling();
private:
	Graphics::CameraManager cameraManager;

    Object* gameClearPopUp;
    Object* startPoint;
    Object* goalPoint;
	Object* object1;
	Object* object2;
	Object* background;
	Object* object4;
	Object* numbers;
	Object* testObject; // test for jaemin
	String* string;

//map objects
    Object* first_Objects_1;
    Object* first_Objects_2;
    Object* first_Objects_3;

    Object* third_Objects_1;
    Object* third_Objects_2;
    Object* third_Objects_3;
    Object* third_Objects_4;
    Object* third_Objects_5;

    Object* map;

//Obstacle
    Object* sharpKnife;

    //movement image
    Object* movement_p1;
    Object* movement_p2;

	bool flag = false;
    bool isCheck_Clear = false;
};
