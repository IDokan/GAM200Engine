/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Prolog.hpp
Author
	- doyoung413@gmail.com
Creation Date: 07.09.2020

	Header file for prolog level
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>

class Object;
class Player;
class String;

class Prolog : public Scene
{
public:
	Prolog();
	virtual ~Prolog();

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
	Object* pressS;
	int cutCount;
	bool isCutChanged = false;

	float delay;
	float maxDelay;
};