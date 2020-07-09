/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Ending.hpp
Author
	- doyoung413@gmail.com
Creation Date: 07.09.2020

	Header file for ending level
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>

class Object;
class Player;
class String;

class Ending : public Scene
{
public:
	Ending();
	virtual ~Ending();

	void Update(float dt) override;

protected:
	void GameRestart() override;
	void Load() override;
	void Unload() override;

	void Input();
	void InitObject();

private:
	Object* background;

	Object* cutScene;
	int cutCount = 0;
	bool isCutChanged = false;
};