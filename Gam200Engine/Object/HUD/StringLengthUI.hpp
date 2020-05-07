/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringLengthUI.hpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 03.30.2020

    Header file for an actual objects of StringLengthUI
******************************************************************************/
#pragma once

#include <Object/Object.hpp>

class StringLengthUI : public Object
{
public:
    static constexpr float HIDE_Y = -1.05f;
    static constexpr float SHOW_Y = -0.9f;
public:
    StringLengthUI();
    ~StringLengthUI();

    // Only x value, which means y scale do not change!
    void SetBarScale(float x) noexcept;

private:
    void InitUIObjects();

    Object* outline;
    Object* background;
    Object* bar;
};