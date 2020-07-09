/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   EnteringRefrigerator.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 07.08.2020

	Header file for the state when Player is going to enter refrigerator.
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Players/Player.h>
#include <Graphics/Color4f.hpp>

class EnteringRefrigerator : public State<Player>
{
public:
	static constexpr float EndTime = 1.f;
	vector2 TargetPosition;
public:
	static EnteringRefrigerator* Get();
	
	void Enter(Player* obj) override;
	void Execute(Player* obj, float dt) override;
	void Exit(Player* obj) override;

private:
	EnteringRefrigerator();

	void SetColor(float scaler, Player* player);
	void StoreVariables(Player* player);

	// Scaler should be between 0 and 1
	// 0 -> player Position
	// 1 -> targetPosition
	vector2 LerpPosition(float scaler, Player* player);
private:
	float timer;
	Graphics::Color4f p1Color;
	Graphics::Color4f p2Color;
	vector2 p1Position;
	vector2 p2Position;
};