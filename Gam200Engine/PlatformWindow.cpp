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
#define UNUSED

#include "PlatformWindow.hpp"
#include "Input.hpp"
#include <Graphics/glCheck.hpp>
#include <Graphics/GL.hpp>

namespace
{
    void KeyCallback(GLFWwindow *, int key, int scancode, int action, int)
    {
        UNUSED(scancode);
        input.SetKeyboardInput(key, action);
    }
    void MousePositionCallback(GLFWwindow* , double xPos, double yPos)
    {
        input.SetMousePos(static_cast<float>(xPos), static_cast<float>(yPos));
    }
    void MouseButtonCallback(GLFWwindow* , int button, int action, int )
    {
        input.SetMouseButtonInput(button, action);
    }
    void MouseWheelScroll(GLFWwindow* , double x_offset, double y_offset)
    {
        input.SetMouseWheel(x_offset, y_offset);
    }
    void WindowSizeCallback(GLFWwindow *, int width,int height)
    {
        Graphics::GL::set_display_area(width, height);
    }
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
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, MouseWheelScroll);
    glfwSetWindowSizeCallback(window, WindowSizeCallback);
    glfwSwapInterval(true);

    glewInit();

    return true;
}

void PlatformWindow::PollEvent() noexcept
{
    glCheck(glfwPollEvents());
}

void PlatformWindow::SwapBackBuffer() noexcept
{
    glCheck(glfwSwapBuffers(window));
}

bool PlatformWindow::IsFullscreen() noexcept
{
    return glfwGetWindowMonitor(window);
}

void PlatformWindow::TurnOnMonitorVerticalSynchronization(bool enable) noexcept
{
    isVsyncOn = enable;
    glCheck(glfwSwapInterval(enable));
}

bool PlatformWindow::IsMonitorVerticalSynchronizationOn() noexcept
{
    return isVsyncOn;
}

void PlatformWindow::ToggleFullscreen() noexcept
{
    if (!IsFullscreen())
    {
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
       
        glCheck(glfwGetWindowPos(window, &xPos, &yPos));
        glCheck(glfwGetWindowSize(window, &xSize, &ySize));
        glCheck(glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0));
        glCheck(glViewport(0, 0, mode->width, mode->height));
        windowSize.width = static_cast<float>(mode->width);
        windowSize.height = static_cast<float>(mode->height);
    }
    else
    {
        glCheck(glfwSetWindowMonitor(window, nullptr, xPos, yPos, xSize, ySize, 0));
        glCheck(glViewport(0, 0, xSize, ySize));
        windowSize.width = static_cast<float>(xSize);
        windowSize.height = static_cast<float>(ySize);
    }
}

 vector2 PlatformWindow::GetPlatformWindowSize() noexcept
{
    return windowSize;
}