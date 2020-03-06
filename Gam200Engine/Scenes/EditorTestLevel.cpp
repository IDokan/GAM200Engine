/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   EditorTestLevel.hpp
Author
	- Jiwon Jung jjwon6218@gmail.com

Creation Date: 02.27.2020

	Source file for level that tests result of the editor
******************************************************************************/
#include <Scenes/EditorTestLevel.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/StateMachine.hpp>
#include <States/Walking.hpp>
#include <Object/Players/Player.h>

EditorTestLevel::EditorTestLevel(): background(nullptr)
{
}

EditorTestLevel::~EditorTestLevel()
{
}

void EditorTestLevel::Load()
{
	fileIO* a = 0;
	a->Input("../assets/fileIO/saveloadFile.txt");

	EditorTestLevel::InitObject();
	cameraManager.Init();
}


void EditorTestLevel::Update(float /*dt*/)
{
	EditorTestLevel::Input();

	vector2 obj1Position, obj2Position;

	const auto& testObjectContainer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
	for (const auto& object : testObjectContainer)
	{
		if (object->GetObjectType() == Object::ObjectType::PLAYER_1)
		{
			obj1Position = object->GetComponentByTemplate<Physics>()->GetPosition();
			object->SetTranslation(obj1Position);
		}
		else if (object->GetObjectType() == Object::ObjectType::PLAYER_2)
		{
			obj2Position = object->GetComponentByTemplate<Physics>()->GetPosition();
			object->SetTranslation(obj2Position);
		}
	}
	
}

void EditorTestLevel::GameRestart()
{
}


void EditorTestLevel::Unload()
{
}

void EditorTestLevel::Input()
{
}

void EditorTestLevel::Collision()
{
}

void EditorTestLevel::InitObject()
{
	background = new Object();
	background->SetObjectName("background1");
	background->SetTranslation(vector2{ 1.f });
	background->SetScale(vector2{ 1000.f });
	background->AddComponent(new Sprite(background));
	background->AddComponent(new Physics(background));
	background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

	auto objManager = ObjectManager::GetObjectManager();
	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
}
