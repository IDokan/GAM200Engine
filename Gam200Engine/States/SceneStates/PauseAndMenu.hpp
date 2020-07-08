/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   PauseAndMenu.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 05.11.2020

	Header file for PauseAndMenu State
		When player pressed escape button, scane state manager change current state into this.
		Player is going to stop and menu is going to pop up
******************************************************************************/
#pragma once
#include <stack>

#include <States/State.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>

class Object;
class MenuObject;
class DestructiveConfirmation;

class PauseAndMenu : public State<SceneStateManager>
{
public:
	static PauseAndMenu* Get();

	void Enter(SceneStateManager* manager) override;
	void Execute(SceneStateManager* manager, float dt) override;
	void Exit(SceneStateManager* manager) override;


	void PrepareAssets() noexcept;
	void CleanAssets() noexcept;

	MenuObject* defaultItem;


	MenuObject* baseMenu;
	MenuObject* confirmMenu;
	MenuObject* optionMenu;
	MenuObject* mainMenu;
private:
	PauseAndMenu();
	void ClearStack();

	std::stack<MenuObject*> menuStack;
};

