/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   VolumeSettingBarUI.hpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 04.02.2020

    Header file for an actual objects of VolumeSettingBar
******************************************************************************/
#pragma once

#include <Object/HUD/SelectableObject.hpp>

class VolumeSettingUIHandler;

class VolumeSettingBar : public SelectableObject
{
public:
    static constexpr float maxX = 500.f;
    static constexpr float minX = -500.f;
    friend VolumeSettingUIHandler;
public:
    VolumeSettingBar(vector2 translation);
    ~VolumeSettingBar();

private:
    void InitUIObjects();

    Object* outline;
    Object* background;
    Object* bar;
    Object* fillBar;
    Object* circle;
    Object* circleOutline;
    Object* text;
};