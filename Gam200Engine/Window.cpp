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
#include "Window.hpp"
#include "PlatformWindow.hpp"

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


void Window::ToggleFullscreen() noexcept
{
    platformWindow->ToggleFullscreen();
}

Math::vector2 Window::WindowSize() noexcept
{
    return platformWindow->GetPlatformWindowSize();
}
