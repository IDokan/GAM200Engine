/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Editor.hpp
Author
	- Jiwon Jung jjwon6218@gmail.com

Creation Date: 1.7.2020

	Source file for editor
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>

class Object;
class String;

class Editor : public Scene
{
public:
	Editor();
	virtual ~Editor();

	void Update(float dt) override;

protected:
	void GameRestart() override;
	void Load() override;
	void Unload() override;

	void Input();
	void InitObject();;

private:

	int objectNum = 0;
	float mousePosX, mousePosY;
	std::string objectName;

	Object* background;
	Object* startPoint{};
	Object* goalPoint{};
	Object* player1{};
	Object* player2{};
	String* string{};

	enum class chosenObject
	{
		obstacle, startpoint, goalpoint, player1, player2, adjustment
	};

	chosenObject objectSwitch;
};
