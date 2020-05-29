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
    constexpr static float maximum_scaling_limit = 125.f;
	constexpr static float minimum_scaling_limit = 75.f;
	constexpr static float scaling_constant = 1.5f;
	constexpr static float collisionBoxOffset = -40.f;

public:
	static UpdateAnimation* Get();
	
	void Enter(Player* obj) override;
	void Execute(Player* obj, float dt) override;
	void Exit(Player* obj) override;


private:
	void Resizing(Player* player);
	void ResizingPlayer1(Player* player);
	void ResizingPlayer2(Player* player);
	void PlayResizingSound();

	UpdateAnimation();

	void UpdateCollisionBox(Player* player);

	bool isSoundPlay;
};