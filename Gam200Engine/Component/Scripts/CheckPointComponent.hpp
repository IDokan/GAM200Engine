/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   CheckPointComponent.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 06.29.2020

	Header file for logic of Check Point
******************************************************************************/
#pragma once
#include <Component/Component.hpp>
#include <Graphics/Color4f.hpp>

class Player;

struct vector2;

class CheckPointComponent : public Component
{
public:
	CheckPointComponent(Object* obj, Player* targetPlayer1, Player* targetPlayer2);
	virtual ~CheckPointComponent();
	
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Clear() override;

private:
	bool DoesAIntersectB(const vector2& minOfA, const vector2& maxOfA, const vector2& minOfB, const vector2& maxOfB) const noexcept;
	bool CheckPlayerIsInGoal();
private:
	Player* targetPlayer1;
	Player* targetPlayer2;

	float delayTimer;
};
