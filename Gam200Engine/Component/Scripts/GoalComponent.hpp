/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   GoalComponent.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.13.2019

	Header file for goal component that will be attached at goal object
******************************************************************************/
#pragma once
#include <Component/Component.hpp>
#include <Graphics/Color4f.hpp>

class Player;
struct vector2;
enum class MessageTypes;

class GoalComponent : public Component
{
public:
	GoalComponent(Object* obj, Player* targetPlayer, Graphics::Color4f color);
	virtual ~GoalComponent();
	
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Clear() override;

private:
	bool IsAInsideB(const vector2& minOfA, const vector2& maxOfA, const vector2& minOfB, const vector2& maxOfB) const noexcept;
	void DispatchMessage(MessageTypes msg);
private:
	Player* targetPlayer;
	bool isPlayerOnGoal;
	Graphics::Color4f highlightedColor;
};
