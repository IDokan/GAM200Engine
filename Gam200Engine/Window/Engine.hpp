/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Engine.hpp
Author 
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Header file for the Engine.cpp
******************************************************************************/
#pragma once
#include <Systems/Timer.hpp>

class Application;

class Engine
{
public:
    Engine() = default;

    void Init();
    void Update();
    void Clear();

    bool GetIsRunnig() noexcept
    {
        return isRunning;
    }

private:
    float timea = 0;
    bool isRunning = false;
    float dt=0;
    Timer timer;
};