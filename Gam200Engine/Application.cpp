#include "Application.hpp"
#include "Window.hpp"

Application* Application::GetApplication()
{
    static Application* app = new Application;
    return app;
}

void Application::Init()
{
    window.CreateWindow();
}

void Application::Update(float dt)
{
    fpsEllapsedTime += dt;
    ++fpsFrames;
    if (fpsEllapsedTime >= 1.0f)
    {
        fpsEllapsedTime = 0;
        fpsFrames = 0;
    }
    window.PollEvent();
    window.SwapBackBuffer();
}

void Application::Clear()
{
}
