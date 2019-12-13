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

void fileIO::Input(const std::filesystem::path& filePath)
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
		
		Object* object = new Object(); // Make new object
		
		inStream >> objectName;		   // Object Name
		inStream >> xTrans;            // x value of translation
		inStream >> yTrans;            // y value of translation
		inStream >> xScale;            // x value of scale
		inStream >> yScale;            // y value of scale
		inStream >> depth;             // depth value
		inStream >> objectType;        // object type
		inStream >> spriteFileName;    // File path of sprite file
		
		object->SetObjectName(objectName);
		object->SetTranslation(vector2{ xTrans, yTrans });
		object->SetScale(vector2{ xScale, yScale });
		object->AddComponent(new Sprite(object));
		object->AddComponent(new Physics(object));
		
		if(objectType == "player1")
		{
			object->SetObjectType(Object::ObjectType::PLAYER_1);
		}
		else if(objectType == "player2")
		{
			object->SetObjectType(Object::ObjectType::PLAYER_2);
		}
		else if(objectType == "obstacle")
		{
			object->SetObjectType(Object::ObjectType::OBSTACLE);
		}
		else if(objectType == "test")
		{
			object->SetObjectType(Object::ObjectType::TEST);
		}
		if(spriteFileName != "no")
		{
			object->GetComponentByTemplate<Sprite>()->SetImage(spriteFileName);
		}
		
		object->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object, Physics::ObjectType::RECTANGLE);
		object->SetDepth(depth);
		objManager->FindLayer(LayerNames::Stage)->AddObject(object);
	}
	inStream.close();
}

