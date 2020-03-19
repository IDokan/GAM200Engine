/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   FileIO.cpp
Author
    - jiwon.jung jjwon6218@gmail.com
Creation Date: 11.23.2019

    Source file for file IO
******************************************************************************/
#include "FileIO.hpp"
#include "Vector2.hpp"
#include <iostream>
#include <Component/Scripts/GoalComponent.hpp>

void fileIO::Input(const std::filesystem::path& filePath, Player** player1, Player** player2, String** string)
{
	auto objManager = ObjectManager::GetObjectManager();

	std::ifstream inStream;
	std::string objectName;
	inStream.open(filePath);
	
	if(inStream.is_open() == false)
	{
		std::cout << "fail";
	}
	
	while (!inStream.eof()) //Loop continue until .txt file end
	{
		float xTrans;
		float yTrans;
		float xScale;
		float yScale;
		float depth;
		std::string objectType;
		std::string spriteFileName;
		
		inStream >> objectName;		   // Object Name
		inStream >> xTrans;            // x value of translation
		inStream >> yTrans;            // y value of translation
		inStream >> xScale;            // x value of scale
		inStream >> yScale;            // y value of scale
		inStream >> depth;             // depth value
		inStream >> objectType;        // object type
		inStream >> spriteFileName;    // File path of sprite file
		
		if (objectType == "player1")
		{
			Transform transform;
			transform.SetTranslation(vector2{ xTrans, yTrans });
			transform.SetScale(vector2{ xScale, yScale });
			transform.SetDepth(depth);

			*player1 = new Player(Player::Identifier::Player1, transform);
			objManager->FindLayer(LayerNames::Stage)->AddObject(*player1);
		}
		else if (objectType == "player2")
		{
			Transform transform;
			transform.SetTranslation(vector2{ xTrans, yTrans });
			transform.SetScale(vector2{ xScale, yScale });
			transform.SetDepth(depth);
			*player2 = new Player(Player::Identifier::Player2, transform);
			
			*string = new String(*player1, *player2);

			objManager->FindLayer(LayerNames::Stage)->AddObject(*player2);
			objManager->FindLayer(LayerNames::Stage)->AddObject(*string);
		}
		else if (objectType == "background")
		{
			Object* object = new Object();
			object->SetObjectName(objectName);
			object->SetTranslation(vector2{ xTrans, yTrans });
			object->SetScale(vector2{ xScale, yScale });
			object->AddComponent(new Sprite(object));
			object->AddComponent(new Physics(object));
			object->GetComponentByTemplate<Sprite>()->SetImage(spriteFileName);

			objManager->FindLayer(LayerNames::BackGround)->AddObject(object);
		}
		else if ((objectType != "player1") && (objectType != "player2") && (objectType != "background"))
		{
			Object* object = new Object(); // Make new object
			object->SetObjectName(objectName);
			object->SetTranslation(vector2{ xTrans, yTrans });
			object->SetScale(vector2{ xScale, yScale });
			object->AddComponent(new Sprite(object));

			if (objectType == "obstacle")
			{
				object->AddComponent(new Physics(object));
				object->SetObjectType(Object::ObjectType::OBSTACLE);

				if (spriteFileName != "no")
				{
					object->GetComponentByTemplate<Sprite>()->SetImage(spriteFileName);
				}
			}
			else if (objectType == "test")
			{
				object->AddComponent(new Physics(object));
				object->SetObjectType(Object::ObjectType::TEST);

				if (spriteFileName != "no")
				{
					object->GetComponentByTemplate<Sprite>()->SetImage(spriteFileName);
				}
			}
			else if (objectType == "startpoint")
			{
				object->AddComponent(new Physics(object));
				object->SetObjectType(Object::ObjectType::TEST);
				object->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
			}
			else if (objectType == "goalpoint")
			{
				object->AddComponent(new GoalComponent(object, spriteFileName));
				object->AddComponent(new Physics(object));
				object->SetObjectType(Object::ObjectType::TEST);
				object->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
			}
			
			object->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object, Physics::ObjectType::RECTANGLE);
			object->SetDepth(depth);
			objManager->FindLayer(LayerNames::Stage)->AddObject(object);
		}
		
	}
	inStream.close();
}

