/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Pause.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 05.11.2020

	Source file for Pause State
		Pause until other message is received,
******************************************************************************/
#include <States/PlayerStates/Pause.hpp>

Pause* Pause::Get()
{
	static Pause* state = new Pause();
	return state;
}

void Pause::Enter(Player* obj)
{
	printf("Player enter Pause State\n");
	pausedPosition = obj->GetTranslation();
}

void Pause::Execute(Player* obj, float /*dt*/)
{
	obj->GetComponentByTemplate<Physics>()->SetVelocity(vector2{ 0.f });
	obj->GetComponentByTemplate<Physics>()->SetVectorTranslation(pausedPosition);
}

void Pause::Exit(Player* /*obj*/)
{
	printf("Player exit Pause State\n");
}

Pause::Pause()
{
}
