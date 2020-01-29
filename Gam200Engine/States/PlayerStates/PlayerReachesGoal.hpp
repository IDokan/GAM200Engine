/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   PlayerReachesGoal.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.29.2020

	Header file for PlayerReachesGoal State
		Since this event did not designed,
		We need a team discuss.
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Players/Player.h>

class PlayerReachesGoal : public State<Player>
{
public:
	static PlayerReachesGoal* Get();
	~PlayerReachesGoal() = default;
	
	void Enter(Player* obj) override;
	void Execute(Player* obj) override;
	void Exit(Player* obj) override;

private:
	PlayerReachesGoal() = default;
};