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
#include "Input.hpp"

namespace
{
    void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        input.SetKeyboardInput(key, action);
    }
    void MousePositionCallback(GLFWwindow* window, double xPos, double yPos)
    {
        input.SetMousePos(xPos, yPos);
    }
    //void WindowSizeCallback(GLFWwindow *window, int width,int height)
    //{
    //    xSize = width;
    //    ySize = height;
    //}
}

bool PlatformWindow::CreateWindow() noexcept
{

    if (!glfwInit())
    {
        return false;
    }

    xPos = 100;
    yPos = 100;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    window = glfwCreateWindow(xSize, ySize, "engine", nullptr, nullptr);
    glfwSetWindowPos(window, xPos, yPos);

    if (!window)
    {
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MousePositionCallback);
    //glfwSetWindowSizeCallback(window, WindowSizeCallback);
    glfwSwapInterval(true);

	glewInit();

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

bool PlatformWindow::IsFullscreen() noexcept
{
    return glfwGetWindowMonitor(window);
}

void PlatformWindow::ToggleFullscreen() noexcept
{
    if (!IsFullscreen())
    {
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
       
        glfwGetWindowPos(window, &xPos, &yPos);
        glfwGetWindowSize(window, &xSize, &ySize);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
        glViewport(0, 0, mode->width, mode->height);
        windowSize.width = mode->width;
        windowSize.height = mode->height;
    }
    else
    {
        glfwSetWindowMonitor(window, nullptr, xPos, yPos, xSize, ySize, 0);
        glViewport(0, 0, xSize, ySize);
        windowSize.width = xSize;
        windowSize.height = ySize;
    }
}

 vector2 PlatformWindow::GetPlatformWindowSize() noexcept
{
    return windowSize;
}