void fileIO::Output()
{
	std::ofstream saveLoad("../assets/fileIO/saveloadFile.txt");

	int i = 0;
	const auto& loadsaveObjectContainer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
	for (const auto& object : loadsaveObjectContainer)
	{
		if (object->GetObjectType() == Object::ObjectType::TEST)
		{
			++i;
		}
	}
	int j = 0;
	for(const auto& object : loadsaveObjectContainer)
	{
		if(object->GetObjectType() == Object::ObjectType::TEST)
		{
			++j;
			saveLoad << object->GetObjectName() << ' ';
			saveLoad << object->GetTranslation().x << ' ';
			saveLoad << object->GetTranslation().y << ' ';
			saveLoad << object->GetScale().x << ' ';
			saveLoad << object->GetScale().y << ' ';
			saveLoad << object->GetDepth() << ' ';
			saveLoad << "test" << ' ';
			saveLoad << object->GetComponentByTemplate<Sprite>()->GetImagePath();
			if(i != j)
				saveLoad << '\n';
		}
	}

	saveLoad.close();

	/*********************************Output for object type: TEST*****************************************/
	
	std::ofstream outputTEST("../assets/fileIO/OutputFiles/objectOutput_TEST.txt");

	outputTEST << "Name" << '/';
	outputTEST << "x_pos" << '/';
	outputTEST << "y_pos" << '/';
	outputTEST << "x_scale" << '/';
	outputTEST << "y_scale" << '/';
	outputTEST << "depth" << '/';
	outputTEST << "object_type" << '/';
	outputTEST << "file_path" << '\n';
	outputTEST << '\n';
	
	int m = 0;
	const auto& testObjectContainer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
	for (const auto& object : testObjectContainer)
	{
		if (object->GetObjectType() == Object::ObjectType::TEST)
		{
			++m;
		}
	}
	int n = 0;
	for (const auto& object : testObjectContainer)
	{
		if (object->GetObjectType() == Object::ObjectType::TEST)
		{
			++n;
			outputTEST << object->GetObjectName() << ' ';
			outputTEST << object->GetTranslation().x << ' ';
			outputTEST << object->GetTranslation().y << ' ';
			outputTEST << object->GetScale().x << ' ';
			outputTEST << object->GetScale().y << ' ';
			outputTEST << object->GetDepth() << ' ';
			outputTEST << "test" << ' ';
			outputTEST << object->GetComponentByTemplate<Sprite>()->GetImagePath();
			if (m != n)
				outputTEST << '\n';
		}
	}
	outputTEST.close();

	/**********************************Output for object type: OBSTACLE*******************************************/

	std::ofstream outputOBSTACLE("../assets/fileIO/OutputFiles/objectOutput_OBSTACLE.txt");

	outputOBSTACLE << "Name" << '/';
	outputOBSTACLE << "x_pos" << '/';
	outputOBSTACLE << "y_pos" << '/';
	outputOBSTACLE << "x_scale" << '/';
	outputOBSTACLE << "y_scale" << '/';
	outputOBSTACLE << "depth" << '/';
	outputOBSTACLE << "object_type" << '/';
	outputOBSTACLE << "file_path" << '\n';
	outputOBSTACLE << '\n';


	int x = 0;
	const auto& obstacleObjectContainer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
	for (const auto& object : obstacleObjectContainer)
	{
		if (object->GetObjectType() == Object::ObjectType::OBSTACLE)
		{
			++x;
		}
	}
	int y = 0;
	for (const auto& object : obstacleObjectContainer)
	{
		if (object->GetObjectType() == Object::ObjectType::OBSTACLE)
		{
			++y;
			outputOBSTACLE << object->GetObjectName() << ' ';
			outputOBSTACLE << object->GetTranslation().x << ' ';
			outputOBSTACLE << object->GetTranslation().y << ' ';
			outputOBSTACLE << object->GetScale().x << ' ';
			outputOBSTACLE << object->GetScale().y << ' ';
			outputOBSTACLE << object->GetDepth() << ' ';
			outputOBSTACLE << "obstacle" << ' ';
			outputOBSTACLE << object->GetComponentByTemplate<Sprite>()->GetImagePath();
			if (x != y)
				outputOBSTACLE << '\n';
		}
	}

	outputOBSTACLE.close();
	
	/********************************Output for object type: PLAYER_1, PLAYER_2******************************************/

	std::ofstream outputPLAYER("../assets/fileIO/OutputFiles/objectOutput_PLAYER.txt");

	outputPLAYER << "Name" << '/';
	outputPLAYER << "x_pos" << '/';
	outputPLAYER << "y_pos" << '/';
	outputPLAYER << "x_scale" << '/';
	outputPLAYER << "y_scale" << '/';
	outputPLAYER << "depth" << '/';
	outputPLAYER << "object_type" << '/';
	outputPLAYER << "file_path" << '\n';
	outputPLAYER << '\n';


	int a = 0;
	const auto& playerObjectContainer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
	for (const auto& object : playerObjectContainer)
	{
		if (object->GetObjectType() == Object::ObjectType::PLAYER_1)
		{
			++a;
		}
		else if (object->GetObjectType() == Object::ObjectType::PLAYER_2)
		{
			++a;
		}
	}
	int b = 0;
	for (const auto& object : playerObjectContainer)
	{
		if (object->GetObjectType() == Object::ObjectType::PLAYER_1)
		{
			++b;
			outputPLAYER << object->GetObjectName() << ' ';
			outputPLAYER << object->GetTranslation().x << ' ';
			outputPLAYER << object->GetTranslation().y << ' ';
			outputPLAYER << object->GetScale().x << ' ';
			outputPLAYER << object->GetScale().y << ' ';
			outputPLAYER << object->GetDepth() << ' ';
			outputPLAYER << "player1" << ' ';
			outputPLAYER << object->GetComponentByTemplate<Sprite>()->GetImagePath();
			if (a != b)
				outputPLAYER << '\n';
		}

		if (object->GetObjectType() == Object::ObjectType::PLAYER_2)
		{
			++b;
			outputPLAYER << object->GetObjectName() << ' ';
			outputPLAYER << object->GetTranslation().x << ' ';
			outputPLAYER << object->GetTranslation().y << ' ';
			outputPLAYER << object->GetScale().x << ' ';
			outputPLAYER << object->GetScale().y << ' ';
			outputPLAYER << object->GetDepth() << ' ';
			outputPLAYER << "player2" << ' ';
			outputPLAYER << object->GetComponentByTemplate<Sprite>()->GetImagePath();
			if (a != b)
				outputPLAYER << '\n';
		}
	}

	outputPLAYER.close();
}
