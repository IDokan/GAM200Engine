/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Header file for the Application.cpp
******************************************************************************/
#pragma once
#include "Window.hpp"
#include <States/TestLevel.hpp>
#include <States/ProtoLevel.hpp>
#include <Graphics/Color4f.hpp>

class Application
{
public:
    static Application* GetApplication();
    void Init();
    void Update(float dt);
    void Clear();
    void InputTest();
    void Input();
     vector2 GetWindowSize;

private:
    Application() = default;
    float fpsEllapsedTime = 0.f;
    int fpsFrames = 0;
    Window window;

	TestLevel testLevel;
    ProtoLevel protoLevel;

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	Graphics::Color4f clear_color = Graphics::Color4f{ 0.45f, 0.55f, 0.60f, 1.00f };

};