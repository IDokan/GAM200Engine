/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.hpp
Author
	- Sinil.Kang rtd99062@gmail.com

Creation Date: 12.10.2019

	Header file for level that player learned how to move player
******************************************************************************/
#pragma once
#include <States/State.hpp>

class Object;
class String;


class BasicMovementLevel : public State
{
public:
	BasicMovementLevel();
	virtual ~BasicMovementLevel();

	void Update(float dt) override;

protected:
    void GameRestart() override;
	void Load() override;
	void Unload() override;

    void Input();
    void Collision();
    void InitObject();

private:
    Object* background;
    Object* startPoint{};
    Object* goalPoint{};
    Object* player1{};
    Object* player2{};
    String* string{};
};