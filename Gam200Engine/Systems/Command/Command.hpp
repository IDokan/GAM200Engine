/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Command.hpp
Author
		sinil.gang
			rtd99062@gmail.com
Creation Date: 23th/Jan/2020

	Header file for Command virtual ancestor class
******************************************************************************/
#pragma once
#include <GLFW/glfw3.h>

class Command
{
public:
	Command(unsigned int KEY)
		:GLFW_KEY(KEY)
	{}
	virtual ~Command() {}
	virtual void execute() = 0;

	unsigned int GLFW_KEY = GLFW_KEY_LAST;
};