/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringLengthUI.hpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 03.30.2020

    Header file for an interface object of BodyOfStringLengthUI
        When string start to stretch, this showed up
******************************************************************************/
#pragma once

#include <Object/Object.hpp>

class BodyOfStringLengthUI;

class StringLengthUI : public Object
{
public:
    StringLengthUI();
    ~StringLengthUI();

private:
    BodyOfStringLengthUI* body;
};