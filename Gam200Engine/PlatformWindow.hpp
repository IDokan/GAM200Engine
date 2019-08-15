/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   PlatformWindow.hpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Header file for the PlatformWindow.cpp
******************************************************************************/
#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "Vector2.hpp"

class PlatformWindow
{
public:
    bool CreateWindow() noexcept;
    void PollEvent() noexcept;
    void SwapBackBuffer() noexcept;
    void ToggleFullscreen() noexcept;
    bool IsFullscreen() noexcept;
    void TurnOnMonitorVerticalSynchronization(bool enable) noexcept;
    bool IsMonitorVerticalSynchronizationOn() noexcept;
     vector2 GetPlatformWindowSize() noexcept;

private:
    GLFWwindow* window;
    
    int xPos, yPos;
    int xSize = 1600;
    int ySize = 900;
    bool isVsyncOn;
     vector2 windowSize{ xSize, ySize };

};