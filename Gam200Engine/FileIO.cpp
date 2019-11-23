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
#include <fstream>
void fileIO::input()
{
	ObjectData* object;
	
	std::ofstream outStream;
	outStream.open("objectData.txt");

	while(!outStream.eof())
	{
		object = new ObjectData;
		outStream << object->playername << std::endl;
		outStream << object->transform << std::endl;
		outStream << object->size << std::endl;
		outStream << object->objectType << std::endl;
	}
}
