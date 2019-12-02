/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   FileIO.cpp
Author
    - jiwon.jung jjwon6218@gmail.com
    - Hyerin Jung (junghl0621@gmail.com)
Creation Date: 11.23.2019

    Source file for file IO
******************************************************************************/
#include "FileIO.hpp"
#include "Vector2.hpp"
#include <iostream>


// TODO: Get a File path as argument - Complete
// TODO: Make it SetImage available
// TODO: & Depth - Complete
//
// TODO: Save
// Later: Sprite get image path.
void fileIO::input(const std::filesystem::path& filePath)
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
		float xTrans, yTrans;
		float xScale, yScale;
		float depth;
		Object* object = new Object(); // Make new object
		
		inStream >> objectName;		   // Object Name
		inStream >> xTrans;            // x value of translation
		inStream >> yTrans;            // y value of translation
		inStream >> xScale;            // x value of scale
		inStream >> yScale;            // y value of scale
		inStream >> depth;             // depth value

		object->SetObjectName(objectName);
		object->SetTranslation(vector2{ xTrans, yTrans });
		object->SetScale(vector2{ xScale, yScale });
		object->AddComponent(new Sprite(object));
		object->AddComponent(new Physics(object));
		object->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object, Physics::ObjectType::RECTANGLE);
		object->SetDepth(depth);
		objManager->FindLayer(LayerNames::Stage)->AddObject(object);
	}
	inStream.close();
}
