/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   FullScreenSettingUI.hpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 04.02.2020

    Header file for an actual objects of FullScreenSettingUI
******************************************************************************/
#pragma once

#include <Object/HUD/SelectableObject.hpp>

class FullScreenUIHandler;

class FullScreenSettingUI : public SelectableObject
{
public:
    static constexpr float maxX = 500.f;
    static constexpr float minX = -500.f;
    friend FullScreenUIHandler;
public:
    FullScreenSettingUI(vector2 translation);
    ~FullScreenSettingUI();

private:
    void InitUIObjects();

    Object* checkBox;
    Object* text;
};