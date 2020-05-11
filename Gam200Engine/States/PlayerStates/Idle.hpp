/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Idle.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.13.2020

	Header file for Idle State
		This state wait for input to move.
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Players/Player.h>

class Idle : public State<Player>
{
public:
	static Idle* Get();
	
	void Enter(Player* obj) override;
	void Execute(Player* obj, float dt) override;
	void Exit(Player* obj) override;

private:
	Idle();
};