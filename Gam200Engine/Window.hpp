#pragma once
#include <memory>

class PlatformWindow;

class Window
{
public:
    Window() noexcept;
    ~Window() noexcept;
    
    bool CreateWindow() noexcept;
    void PollEvent() noexcept;
    void SwapBackBuffer() const noexcept;

private:
    std::unique_ptr<PlatformWindow> platformWindow{};
};