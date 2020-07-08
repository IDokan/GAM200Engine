/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MenuObject.hpp
Author
		rtd99062@gmail.com
Creation Date: 05.11.2020

	Declaration for Base Menu
		- Resume
		- Option
		- Quit
******************************************************************************/
#include <Object/Menu/BaseMenu.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/DepthStandard.hpp>

#include <Object/ObjectManager.hpp>
#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>

#include <Object/Menu/DestructiveConfirmation.hpp>

SoundManager smInBaseMenu;
BaseMenu::BaseMenu()
	: MenuObject(), menuBackground(nullptr), resumeButton(nullptr), optionButton(nullptr), exitButton(nullptr), selectionHighlight(nullptr), currentSelection(Resume), isTransparency(true), playerPressEnter(false)
{
	menuBackground = new Object();
	menuBackground->GetTransform().SetParent(&GetTransform());
	Sprite* menuBackgroundSprite = new Sprite(menuBackground);
	menuBackground->AddComponent(menuBackgroundSprite);
	menuBackgroundSprite->SetImage("../assets/textures/UI/MenuBackground.png");
	menuBackground->SetScale(vector2{ 1.f, 1.8f });
	menuBackground->SetObjectName("MenuBackground");
	menuBackground->SetDepth(Depth_Standard::HUDBackground);
	menuBackground->SetObjectType(ObjectType::Menu);

	resumeTransform.SetTranslation(vector2{ 0.f, 0.2f });
	resumeTransform.SetScale(buttonInitSize);
	optionTransform.SetTranslation(vector2{ 0.f, -0.1f });
	optionTransform.SetScale(buttonInitSize);
	exitTransform.SetTranslation(vector2{ 0.f, -0.4f });
	exitTransform.SetScale(buttonInitSize);
	quitTransform.SetTranslation(vector2{ 0.f, -0.7f });
	quitTransform.SetScale(buttonInitSize);
	resumeTransform.SetParent(&GetTransform());
	optionTransform.SetParent(&GetTransform());
	exitTransform.SetParent(&GetTransform());
	quitTransform.SetParent(&GetTransform());


	resumeButton = new Object();
	resumeButton->GetTransform().SetParent(&GetTransform());
	Sprite* resumeButtonSprite = new Sprite(resumeButton);
	resumeButton->AddComponent(resumeButtonSprite);
	resumeButtonSprite->SetImage("../assets/textures/UI/Resume.png");
	resumeButton->SetObjectName("ResumeButton");
	resumeButton->SetDepth(Depth_Standard::HUDImage);
	resumeButton->SetObjectType(ObjectType::Menu);

	optionButton = new Object();
	optionButton->GetTransform().SetParent(&GetTransform());
	Sprite* optionButtonSprite = new Sprite(optionButton);
	optionButton->AddComponent(optionButtonSprite);
	optionButtonSprite->SetImage("../assets/textures/UI/Option.png");
	optionButton->SetObjectName("OptionButton");
	optionButton->SetDepth(Depth_Standard::HUDImage);
	optionButton->SetObjectType(ObjectType::Menu);

	exitButton = new Object();
	exitButton->GetTransform().SetParent(&GetTransform());
	Sprite* exitButtonSprite = new Sprite(exitButton);
	exitButton->AddComponent(exitButtonSprite);
	exitButtonSprite->SetImage("../assets/textures/UI/Exit.png");
	exitButton->SetObjectName("ExitButton");
	exitButton->SetDepth(Depth_Standard::HUDImage);
	exitButton->SetObjectType(ObjectType::Menu);

	quitButton = new Object();
	quitButton->GetTransform().SetParent(&GetTransform());
	Sprite* quitButtonSprite = new Sprite(quitButton);
	quitButton->AddComponent(quitButtonSprite);
	quitButtonSprite->SetImage("../assets/textures/UI/Quit.png");
	quitButton->SetObjectName("ExitButton");
	quitButton->SetDepth(Depth_Standard::HUDImage);
	quitButton->SetObjectType(ObjectType::Menu);



	selectionHighlight = new Object();
	selectionHighlight->GetTransform().SetParent(&GetTransform());
	selectionHighlight->SetObjectName("Selection Highlight");
	selectionHighlight->SetDepth(0.f);
	selectionHighlight->SetObjectType(ObjectType::Menu);

	UpdateSelectionHighlightTransformation();
	smInBaseMenu = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
}

BaseMenu::~BaseMenu()
{
}

MenuObject* BaseMenu::MenuUpdate(float dt)
{
	UpdateSelection();
	UpdateSelectionHighlightTransparency(dt);

	// When esc key is pressed, return to game
	if (input.IsKeyTriggered(GLFW_KEY_ESCAPE))
	{
		smInBaseMenu = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
		smInBaseMenu.SetVolumeOnGameRunning();

		smInBaseMenu.Play_Sound(UNDO_SOUND);
		return nullptr;
	}

	if (input.IsKeyPressed(GLFW_KEY_ENTER))
	{
		GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(0.3f));
		playerPressEnter = true;
	}
	else if (playerPressEnter)
	{
		playerPressEnter = false;
		GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(1.f));
		smInBaseMenu.Play_Sound(BUTTON_TRIGGERED_SOUND);
		switch (currentSelection)
		{
		case BaseMenu::Resume:
			return nullptr;
			break;
		case BaseMenu::Option:
			return PauseAndMenu::Get()->optionMenu;
			break;
		case BaseMenu::Exit:
			dynamic_cast<DestructiveConfirmation*>(PauseAndMenu::Get()->confirmMenu)->SetDoThis([&]()
				{
					smInBaseMenu = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
					smInBaseMenu.Stop_Sound(SOUNDS::BACKGROUND_SOUND);
					SceneManager::GetSceneManager()->SetNextScene("MenuScene");
				});
			return PauseAndMenu::Get()->confirmMenu;
		case BaseMenu::Quit:
			dynamic_cast<DestructiveConfirmation*>(PauseAndMenu::Get()->confirmMenu)->SetDoThis([&]()
				{
					smInBaseMenu = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
					smInBaseMenu.Stop_Sound(SOUNDS::BACKGROUND_SOUND);
					input.SetIsRunning(false);
				});
			return PauseAndMenu::Get()->confirmMenu;
			break;
		default:
			break;
		}
	}
	return this;
}

