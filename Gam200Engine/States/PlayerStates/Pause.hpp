/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Pause.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 05.11.2020

	Header file for Pause State
		Pause until other message is received,
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Players/Player.h>

class Pause : public State<Player>
{
public:
	static Pause* Get();
	~Pause() = default;
	
	void Enter(Player* obj) override;
	void Execute(Player* obj, float dt) override;
	void Exit(Player* obj) override;

private:
	Pause();
};