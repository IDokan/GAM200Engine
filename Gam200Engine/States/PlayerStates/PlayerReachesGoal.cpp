/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   PlayerReachesGoal.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.29.2020

	Source file for PlayerReachesGoal State
		Since this event did not designed,
		We need a team discuss.
******************************************************************************/
#include <States/PlayerStates/PlayerReachesGoal.hpp>

PlayerReachesGoal* PlayerReachesGoal::Get()
{
	static PlayerReachesGoal* state = new PlayerReachesGoal();
	return state;
}

void PlayerReachesGoal::Enter(Player* obj)
{
	switch (obj->GetID()) {
	case Player::Identifier::Player1:
		printf("Player1 reaches goal!\n");
		break;
	case Player::Identifier::Player2:
		printf("Player2 reaches goal!\n");
		break;
	default:
		printf("Undefined behavior!\n");
	}
}

void PlayerReachesGoal::Execute(Player* /*obj*/, float /*dt*/)
{
	// TODO: Have a team discuss and implement it!
}

void PlayerReachesGoal::Exit(Player* obj)
{
	switch (obj->GetID()) {
	case Player::Identifier::Player1:
		printf("Player1 exit goal!\n");
		break;
	case Player::Identifier::Player2:
		printf("Player2 exit goal!\n");
		break;
	default:
		printf("Undefined behavior!\n");
	}
}
