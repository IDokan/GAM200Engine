/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SceneComplete.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.16.2020

	Source file for SceneComplete State
		if both players reached goal, both player start dancing to celebrate their achievements.
																			--------- -> This is my hope
		Enter
			- Send message ¡°Players reached goal!¡± to both players.
			- Display menu that congratulate players and give a couple of choice.
			- Play "Scene Complete Sound"

		Execute
			- Wait until player do anything with buttons.

		Exit
			- Stop "Scene Complete Sound"

******************************************************************************/
#include <States/SceneStates/SceneComplete.hpp>
#include <Systems/MessageSystem/MessageDispatcher.hpp>

#include <Component/Sprite/Sprite.hpp>
#include <Object/DepthStandard.hpp>
#include <Object/ObjectManager.hpp>
#include <Object/Particles/ParticleEmitter.hpp>
#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>

bool IsMousePositionInBox(vector2 mousePosition, vector2 boxPosition, vector2 boxScale)
{
	vector2 min{ boxPosition - (boxScale / 2.f) };
	vector2 max{ boxPosition + (boxScale / 2.f) };

	return !(
		mousePosition.x < min.x ||
		mousePosition.y < min.y ||
		max.x < mousePosition.x ||
		max.y < mousePosition.y
		);
}

SceneComplete* SceneComplete::Get()
{
	static SceneComplete* state = new SceneComplete();
	return state;
}

void SceneComplete::Enter(SceneStateManager* /*manager*/)
{
	// Send message ¡°Players reached goal!¡± to both players.
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player1, MessageTypes::SceneComplete);
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::SceneStateManager, MessageObjects::Player2, MessageTypes::SceneComplete);

	// Display menu that congratulate players and give a couple of choice.
	PrepareAssets();
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(menuBackground);
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(backToMain);
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(goToNextLevel);
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(confetti);
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObjectDynamically(selectionHighlight);

	// Play "Scene Complete Sound"
	// TODO:
	//SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(SOUNDS::GOAL_SOUND);
	//SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(SOUNDS::GOAL_SOUND, 0.4f);
}



void SceneComplete::LerpIn(float timer)
{
	offset.SetScale(vector2{ EaseOutBounce(timer) });
}


float SceneComplete::EaseOutBounce(float timer)
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


void SceneComplete::Execute(SceneStateManager* manager, float dt)
{
	// Only update lerp when lerpTimer is valid
	if (lerpTimer >= 0.f && lerpTimer < 1.f)
	{
		lerpTimer += dt;
		LerpIn(lerpTimer);
	}

	// Mouse input which is not good because our game is typically controlled by key board.
	vector2 mousePos = input.GetMouseAbsolutePosition();
	if (IsMousePositionInBox(mousePos, vector2{ -200.f, 0.f }, vector2{ 160.f, 180.f }))
	{
		if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			SceneManager::GetSceneManager()->SetNextScene("MenuScene");
		}
		else	if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			printf("Back To Mainmenu button is pressed!\n");
		}
		else
		{
			printf("Back To Mainmenu button is hovered!\n");
		}
	}
	if (IsMousePositionInBox(mousePos, vector2{ 200.f, 0.f }, vector2{ 160.f, 180.f }))
	{
		if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_LEFT))
		{
			SceneManager::GetSceneManager()->SetNextScene(manager->GetNameOfSelectedLevel());
		}
		else	if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			printf("Go to Next Level button is pressed!\n");
		}
		else
		{
			printf("Go to Next Level button is hovered!\n");
		}
	}

	UpdateSelection();
	UpdateSelectionHighlightTransparency(dt);

	if (input.IsKeyTriggered(GLFW_KEY_ENTER) || input.IsKeyTriggered(GLFW_KEY_LEFT_SHIFT) || input.IsKeyTriggered(GLFW_KEY_RIGHT_SHIFT))
	{
		GetSelectedObject()->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(0.3f));
		switch (currentSelection)
		{
		case SceneComplete::Back2Main:
			SceneManager::GetSceneManager()->SetNextScene("MenuScene");
			break;
		case SceneComplete::Go2NextLevel:
			SceneManager::GetSceneManager()->SetNextScene(manager->GetNameOfSelectedLevel());
			break;
		default:
			break;
		}
	}
}

