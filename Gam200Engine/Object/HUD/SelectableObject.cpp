/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SelectableObject.cpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 04.02.2020

    Source file for an parent object of all selectable Object.hpp
******************************************************************************/
#include <Object/HUD/SelectableObject.hpp>

SelectableObject::~SelectableObject()
{
}

bool SelectableObject::IsSelected() const noexcept
{
	return isSelected;
}

void SelectableObject::SetIsSelected(bool is) noexcept
{
	isSelected = is;
}