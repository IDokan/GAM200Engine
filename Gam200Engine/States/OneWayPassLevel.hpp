/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   OneWayPassLevel.hpp
Author
    - Sinil.Kang rtd99062@gmail.com
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 12.10.2019

    Header file for level that string make player move easily
******************************************************************************/
#pragma once
#include <States/State.hpp>

class Player1;
class Player2;
class Object;
class String;

class OneWayPassLevel : public State
{
public:
    OneWayPassLevel();
    virtual ~OneWayPassLevel();

	void Update(float dt) override;

protected:
	void Load() override;
	void Unload() override;
	
    void Input();
    void Collision();
    void InitObject();
private:
    Object* background;
    Object* startPoint{};
    Object* goalPoint{};

    Object* first_Objects_1{};
    Object* first_Objects_2{};
    Object* first_Objects_3{};

    Player1* player1{};
    Player2* player2{};
    String* string{};
};