/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StatusUI.hpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 05.05.2020

    Header file for Status UI
******************************************************************************/
#pragma once

#include <Object/Object.hpp>

class StatusUI : public Object
{
public:
	StatusUI();
    ~StatusUI();

	Object* animation;
};