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


void fileIO::input()
{
	Object* object;
	
	std::ifstream inStream;
	std::string s;
	inStream.open("objectData.txt");
	if(inStream.is_open())
	{
		std::cout << "fail";
	}
	
	while (!inStream.eof())
	{
		float x, y;
		float a, d;
		object = new Object();
		//std::string temp;
		//inStream >> object->GetObjectName();       // object name

		//std::getline(inStream, temp);
		//object->GetTranslation().x = (float)inStream.get();      //object translation
		//inSobject->SetTranslation().y;      //object translation
		inStream >> s;			  // Test string
		inStream >> x;            // Test number
		inStream >> y;            // Test number
		inStream >> a;            // Test number
		inStream >> d;            // Test number

		object->SetObjectName(s);
		object->SetTranslation(vector2{ x, y });
		object->SetScale(vector2{ a, d });
		//object->AddComponent(new Sprite(object));
		//object->AddComp
        //outStream << object->AddComponent << std::endl;
	}
	inStream.close();
}


void fileIO::output()
{



}