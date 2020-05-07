/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MouseIdle.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.31.2020

	Header file for Idle State
		This state wait for input to move.
		AI
******************************************************************************/
#include <States/State.hpp>

class Mouse;

class MouseIdle : public State<Mouse>
{
public:
	virtual void Enter(Mouse* mouse);
	virtual void Execute(Mouse* mouse);
	virtual void Exit(Mouse* mouse);

	static MouseIdle* Get();

private:
	MouseIdle() = default;
};