void SceneComplete::Exit(SceneStateManager* /*manager*/)
{
	menuBackground->SetDead(true);
	menuBackground = nullptr;
	backToMain->SetDead(true);
	backToMain = nullptr;
	goToNextLevel->SetDead(true);
	goToNextLevel = nullptr;
	confetti->SetDead(true);
	confetti = nullptr;
	selectionHighlight = nullptr;
	currentSelection = Back2Main;
	isTransparency = true;
	// Stop "Scene Complete Sound"
}

SceneComplete::SceneComplete()
	:menuBackground(nullptr), backToMain(nullptr), goToNextLevel(nullptr), confetti(nullptr), selectionHighlight(nullptr), currentSelection(Back2Main), isTransparency(true), lerpTimer(0.f)
{
	offset.SetScale(vector2{0.f});
}

void SceneComplete::SetCurrentSelection(SelectionEnum newValue)
{
	if (newValue >= OutOfEnum)
	{
		currentSelection = Back2Main;
	}
	else if (newValue < Back2Main)
	{
		currentSelection = Go2NextLevel;
	}
	else
	{
		currentSelection = newValue;
	}
}

void SceneComplete::UpdateSelection() noexcept
{
	if (input.IsKeyTriggered(GLFW_KEY_DOWN))
	{
		SetCurrentSelection(static_cast<SelectionEnum>(currentSelection + 1));
	}
	else if (input.IsKeyTriggered(GLFW_KEY_UP)) 
	{
		SetCurrentSelection(static_cast<SelectionEnum>(currentSelection - 1));
	}
	else
	{
		return;
	}

	UpdateSelectionHighlightTransformation();
}

Object* SceneComplete::GetSelectedObject()
{
	switch (currentSelection)
	{
	case SceneComplete::Back2Main:
		return backToMain;
		break;
	case SceneComplete::Go2NextLevel:
		return goToNextLevel;
		break;
	case SceneComplete::OutOfEnum:
		break;
	default:
		break;
	}
	return nullptr;
}

void SceneComplete::UpdateSelectionHighlightTransformation()
{
	Object* selectedObject = GetSelectedObject();
	selectionHighlight->SetTranslation(selectedObject->GetTranslation());
	selectionHighlight->SetScale(1.2f * selectedObject->GetScale());
}

void SceneComplete::UpdateSelectionHighlightTransparency(float dt)
{
	Sprite* selectionSprite = selectionHighlight->GetComponentByTemplate<Sprite>();
	Graphics::Color4f color = selectionSprite->GetColor();

	// When a flag is on, decrease as mush as given dt
	if (isTransparency)
	{
		color.alpha = color.alpha - dt;

		// if the alpha value is smaller than minimum capacity
		if (color.alpha < 0.f)
		{
			color.alpha = 0.f;
			isTransparency = !isTransparency;
		}
	}
	// and increase when the flag is off 
	else
	{
		color.alpha = color.alpha + dt;

		// if the alpha value is bigger than maximum capacity
		if (color.alpha > 1.f)
		{
			color.alpha = 1.f;
			isTransparency = !isTransparency;
		}
	}
	selectionSprite->SetColor(color);
}

