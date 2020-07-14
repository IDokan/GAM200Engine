/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Credit.hpp
Author
	- jjwon6218@gmail.com
Creation Date: 05.22.2020

	Header file for credit level
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>

class Object;
class Player;
class String;

class Credit : public Scene
{
public:
	Credit();
	virtual ~Credit();

	void Update(float dt) override;

protected:
	void GameRestart() override;
	void Load() override;
	void Unload() override;

	void Input();
	void Collision();
	void InitObject();

private:

	float totalDT;

	Object* gamelogo{};
	Object* teamlogo{};
	Object* list1{};
	Object* list2{};
	Object* list3{};
	Object* list4{};
	Object* digipenLogo{};
};