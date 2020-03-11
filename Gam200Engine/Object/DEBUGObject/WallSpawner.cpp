/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   WallSpawner.cpp
Author
	- Sinil.Kang rtd99062@gmail.com

Creation Date: 12.12.2019

	Source file for object that make add object
******************************************************************************/
#include <Object/DEBUGObject/WallSpawner.hpp>
#include <Object/ObjectManager.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Component/Physics.hpp>

WallSpawner::WallSpawner()
	:Object(), counter(0)
{
	SetObjectName("WallSpawner");
	SetDepth(-50.f);
	SetScale(vector2{ 100.f });
}

WallSpawner::~WallSpawner()
{
}

void WallSpawner::SpawnWall()
{
	Object* obj = new Object();
	obj->SetObjectName("TestSpawnedObject" + std::to_string(counter++));
	obj->SetTranslation(GetTranslation());
	obj->SetScale(GetScale());
	obj->SetRotation(GetRotation());
	obj->SetDepth(GetDepth());
	obj->AddComponent(new Sprite(obj));
	obj->AddComponent(new Physics(obj));
	obj->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(obj, Physics::ObjectType::RECTANGLE);
	obj->SetObjectType(ObjectType::TEST);
	
	ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->AddObjectDynamically(obj);
}