void fileIO::Output(const std::filesystem::path& outFilePath)
{
	std::ofstream saveLoad(outFilePath);

	int i = 0;
	const auto& loadsaveObjectContainer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
	for (const auto& object : loadsaveObjectContainer)
	{
		if ((object->GetObjectType() == Object::ObjectType::OBSTACLE)
			|| (object->GetObjectType() == Object::ObjectType::PLAYER_1)
			|| (object->GetObjectType() == Object::ObjectType::PLAYER_2)
			|| (object->GetObjectType() == Object::ObjectType::TEST))
		{
			++i;
		}
	}
	int j = 0;
	for(const auto& object : loadsaveObjectContainer)
	{
		if(object->GetObjectType() == Object::ObjectType::OBSTACLE)
		{
			++j;
			saveLoad << object->GetObjectName() << ' ';
			saveLoad << object->GetTranslation().x << ' ';
			saveLoad << object->GetTranslation().y << ' ';
			saveLoad << object->GetScale().x << ' ';
			saveLoad << object->GetScale().y << ' ';
			saveLoad << object->GetDepth() << ' ';
			saveLoad << "obstacle" << ' ';
			if (object->GetComponentByTemplate<Sprite>() != nullptr)
			{
				saveLoad << object->GetComponentByTemplate<Sprite>()->GetImagePath();
			}
			else
			{
				saveLoad << "no";
			}
			if (i != j)
			{
				saveLoad << '\n';
			}
		}
		else if (object->GetObjectType() == Object::ObjectType::TEST)
		{
			++j;
			saveLoad << object->GetObjectName() << ' ';
			saveLoad << object->GetTranslation().x << ' ';
			saveLoad << object->GetTranslation().y << ' ';
			saveLoad << object->GetScale().x << ' ';
			saveLoad << object->GetScale().y << ' ';
			saveLoad << object->GetDepth() << ' ';
			
			if (object->GetObjectName() == "goalPoint")
			{
				saveLoad << "goalpoint" << ' ';
				saveLoad << object->GetComponentByTemplate<GoalComponent>()->GetTargetStage();
			}
			else if (object->GetObjectName() == "startPoint")
			{
				saveLoad << "startpoint" << ' ';
			}
			else
			{
				saveLoad << "test" << ' ';
			}

			if (object->GetObjectName() != "goalPoint")
			{
				if (object->GetComponentByTemplate<Sprite>() != nullptr)
				{
					saveLoad << object->GetComponentByTemplate<Sprite>()->GetImagePath();
				}
				else
				{
					saveLoad << "no";
				}
			}
			
			if (i != j)
			{
				saveLoad << '\n';
			}
		}
		else if (object->GetObjectType() == Object::ObjectType::PLAYER_1)
		{
			++j;
			saveLoad << object->GetObjectName() << ' ';
			saveLoad << object->GetTranslation().x << ' ';
			saveLoad << object->GetTranslation().y << ' ';
			saveLoad << object->GetScale().x << ' ';
			saveLoad << object->GetScale().y << ' ';
			saveLoad << object->GetDepth() << ' ';
			saveLoad << "player1" << ' ';
			if (object->GetComponentByTemplate<Sprite>() != nullptr)
			{
				saveLoad << object->GetComponentByTemplate<Sprite>()->GetImagePath();
			}
			else
			{
				saveLoad << "no";
			}
			if (i != j)
			{
				saveLoad << '\n';
			}
		}
		else if (object->GetObjectType() == Object::ObjectType::PLAYER_2)
		{
			++j;
			saveLoad << object->GetObjectName() << ' ';
			saveLoad << object->GetTranslation().x << ' ';
			saveLoad << object->GetTranslation().y << ' ';
			saveLoad << object->GetScale().x << ' ';
			saveLoad << object->GetScale().y << ' ';
			saveLoad << object->GetDepth() << ' ';
			saveLoad << "player2" << ' ';
			if (object->GetComponentByTemplate<Sprite>() != nullptr)
			{
				saveLoad << object->GetComponentByTemplate<Sprite>()->GetImagePath();
			}
			else
			{
				saveLoad << "no";
			}
			if (i != j)
			{
				saveLoad << '\n';
			}
		}
	}

	saveLoad.close();
}
