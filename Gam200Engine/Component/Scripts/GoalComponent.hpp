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
#include <Object/Players/Player.h>

struct vector2;
enum class MessageTypes;

class GoalComponent : public Component
{
public:
	GoalComponent(Object* obj, Player* targetPlayer1, Player* targetPlayer2);
	virtual ~GoalComponent();
	
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Clear() override;

	std::string GetTargetStage();

private:
	void CheckPlayerIsInGoal(Player::Identifier id);
	bool IsAInsideB(const vector2& minOfA, const vector2& maxOfA, const vector2& minOfB, const vector2& maxOfB) const noexcept;
	void DispatchMessage(Player::Identifier id, MessageTypes msg);
private:
	std::string targetStage;
	Player* targetPlayer1;
	Player* targetPlayer2;
	bool isPlayerOnGoal1;
	bool isPlayerOnGoal2;
	bool doorSoundTriggerd;
};
