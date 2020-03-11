/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   KeyHelpers.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.30.2019

	Source file for Key helper functions
		Use it rather than using input.IsKeySomething(Some GLFW Key Value).....
******************************************************************************/
#include <Systems/KeyHelpers.hpp>
#include <Systems/Input.hpp>

namespace KeyHelpers
{

	bool IsSnapButtonTriggered()
	{
		return input.IsKeyTriggered(GLFW_KEY_LEFT_CONTROL);
	}
	bool IsSnapButtonPressed()
	{
		return input.IsKeyPressed(GLFW_KEY_LEFT_CONTROL);
	}
	bool IsMoveButtonTriggered()
	{
		return input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_LEFT);
	}
	bool IsMoveButtonReleased()
	{
		return input.IsMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT);
	}
}