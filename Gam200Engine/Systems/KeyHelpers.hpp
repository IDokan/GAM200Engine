/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   KeyHelpers.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.30.2019

	Header file for Key helper functions
		Use it rather than using input.IsKeySomething(Some GLFW Key Value).....
******************************************************************************/

namespace KeyHelpers
{
	// Snap Button is Left Ctrl
	bool IsSnapButtonPressed();
	bool IsSnapButtonTriggered();

	// Move Button is Mouse Left Button
	bool IsMoveButtonTriggered();
	bool IsMoveButtonReleased();
}