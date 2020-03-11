/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   EditorTestLevel.hpp
Author
	- Jiwon Jung jjwon6218@gmail.com

Creation Date: 02.27.2020

	Header file for level that tests result of the editor
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>

class EditorTestLevel : public Scene
{
public:
	EditorTestLevel();
	virtual ~EditorTestLevel();

	void Update(float dt) override;

protected:
	void GameRestart() override;
	void Load() override;
	void Unload() override;

	void Input();
	void Collision();
	void InitObject();

private:
	Object* background;
	Player* player1{};
	Player* player2{};
	String* string{};
};