/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 08.15.2019 (Liberation Day! :)

	Source file for the Component.cpp
******************************************************************************/
#include "Component.hpp"

Component::Component(Object* obj) noexcept
	:owner(obj)
{
}