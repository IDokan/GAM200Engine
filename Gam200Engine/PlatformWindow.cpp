/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   PlatformWindow.cpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Source file for making window
******************************************************************************/
#include "PlatformWindow.hpp"

bool PlatformWindow::CreateWindow() noexcept
{
    if (!glfwInit())
    {
        return false;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    window = glfwCreateWindow(1280, 1080, "engine", nullptr, nullptr);

    if (!window)
    {
        return false;
    }

    glfwSwapInterval(true);
    glfwMakeContextCurrent(window);
    
    return true;
}

void PlatformWindow::PollEvent() noexcept
{
    glfwPollEvents();
}

void PlatformWindow::SwapBackBuffer() noexcept
{
    glfwSwapBuffers(window);
}