void SceneComplete::PrepareAssets() noexcept
{
	if (menuBackground == nullptr)
	{
		menuBackground = new Object();
		menuBackground->SetObjectName("menuBackground");
		menuBackground->SetScale(vector2{ 1.f, 1.6f });
		Sprite* spriteOfBackground = new Sprite(menuBackground);
		menuBackground->AddComponent(spriteOfBackground);
		spriteOfBackground->SetImage("../assets/textures/UI/LevelClearBackground.png");
		menuBackground->SetDepth(Depth_Standard::HUDBackground);
		menuBackground->GetTransform().SetParent(&offset);
	}

	if (backToMain == nullptr)
	{
		backToMain = new Object();
		backToMain->SetObjectName("Exit Button - SceneComplete");
		backToMain->SetScale(vector2{ 0.5f, 0.25f });
		backToMain->SetTranslation(vector2{ 0.f, -0.4f });
		Sprite* spriteOfBackButton = new Sprite(backToMain);
		backToMain->AddComponent(spriteOfBackButton);
		spriteOfBackButton->SetImage("../assets/textures/UI/Exit.png");
		backToMain->SetDepth(Depth_Standard::HUDImage);
		backToMain->GetTransform().SetParent(&offset);
	}

	if (goToNextLevel == nullptr)
	{
		goToNextLevel = new Object();
		goToNextLevel->SetObjectName("NextLevel - SceneComplete");
		goToNextLevel->SetScale(vector2{ 0.5f, 0.25f });
		goToNextLevel->SetTranslation(vector2{ 0.f, 0.f });
		Sprite* spriteOfNextLevelButton = new Sprite(goToNextLevel);
		goToNextLevel->AddComponent(spriteOfNextLevelButton);
		spriteOfNextLevelButton->SetImage("../assets/textures/UI/NextLevel.png");
		goToNextLevel->SetDepth(Depth_Standard::HUDImage);
		goToNextLevel->GetTransform().SetParent(&offset);
	}


	if (confetti == nullptr)
	{

		confetti = new ParticleEmitter(15.f, 80.f, 100, [&]() ->Particle::ParticleObject
			{
				Graphics::Color4f colors[3];
				colors[0] = Graphics::Color4f(1.f, 0.f, 0.f);
				colors[1] = Graphics::Color4f(0.f, 1.f, 0.f);
				colors[2] = Graphics::Color4f(0.f, 0.f, 1.f);
				float startX = (static_cast<float>(rand() % 250) - 125) / 125.f;
				Particle::ParticleObject p;
				p.transform.SetScale(vector2{ 0.025f, 0.025f });
				p.transform.SetTranslation(vector2{ startX, 1.f });
				float rotation = static_cast<float>(rand() % 314) / 100.f;
				p.transform.SetRotation(rotation);
				p.transform.SetDepth(Depth_Standard::HUD);
				p.life = 1.f;
				p.color = colors[rand() % 3];
				p.velocity = vector2{ 0.f, -2.5f };

				return p;
			},
			[&](Particle::ParticleObject& p, float dt)
			{
				p.transform.SetTranslation(p.transform.GetTranslation() + (dt * p.velocity));
			}
			);
		confetti->SetObjectName("Confetti Emitter");
		confetti->SetParticleImage("../assets/textures/circle.png");
		confetti->SetDepth(Depth_Standard::HUDFrontVFX);
	}

	currentSelection = Back2Main;

	if (selectionHighlight == nullptr)
	{
		selectionHighlight = new Object();
		Sprite* spriteOfSelectionHighlight = new Sprite(selectionHighlight);
		selectionHighlight->AddComponent(spriteOfSelectionHighlight);
		selectionHighlight->SetObjectName("Selection Highlight");
		selectionHighlight->SetDepth(Depth_Standard::HUDBackImage);
		selectionHighlight->GetTransform().SetParent(&offset);
		// Update transforms of this object based on currentSelection
		UpdateSelectionHighlightTransformation();
		// Transparency and other stuff
	}
}

void SceneComplete::CleanAssets() noexcept
{
	menuBackground = nullptr;
	backToMain = nullptr;
	goToNextLevel = nullptr;
	confetti = nullptr;
	selectionHighlight = nullptr;
	currentSelection = Back2Main;
	isTransparency = true;
}
