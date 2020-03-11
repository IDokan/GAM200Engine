/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Dead.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.29.2020

	Source file for Dead State
		Since dead event did not determined,
		We need a team discuss.
******************************************************************************/
#include <States/PlayerStates/Dead.hpp>

Dead* Dead::Get()
{
	static Dead* state = new Dead();
	return state;
}

void Dead::Enter(Player* /*obj*/)
{
	printf("Player enter Dead State\n");
}

void Dead::Execute(Player* /*obj*/)
{
	// TODO: Have a team discuss and implement it!
}

void Dead::Exit(Player* /*obj*/)
{
	printf("Player exit Dead State\n");
}
