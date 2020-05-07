/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SelectableObject.hpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 04.02.2020

    Header file for an parent object of all selectable Object.hpp
******************************************************************************/
#pragma once

#include <Object/Object.hpp>

class SelectableObject : public Object
{
public:

public:
	SelectableObject()
	: isSelected(false)
	{}
	~SelectableObject();

	bool IsSelected() const noexcept;
	void SetIsSelected(bool is) noexcept;

protected:
	bool isSelected;
};