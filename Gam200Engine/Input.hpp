/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Input.hpp
Author
    - jaemin.woo wjm9932@gmail.com

Creation Date: 08.06.2019

    Header file for the Input.cpp
******************************************************************************/
#pragma once
#include <bitset>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vector2.hpp"

class Input
{
public:
    void Init();
    void TriggeredReset();
    void SetKeyboardInput(int key, int action);
    void SetMousePos(float xPos, float yPos);
    void SetMouseButtonInput(int button, int action);
    void SetMouseWheel(double x, double y);

    bool IsKeyTriggered(int key);
    bool IsKeyPressed(int key);
    bool IsKeyReleased(int key);

    bool IsMouseButtonTriggered(int button);
    bool IsMouseButtonPressed(int button);
    bool IsMouseButtonReleased(int button);
    bool IsMouseDoubleClicked(int button);

    double MouseWheelScroll();

    Math::vector2 GetMousePos();


private:
    std::bitset<GLFW_KEY_LAST> keyTriggered;
    std::bitset<GLFW_KEY_LAST> keyPressed;
    std::bitset<GLFW_KEY_LAST> keyReleased;

    std::bitset<GLFW_MOUSE_BUTTON_LAST> mouseButtonTriggered;
    std::bitset<GLFW_MOUSE_BUTTON_LAST> mouseButtonPressed;
    std::bitset<GLFW_MOUSE_BUTTON_LAST> mouseButtonReleased;
    std::bitset<GLFW_MOUSE_BUTTON_LAST> mouseButtonDoubleClicked;

    Math::vector2 mousePosistion{};

    double xOffset;
    double yOffset;
};

extern Input input;