/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Window.hpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Header file for the Window.cpp
******************************************************************************/
#pragma once
#include <memory>
#include "Vector2.hpp"

class PlatformWindow;

class Window
{
public:
    Window() noexcept;
    ~Window() noexcept;
    
    bool CreateWindow() noexcept;
    void PollEvent() noexcept;
    void SwapBackBuffer() const noexcept;
    void ToggleFullscreen() noexcept;
    bool IsFullscreen() noexcept;
     vector2 WindowSize() noexcept;
    bool IsMonitorVerticalSynchronizationOn() noexcept;
    void TurnOnMonitorVerticalSynchronization(bool enable) noexcept;
	void ClearWindow() const noexcept;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

private:
    std::unique_ptr<PlatformWindow> platformWindow{};
};