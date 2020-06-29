/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.cpp
Author
	- Jiwon.Jung       jjwon6218@gmail.com

Creation Date: 03.18.2020

	Source file for component to make checkpoint
******************************************************************************/
#include "Checkpoint.hpp"
#include <Systems/FileIO.hpp>

CheckPoint::CheckPoint(const std::filesystem::path& filePath, Object* obj)
	:checkpoint(obj), fileName(filePath), Component(obj), player1Reached(false), player2Reached(false)
{
	checkpointPos = obj->GetTranslation(); //position of checkpoint
	checkpointScale = obj->GetScale(); // scale of checkpoint
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::Init()
{
}

void CheckPoint::Update(float dt)
{
	//check if players touched checkpoint
	SaveReach();

	if (player1Reached && player2Reached)
	{
		//save the informations and reset the booleans
		Save();
		player1Reached = false;
		player2Reached = false;
	}
}

void CheckPoint::Clear()
{
}

void CheckPoint::Save()
{
	fileIO* fileio = new fileIO;
	fileio->Output(fileName);
}

void CheckPoint::SaveReach()
{
	const auto& playerFinder = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
	for (const auto& object : playerFinder)
	{
		//check if players collided with checkpoint box
		if (object->GetObjectType() == Object::ObjectType::PLAYER_1)
		{
			if (object->GetComponentByTemplate<Physics>()->IsCollideWith(checkpoint))
				player1Reached = true;
		}
		else if (object->GetObjectType() == Object::ObjectType::PLAYER_2)
		{
			if (object->GetComponentByTemplate<Physics>()->IsCollideWith(checkpoint))
				player2Reached = true;
		}
	}
}
