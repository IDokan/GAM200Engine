/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Button.hpp
Author
		jjwon6218@gmail.com
Creation Date: March 16th, 2020

	Header file for buttons in menu scene
******************************************************************************/
#pragma once
#include <Object/Object.hpp>

class Button : public Object
{
public:
	enum class ButtonIdentifier
	{
		NextLevel,
		Quit,
	};
public:
	explicit Button(ButtonIdentifier button, const Transform& buttonTransformData = Transform());

private:
	ButtonIdentifier id;
};