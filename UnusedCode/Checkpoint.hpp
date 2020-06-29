/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.cpp
Author
	- Jiwon.Jung       jjwon6218@gmail.com

Creation Date: 03.18.2020

	Header file for component to make checkpoint
******************************************************************************/
#pragma once

#include <Window/Application.hpp>
#include <Component/Component.hpp>
#include <Object/Object.hpp>
#include <Window/Application.hpp>
#include <fstream>
#include <Object/ObjectManager.hpp>
#include <string>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>
#include <Object/DepthStandard.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Vector2.hpp>


class CheckPoint : public Component
{
public:
	CheckPoint(const std::filesystem::path& filePath, Object* obj);
	virtual ~CheckPoint();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Clear();

	void Save();
	void SaveReach();

private:
	Object* checkpoint;
	const std::filesystem::path& fileName;
	bool player1Reached;
	bool player2Reached;
	vector2 checkpointPos;
	vector2 checkpointScale;
};