/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   InRefrigerator.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 07.08.2020

	Header file for the state when Player is in refrigerator.
		Wait until get any input and play some animation and change to Idle state
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Players/Player.h>
#include <Graphics/Color4f.hpp>

class String;

class InRefrigerator : public State<Player>
{
public:
	String* ptrString;
	static constexpr float EndTime = 2.f;
public:
	static InRefrigerator* Get();
	
	void Enter(Player* obj) override;
	void Execute(Player* obj, float dt) override;
	void Exit(Player* obj) override;

private:
	InRefrigerator();

	void SetColor(float scaler, Player* player);
	void StoreColor(Player* player);

	void SetStringColor(float scaler);
private:
	bool wasInputDetected;
	float timer;
	Graphics::Color4f p1Color;
	Graphics::Color4f p2Color;
};