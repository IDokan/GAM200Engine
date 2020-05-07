/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Option.hpp
Author
	- Sinil.Kang rtd99062@gmail.com

Creation Date: 04.02.2020

	Header file for level that change Game's settings
******************************************************************************/


#pragma once
#include <Scenes/Scene.hpp>

class SelectableObject;
class Object;


class OptionLevel : public Scene
{
public:
	OptionLevel();
	virtual ~OptionLevel();

	void Update(float dt) override;

protected:
	void GameRestart() override;
	void Load() override;
	void Unload() override;

	void SetArrowsYPosition(float y) noexcept;

private:
	void InitObjects();
	SelectableObject* volume;
	SelectableObject* fullScreen;
	Object* leftArrow;
	Object* rightArrow;
};