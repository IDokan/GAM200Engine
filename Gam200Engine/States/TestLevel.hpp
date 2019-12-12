/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TestLevel.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
    - Hyerin Jung junghl0621@gmail.com
Creation Date: 08.15.2019

	Header file for First Level to Test Sprite Component
******************************************************************************/
#pragma once
#include <States/State.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Object/InteractiveObject/CrushableObject.hpp>
#include <Object/InteractiveObject/ObstacleObject.hpp>

class TestLevel final : public State
{
public:
	TestLevel() = default;

	virtual ~TestLevel()
	{
	};

	virtual void Update(float dt) override;

    void Input();
    void Collision();
protected:
    virtual void GameRestart() override;
	virtual void Load() override;
	virtual void Unload() override;
private:
    void PlayerMove(vector2 player1Position, vector2 player2Position) const;
	void PlayerScaling();
	void CheckOutofPlace();
	void UpdateCollisionBox(Object* obj1, Object* obj2);
private:

    Object* gameClearPopUp{};
    Object* startPoint{};
    Object* goalPoint{};
	Object* object1{};
	Object* object2{};
	Object* background{};
	Object* object4{};
	Object* numbers{};
	Object* testObject{}; // test for jaemin
	String* string{};
    CrushableObject* crushable_Object;



//map objects
    Object* first_Objects_1{};
    Object* first_Objects_2{};
    Object* first_Objects_3{};

    Object* third_Objects_1{};
    Object* third_Objects_2{};
    Object* third_Objects_3{};
    Object* third_Objects_4{};
    Object* third_Objects_5{};

    Object* map{};

//Obstacle
    ObstacleObject * sharpKnife{};

    //movement image
    Object* movement_p1{};
    Object* movement_p2{};

	bool flag = false;
    bool isCheck_Clear = false;
};
