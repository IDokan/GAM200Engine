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

class PlatformWindow
{
public:
    bool CreateWindow() noexcept;
    void PollEvent() noexcept;
    void SwapBackBuffer() noexcept;

private:
    GLFWwindow* window;
};