#include "Engine.hpp"
#include "Application.hpp"

Application* app_ = nullptr;

void Engine::Init()
{
    app_ = Application::GetApplication();
    app_->Init();
    timer.Reset();
    isRunning = false;
}

void Engine::Update()
{
    dt = static_cast<float>(timer.GetElapsedSeconds());
    timer.Reset();
    app_->Update(dt);
}

void Engine::Clear()
{
}
