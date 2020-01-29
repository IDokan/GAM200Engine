/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Dead.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.29.2020

	Header file for Dead State
		Since dead event did not determined,
		We need a team discuss.
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Players/Player.h>

class Dead : public State<Player>
{
public:
	static Dead* Get();
	~Dead() = default;
	
	void Enter(Player* obj) override;
	void Execute(Player* obj) override;
	void Exit(Player* obj) override;

private:
	Dead();
};