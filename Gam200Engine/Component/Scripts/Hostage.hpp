/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Hostage.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 05.04.2020

	Header file for hostage.
	When it collides let scene state know hostage is rescued.
******************************************************************************/
#pragma once
#include <Component/Component.hpp>

class Player;
enum class MessageTypes;

class Hostage : public Component
{
public:
	Hostage(Object* obj, Player* player1, Player* player2);
	virtual ~Hostage();
	
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Clear() override;

private:
	void DispatchMessage(MessageTypes msg);
private:
	Player* player1;
	Player* player2;
	bool isRescued;
};
