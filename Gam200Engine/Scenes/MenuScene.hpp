/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MenuScene.hpp
Author
	- jiwon.jung jjwon6218@gmail.com
Creation Date: 03.13.2020

	Header file for scene which works as menu
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>

class Object;

class MenuScene : public Scene
{
public:
	MenuScene();
	virtual ~MenuScene();

	void Update(float dt) override;

protected:
	void GameRestart() override;
	void Load() override;
	void Unload() override;

	void Input();
	void Collision();
	void InitObject();

private:

	Object* nextLevelButton{};
	Object* howToPlayButton{};
	Object* settingButton{};
	Object* creditButton{};
	Object* quitButton{};

};
