/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Move.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.13.2020

	Header file for Move State
		This state execute move
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Players/Player.h>

class Move : public State<Player>
{
public:
	static Move* Get();
	~Move() = default;
	
	void Enter(Player* obj) override;
	void Execute(Player* obj, float dt) override;
	void Exit(Player* obj) override;
    void SetPlayerMoveSpeed(float amount);
    void SetIsCheatCodeActivated(bool flag);
    bool GetIsCheatCodeActivated() const;

private:
	Move() = default;
    vector2 playerUpMoveSpeed = vector2{ 0.f, 200.f };
    vector2 playerLeftUpMoveSpeed = vector2{ -200.f, 200.f };
    vector2 playerRightUpMoveSpeed = vector2{ 200.f, 200.f };
    vector2 playerDownMoveSpeed = vector2{ 0.f, -200.f };
    vector2 playerLeftDownMoveSpeed = vector2{ -200.f, -200.f };
    vector2 playerRightDownMoveSpeed = vector2{ 200.f, -200.f };
    vector2 playerLeftMoveSpeed = vector2{ -200.f, 0.f };
    vector2 playerRightMoveSpeed = vector2{ 200.f, 0.f };

    bool isCheatCodeActivated = false;
};