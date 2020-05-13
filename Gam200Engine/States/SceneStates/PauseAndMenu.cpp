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
		
		Enter
			- Send message ��Pause!�� to both players.		-- TBD
			- Display menu.
			- Reduce Background volume

		Execute
			- Update Menus

		Exit
			- Send message "Resume" to both players.		-- TBD

******************************************************************************/
#include <States/SceneStates/PauseAndMenu.hpp>
#include <Systems/MessageSystem/MessageDispatcher.hpp>

#include <Component/Sprite/Sprite.hpp>
#include <Object/DepthStandard.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>

#include <Systems/MessageSystem/MessageDispatcher.hpp>

#include <Object/Menu/BaseMenu.hpp>
#include <Component/StateMachine.hpp>
#include <States/SceneStates/GamsIsRunning.hpp>

PauseAndMenu* PauseAndMenu::Get()
{
	static PauseAndMenu* state = new PauseAndMenu();
	return state;
}

void PauseAndMenu::Enter(SceneStateManager* /*manager*/)
{
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::Pause);
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::Pause);

	PrepareAssets();

	menuStack.push(baseMenu);
	baseMenu->StartLerpIn();
}

void PauseAndMenu::Execute(SceneStateManager* manager, float dt)
{
	// if menuStack is empty change state
	if (menuStack.empty())
	{
		bool isHostageRescued = GameIsRunning::Get()->GetIsHostageRescued();
		manager->GetComponentByTemplate<StateMachine<SceneStateManager>>()->ChangeState(GameIsRunning::Get());
		GameIsRunning::Get()->SetIsHostageRescued(isHostageRescued);
		return;
	}

	// if return ptr is different with menuStack.top
	if (
		MenuObject* returnValue = menuStack.top()->Update(dt);
		returnValue != menuStack.top()
		)
	{
		// if nullptr is returned, pop stack.
		if (returnValue == nullptr)
		{
			MenuObject* top = menuStack.top();
			if (top->isLerpOut == true)
			{
				// When try to pop one more, pop immediately.
				top->lerpTimer = 1.f;
				top->LerpOut(top->lerpTimer);
				menuStack.pop();
			}
			else
			{
				top->StartLerpOut();
			}
		}
		// if ptr is pointing other thing, push that ptr;
		else
		{
			menuStack.push(returnValue);
			returnValue->StartLerpIn();
		}
	}
	// when they are same
	else if(
		returnValue->isLerpOut == true &&
		returnValue->lerpTimer >= 1.f
		)
	{
		menuStack.pop();
	}
}

void PauseAndMenu::Exit(SceneStateManager* /*manager*/)
{
	while (!menuStack.empty())
	{
		menuStack.top()->SetScale(0.f);
		menuStack.pop();
	}

	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::Resume);
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::Resume);
}

PauseAndMenu::PauseAndMenu()
	: baseMenu(nullptr)
{
}

void PauseAndMenu::PrepareAssets() noexcept
{
	if (baseMenu == nullptr)
	{
		baseMenu = new BaseMenu();
		baseMenu->SetObjectName("Base Menu");
		baseMenu->SetScale(0.f);
		baseMenu->SetDepth(0.f);
		Layer* HUDLayer = ObjectManager::GetObjectManager()->FindLayer(HUD);
		HUDLayer->AddObjectDynamically(baseMenu);
		baseMenu->AddChildObjectsDynamically();
	}
}

void PauseAndMenu::CleanAssets() noexcept
{
	if (baseMenu != nullptr)
	{
		baseMenu->CleanChildObjects();
		baseMenu->SetDead(true);
		baseMenu = nullptr;
	}
}