/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Patrol.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.31.2020

	Header file for Idle State
		When AI is in this state, AI patrol determined two position.
		AI
******************************************************************************/
#include <States/State.hpp>

class Mouse;
struct vector2;

class Patrol : public State<Mouse>
{
public:
	void Enter(Mouse* mouse);
	void Execute(Mouse* mouse);
	void Exit(Mouse* mouse);

	static Patrol* Get();

private:
	void MoveMouse(Mouse* mouse, vector2 position);
	bool canMouseSeePlayer(Mouse* mouse);
	void AttackPlayers(Mouse* mouse);
	Patrol() = default;
};