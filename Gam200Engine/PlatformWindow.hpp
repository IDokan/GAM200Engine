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