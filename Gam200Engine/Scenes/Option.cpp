/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Option.cpp
Author
	- Sinil.Kang rtd99062@gmail.com

Creation Date: 04.02.2020

	Source file for level that change Game's settings
******************************************************************************/

#include <Scenes/Option.hpp>

#include <Systems/FileIO.hpp>
#include <Object/HUD/SelectableObject.hpp>
#include <Object/HUD/VolumeSettingBarUI.hpp>
#include <Object/HUD/FullScreenSettingUI.hpp>
#include <Object/Object.hpp>
#include <Object/DepthStandard.hpp>

#include <Systems/Input.hpp>
#include <Scenes/SceneManager.hpp>

#include <Angle.hpp>

OptionLevel::OptionLevel()
	: fullScreen(nullptr), volume(nullptr), leftArrow(nullptr), rightArrow(nullptr)
{
}

OptionLevel::~OptionLevel()
{
}

void OptionLevel::Update(float /*dt*/)
{
	if (input.IsKeyTriggered(GLFW_KEY_UP))
	{
		volume->SetIsSelected(false);
		fullScreen->SetIsSelected(true);
		SetArrowsYPosition(fullScreen->GetTranslation().y);
	}
	else if(input.IsKeyTriggered(GLFW_KEY_DOWN))
	{
		volume->SetIsSelected(true);
		fullScreen->SetIsSelected(false);
		SetArrowsYPosition(volume->GetTranslation().y);
	}

	if (input.IsKeyTriggered(GLFW_KEY_ESCAPE))
	{
		SceneManager::GetSceneManager()->SetNextScene("MenuScene");
	}
}

void OptionLevel::GameRestart()
{
}

void OptionLevel::Load()
{
	InitObjects();
	volume->SetIsSelected(true);
}

void OptionLevel::Unload()
{	

}

void OptionLevel::SetArrowsYPosition(float y) noexcept
{
	leftArrow->SetTranslation(vector2{ leftArrow->GetTranslation().x, y });
	rightArrow->SetTranslation(vector2{ rightArrow->GetTranslation().x, y });
}

void OptionLevel::InitObjects()
{
	ObjectManager* objManager = ObjectManager::GetObjectManager();
	volume = new VolumeSettingBar(vector2{ 0.f, -130.f });
	objManager->FindLayer(Stage)->AddObject(volume);

	fullScreen = new FullScreenSettingUI(vector2{ 0.f, 158.f });
	objManager->FindLayer(Stage)->AddObject(fullScreen);

	leftArrow = new Object();
	leftArrow->SetObjectName("Left Arrow");
	leftArrow->SetObjectType(Object::ObjectType::UI);
	leftArrow->SetTranslation(vector2{ -600.f, volume->GetTranslation().y });
	leftArrow->SetScale(vector2{ 100.f });
	leftArrow->AddComponent(new Sprite(leftArrow));
	leftArrow->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/Arrow.png");
	leftArrow->SetDepth(Depth_Standard::HUDImage);
	objManager->FindLayer(Stage)->AddObject(leftArrow);

	rightArrow = new Object();
	rightArrow->SetObjectName("Left Arrow");
	rightArrow->SetObjectType(Object::ObjectType::UI);
	rightArrow->SetTranslation(vector2{ 600.f, volume->GetTranslation().y });
	rightArrow->SetScale(vector2{ 100.f });
	rightArrow->AddComponent(new Sprite(rightArrow));
	rightArrow->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/Arrow.png");
	rightArrow->SetDepth(Depth_Standard::HUDImage);
	rightArrow->SetRotation(MATH::PI);
	objManager->FindLayer(Stage)->AddObject(rightArrow);

	Object* background = new Object();
	background->SetObjectName("Background");
	background->SetScale(vector2{ 2000.f, 1000.f });
	background->SetDepth(Depth_Standard::Background);
	background->SetObjectType(Object::ObjectType::Default);
	background->AddComponent(new Sprite(background));
	background->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{0.735f, 0.45f, 0.0f});
	objManager->FindLayer(Stage)->AddObject(background);
}
