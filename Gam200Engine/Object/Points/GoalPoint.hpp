/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   GoalPoint.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 03.20.2020

	Header file for goal object
		When player is on this (Goal Point), send message to SceneStateManager.
******************************************************************************/
#include <Object/Object.hpp>
#include <Graphics/Color4f.hpp>

class Player;

class GoalPoint : public Object
{
public:
	GoalPoint(const Transform& transform, Player* ptrToPlayer, Graphics::Color4f highlightedColor = Graphics::Color4f{ 1.f, 0.f, 0.f });

private:
	void LoadGoalPoint1Layout() noexcept;
	void LoadGoalPoint2Layout() noexcept;

private:
	Player* player;
};