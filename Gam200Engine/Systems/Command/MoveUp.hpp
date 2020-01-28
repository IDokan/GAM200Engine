/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MoveUp.hpp
Author
		sinil.gang
			rtd99062@gmail.com
Creation Date: 23th/Jan/2020

	Header file for Move Up command derived by Command class
******************************************************************************/
#pragma once
#include <Systems/Command/Command.hpp>
#include <Systems/Input.hpp>
#include <Component/Physics.hpp>
#include <Object/Players/Player.h>

class MoveUp : public Command
{
public:
	MoveUp(int KEY, Player* player);
	~MoveUp() = default;

	virtual void execute();

private:
	Player* player;
	
};

inline MoveUp::MoveUp(int KEY, Player* player)
	:Command(KEY), player(player)
{
}

inline void MoveUp::execute()
{
	if (input.IsKeyPressed(GLFW_KEY))
	{
		player->GetComponentByTemplate<Physics>()->SetVelocity(
			player->GetComponentByTemplate<Physics>()->GetVelocity() + vector2{0.f, 3.f});
	}
}
