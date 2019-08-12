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

    bool IsKeyTriggered(int key);
    bool IsKeyPressed(int key);
    bool IsKeyReleased(int key);

     vector2 GetMousePos();


private:
    std::bitset<GLFW_KEY_LAST> keyTriggered;
    std::bitset<GLFW_KEY_LAST> keyPressed;
    std::bitset<GLFW_KEY_LAST> keyReleased;

     vector2 mousePosistion{};

    double xOffeset = 0.0f;
    double yOffeset = 0.0f;
};

extern Input input;