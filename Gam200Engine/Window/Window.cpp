/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Window.cpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Source file for making window
******************************************************************************/
#include <Window/Window.hpp>
#include <Window/PlatformWindow.hpp>

Window::Window() noexcept : platformWindow(std::make_unique<PlatformWindow>()) {};

Window::~Window() noexcept {};

bool Window::CreateWindow() noexcept
{
    return platformWindow->CreateWindow();
}

void Window::PollEvent() noexcept
{
    platformWindow->PollEvent();
}

void Window::SwapBackBuffer() const noexcept
{
    platformWindow->SwapBackBuffer();
}

bool Window::IsFullscreen() noexcept
{
    return platformWindow->IsFullscreen();
}

void Window::TurnOnMonitorVerticalSynchronization(bool enable) noexcept
{
    platformWindow->TurnOnMonitorVerticalSynchronization(enable);
}

void Window::ClearWindow() const noexcept
{
	platformWindow->ClearWindow();
}

bool Window::IsMonitorVerticalSynchronizationOn() noexcept
{
    return platformWindow->IsMonitorVerticalSynchronizationOn();
}

void Window::ToggleFullscreen() noexcept
{
    platformWindow->ToggleFullscreen();
}

 vector2 Window::WindowSize() noexcept
{
    return platformWindow->GetPlatformWindowSize();
}
