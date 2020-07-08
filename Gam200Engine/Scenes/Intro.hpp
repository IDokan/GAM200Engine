/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Intro.hpp
Author
	- sinil.gang rtd99062@gmail.com
Creation Date: 07.06.2020

	Header file for intro
******************************************************************************/
#pragma once

#include <Scenes/Scene.hpp>

class Sprite;

class Intro : public Scene
{
public:
	Intro();
	virtual ~Intro();

	void Update(float dt);

protected:
	void GameRestart() override;
	void Load() override;
	void Unload() override;

private:
	Object* digipenLogo;
	Object* fmodLogo;
	Sprite* digipenSprite;
	Sprite* fmodSprite;

	float time;
};