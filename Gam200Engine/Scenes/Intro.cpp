/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Intro.cpp
Author
	- sinil.gang rtd99062@gmail.com
Creation Date: 07.06.2020

	Source file for intro
******************************************************************************/
#include <Scenes/Intro.hpp>
#include <Object/Object.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Object/DepthStandard.hpp>
#include <Scenes/SceneManager.hpp>
#include <Systems/Input.hpp>

Intro::Intro()
	: digipenLogo(nullptr), fmodLogo(nullptr), time(0.f)
{
	isMenu = true;
}

Intro::~Intro()
{
}

void Intro::Update(float dt)
{
	time += dt;

	// Input Trigger
	if (input.IsAnyKeyTriggered())
	{
		time += 5.f;
	}

	// Update depend on timer
	if (time < 4.f)
	{
		digipenSprite->SetColor(Graphics::Color4f(1.f));
	}
	else if (time >= 4.f && time < 5.f)
	{
		digipenSprite->SetColor(Graphics::Color4f(5.f - time));
	}
	else if (time >= 5.f && time < 6.f)
	{
		digipenSprite->SetColor(Graphics::Color4f(0.f, 0.f));
		fmodSprite->SetColor(Graphics::Color4f(time - 5.f));
	}
	else if (time >= 6.f && time < 10.f)
	{
		digipenSprite->SetColor(Graphics::Color4f(0.f, 0.f));
		fmodSprite->SetColor(Graphics::Color4f(1.f));
	}
	else
	{
		SceneManager::GetSceneManager()->SetNextScene("MenuScene");
	}
}

void Intro::GameRestart()
{
}

void Intro::Load()
{
	fmodLogo = new Object();
	fmodSprite = new Sprite(fmodLogo);
	fmodLogo->AddComponent(fmodSprite);
	fmodSprite->SetImage("../assets/textures/Logos/FmodLogo.png");
	fmodLogo->SetScale(vector2{ 728.f, 200.f });
	fmodLogo->SetObjectName("Fmod Logo");
	fmodSprite->SetColor(Graphics::Color4f(0.f));
	fmodLogo->SetDepth(Depth_Standard::Background - 1.f);


	digipenLogo = new Object();
	digipenSprite = new Sprite(digipenLogo);
	digipenSprite->SetImage("../assets/textures/Logos/DigipenLogo.png");
	digipenSprite->SetColor(Graphics::Color4f(0.f));
	digipenLogo->AddComponent(digipenSprite);
	digipenLogo->SetObjectName("DigiPen Logo");
	digipenLogo->SetScale(vector2{ 1030.f, 260.f });
	digipenLogo->SetDepth(Depth_Standard::Background);

	ObjectManager* objManager = ObjectManager::GetObjectManager();
	objManager->FindLayer(LayerNames::Stage)->AddObject(fmodLogo);
	objManager->FindLayer(LayerNames::Stage)->AddObject(digipenLogo);
}

void Intro::Unload()
{
}
