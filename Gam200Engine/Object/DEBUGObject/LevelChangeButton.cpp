/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   LevelChangeButton.cpp
Author
	- Sinil.Kang rtd99062@gmail.com

Creation Date: 12.11.2019

	Source file for object that make jump level
******************************************************************************/

#include <Object/DEBUGObject/LevelChangeButton.hpp>
#include <States/StateManager.hpp>
#include <utility>

LevelChangeButton::LevelChangeButton()
{
	SetObjectName("Level Change Button");
}

LevelChangeButton::~LevelChangeButton()
{
}

std::vector<std::string> LevelChangeButton::GetStateNames() const noexcept
{
	return StateManager::GetStateManager()->GetStateNames();
}

void LevelChangeButton::ChangeLevel(const std::string& nextLevelName) noexcept
{
	StateManager::GetStateManager()->SetNextLevel(nextLevelName);
}
