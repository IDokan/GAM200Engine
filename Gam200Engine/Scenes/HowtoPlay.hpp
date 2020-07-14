/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   HowtoPlay.hpp
Author
	- jjwon6218@gmail.com
Creation Date: 05.29.2020

	Header file for how to play level
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>

class Object;
class Player;
class String;

class HowToPlay : public Scene
{
public:
	HowToPlay();
	virtual ~HowToPlay();

	void Update(float dt) override;

protected:
	void GameRestart() override;
	void Load() override;
	void Unload() override;

	void Input();
	void Collision();
	void InitObject();

private:

	Object* movementIndicator1{};
	Object* movementIndicator2{};
	Object* movementExplanation{};
	Object* rightArrow{};

	Object* sizeIndicator{};
	Object* sizeExplanation{};
	Object* arrows1{};
	
	Object* movableBox{};
    Object* movableBox1{};
	Object* movableBoxExplanation{};
	Object* arrows2{};

	Object* checkpoint{};
	Object* checkpoint1{};
	Object* checkpointExplanation{};
	Object* leftArrow{};

	Object* press;
	Object* press1;
	Object* press2;
	Object* press3;
};