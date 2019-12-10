#pragma once
/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   FileIO.hpp
Author
    - jiwon.jung jjwon6218@gmail.com
Creation Date: 11.23.2019

    Source file for file IO
******************************************************************************/
#include <Object/Object.hpp>
#include <fstream>
#include <Object/ObjectManager.hpp>
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <string>

class fileIO
{
public:
	void Input(const std::filesystem::path& filePath); //, const std::filesystem::path& texturePath
	void Output();
};