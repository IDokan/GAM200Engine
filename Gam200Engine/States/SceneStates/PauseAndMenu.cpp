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

// Menu Items
#include <Object/Menu/BaseMenu.hpp>
#include <Object/Menu/DestructiveConfirmation.hpp>
#include <Object/Menu/OptionMenu.hpp>
#include <Object/Menu/MainMenu.hpp>
#include <Object/Menu/LevelComplete.hpp>

#include <Component/StateMachine.hpp>
#include <States/SceneStates/GamsIsRunning.hpp>

PauseAndMenu* PauseAndMenu::Get()
{
    static PauseAndMenu* state = new PauseAndMenu();
    return state;
}

void PauseAndMenu::Enter(SceneStateManager* manager)
{
	if (!SceneManager::GetSceneManager()->GetCurrentScene()->IsMenu())
	{
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::Pause);
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::Pause);
	}

    SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolumeOnMenu();

	if (defaultItem == nullptr)
	{
		menuStack.push(baseMenu);
		baseMenu->StartLerpIn();
	}
	else
	{
		menuStack.push(defaultItem);
		defaultItem->StartLerpIn();
	}
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
    else if (
        returnValue->isLerpOut == true &&
        returnValue->lerpTimer >= 1.f
        )
    {
        menuStack.pop();
    }
}

void PauseAndMenu::Exit(SceneStateManager* /*manager*/)
{
	ClearStack();

    MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::Resume);
    MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::Resume);
}

PauseAndMenu::PauseAndMenu()
	: defaultItem(nullptr), baseMenu(nullptr), confirmMenu(nullptr), optionMenu(nullptr), mainMenu(nullptr), clearMenu(nullptr)
{
}

void PauseAndMenu::ClearStack()
{
	while (!menuStack.empty())
	{
		menuStack.top()->SetScale(0.f);
		menuStack.pop();
	}
}

void PauseAndMenu::PrepareAssets() noexcept
{
	Layer* HUDLayer = ObjectManager::GetObjectManager()->FindLayer(HUD);

	if (baseMenu == nullptr)
	{
		baseMenu = new BaseMenu();
		baseMenu->SetObjectName("Base Menu");
		baseMenu->SetScale(0.f);
		baseMenu->SetDepth(0.f);
		HUDLayer->AddObjectDynamically(baseMenu);
		baseMenu->AddChildObjectsDynamically();
	}

	if (confirmMenu == nullptr)
	{
		confirmMenu = new DestructiveConfirmation();
		confirmMenu->SetObjectName("ConfirmMenu");
		confirmMenu->SetScale(0.f);
		confirmMenu->SetDepth(0.f);
		HUDLayer->AddObjectDynamically(confirmMenu);
		confirmMenu->AddChildObjectsDynamically();
	}

	if (optionMenu == nullptr)
	{
		optionMenu = new OptionMenu();
		optionMenu->SetObjectName("OptionMenu");
		optionMenu->SetScale(0.f);
		optionMenu->SetDepth(0.f);
		HUDLayer->AddObjectDynamically(optionMenu);
		optionMenu->AddChildObjectsDynamically();
	}

	if (mainMenu == nullptr)
	{
		mainMenu = new MainMenu();
		mainMenu->SetObjectName("MainMenu Holder");
		mainMenu->SetTranslation(vector2{0.7f, 0.f});
		mainMenu->SetScale(0.f);
		mainMenu->SetDepth(0.f);
		HUDLayer->AddObjectDynamically(mainMenu);
		mainMenu->AddChildObjectsDynamically();
	}

	if (clearMenu == nullptr)
	{
		clearMenu = new LevelComplete();
		clearMenu->SetObjectName("Level Complete Holder");
		clearMenu->SetScale(0.f);
		clearMenu->SetDepth(0.f);
		HUDLayer->AddObjectDynamically(clearMenu);
		clearMenu->AddChildObjectsDynamically();
	}
}

void PauseAndMenu::CleanAssets() noexcept
{
	ClearStack();

	if (baseMenu != nullptr)
	{
		baseMenu->CleanChildObjects();
		baseMenu->SetDead(true);
		baseMenu = nullptr;
	}

	if (confirmMenu != nullptr)
	{
		confirmMenu->CleanChildObjects();
		confirmMenu->SetDead(true);
		confirmMenu = nullptr;
	}

	if (optionMenu != nullptr)
	{
		optionMenu->CleanChildObjects();
		optionMenu->SetDead(true);
		optionMenu = nullptr;
	}

	if (mainMenu != nullptr)
	{
		mainMenu->CleanChildObjects();
		mainMenu->SetDead(true);
		mainMenu = nullptr;
	}

	if (clearMenu != nullptr)
	{
		clearMenu->CleanChildObjects();
		clearMenu->SetDead(true);
		clearMenu = nullptr;
	}

	defaultItem = nullptr;
}
