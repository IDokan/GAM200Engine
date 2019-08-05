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