void BaseMenu::AddChildObjectsDynamically()
{
	Layer* HUDLayer = ObjectManager::GetObjectManager()->FindLayer(HUD);
	HUDLayer->AddObjectDynamically(menuBackground);
	HUDLayer->AddObjectDynamically(resumeButton);
	HUDLayer->AddObjectDynamically(optionButton);
	HUDLayer->AddObjectDynamically(exitButton);
	HUDLayer->AddObjectDynamically(quitButton);
	HUDLayer->AddObjectDynamically(selectionHighlight);
}

void BaseMenu::CleanChildObjects()
{
	menuBackground->SetDead(true);
	resumeButton->SetDead(true);
	optionButton->SetDead(true);
	exitButton->SetDead(true);
	quitButton->SetDead(true);
	selectionHighlight->SetDead(true);
}

void BaseMenu::LerpIn(float timer)
{
	SetScale(EaseOutBounce(timer));
}

void BaseMenu::LerpOut(float timer)
{
	float scaler = 1.f - EaseOutBounce(timer);

	if (scaler < 0.f)
	{
		scaler = 0.f;
	}

	SetScale(scaler);
}

void BaseMenu::SetCurrentSelection(MenuEnum newValue)
{
	if (newValue > Quit)
	{
		currentSelection = Resume;
	}
	else if (newValue < Resume)
	{
		currentSelection = Quit;
	}
	else
	{
		currentSelection = newValue;
	}
}

void BaseMenu::UpdateSelection() noexcept
{
	if (input.IsKeyTriggered(GLFW_KEY_DOWN))
	{
		smInBaseMenu.Play_Sound(CURSOR_MOVEMENT_SOUND);
		SetCurrentSelection(static_cast<MenuEnum>(currentSelection + 1));
	}
	else if (input.IsKeyTriggered(GLFW_KEY_UP))
	{
		smInBaseMenu.Play_Sound(CURSOR_MOVEMENT_SOUND);
		SetCurrentSelection(static_cast<MenuEnum>(currentSelection - 1));
	}
	else
	{
		return;
	}

	UpdateSelectionHighlightTransformation();
}

Object* BaseMenu::GetSelectedObject()
{
	switch (currentSelection)
	{
	case BaseMenu::MenuEnum::Resume:
		return resumeButton;
		break;
	case BaseMenu::MenuEnum::Option:
		return optionButton;
		break;
	case BaseMenu::MenuEnum::Exit:
		return exitButton;
		break;
	case BaseMenu::MenuEnum::Quit:
		return quitButton;
		break;
	default:
		break;
	}
	return nullptr;
}

void BaseMenu::UpdateSelectionHighlightTransformation()
{
	resumeButton->GetTransform().SetParent(&resumeTransform);
	optionButton->GetTransform().SetParent(&optionTransform);
	exitButton->GetTransform().SetParent(&exitTransform);
	quitButton->GetTransform().SetParent(&quitTransform);

	Object* selectedObject = GetSelectedObject();
	selectionHighlight->GetTransform().SetParent(selectedObject->GetTransform().GetParent());
	selectedObject->GetTransform().SetParent(&selectionHighlight->GetTransform());
}

void BaseMenu::UpdateSelectionHighlightTransparency(float dt)
{
	// When a flag is on, decrease as mush as given dt
	if (isTransparency)
	{
		vector2 highlightSize = selectionHighlight->GetScale();
		selectionHighlight->SetScale(highlightSize.x + (dt / 2.f));

		// if the alpha value is smaller than minimum capacity
		if (highlightSize.x > 1.2f)
		{
			selectionHighlight->SetScale(1.2f);
			isTransparency = !isTransparency;
		}
	}
	// and increase when the flag is off 
	else
	{
		vector2 highlightSize = selectionHighlight->GetScale();
		selectionHighlight->SetScale(highlightSize.x - (dt / 2.f));

		// if the alpha value is bigger than maximum capacity
		if (highlightSize.x < 1.f)
		{
			selectionHighlight->SetScale(1.f);
			isTransparency = !isTransparency;
		}
	}
}

float BaseMenu::EaseInBounce(float timer)
{
	return 1.f - EaseOutBounce(1.f - timer);
}

float BaseMenu::EaseOutBounce(float timer)
{
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (timer < (1.f / d1))
	{
		return n1 * timer * timer;
	}
	else if (timer < (2.f / d1))
	{
		return n1 * (timer -= 1.5f / d1) * timer + 0.75f;
	}
	else if (timer < (2.5f / d1))
	{
		return n1 * (timer -= 2.25f / d1) * timer + 0.9375f;
	}
	else
	{
		return n1 * (timer -= 2.625f / d1) * timer + 0.984375f;
	}
}
