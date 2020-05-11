/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   UpdateAnimation.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.08.2020

	Header file for UpdateAnimation State
		This state is global state which update animation with object's velocity.
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Players/Player.h>

class UpdateAnimation : public State<Player>
{
public:
	static UpdateAnimation* Get();
	
	void Enter(Player* obj) override;
	void Execute(Player* obj, float dt) override;
	void Exit(Player* obj) override;

private:
	UpdateAnimation();
};