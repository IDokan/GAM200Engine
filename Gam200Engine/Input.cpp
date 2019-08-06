/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Input.cpp
Author
    - jaemin.woo wjm9932@gmail.com

Creation Date: 08.06.2019

    Source file for getting keyboard input
******************************************************************************/
#include "Input.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Input input;

void Input::Init()
{
    keyPressed.reset();
    keyReleased.reset();
    keyTriggered.reset();
}

void Input::TriggeredReset()
{
    keyTriggered.reset();
}

void Input::SetKeyboardInput(int key, int action)
{
    switch (action)
    {
        case GLFW_PRESS:
        {
            keyPressed.set(key);
            keyTriggered.set(key);
            keyReleased.reset(key);
            break;
        }
        case GLFW_RELEASE:
        {
            keyPressed.reset(key);
            keyTriggered.reset(key);
            keyReleased.set(key);
            break;
        }
    }
}

bool Input::IsKeyTriggered(int key)
{
    return keyTriggered[key];
}

bool Input::IsKeyPressed(int key)
{
    return keyPressed[key];
}

bool Input::IsKeyReleased(int key)
{
    return keyReleased[key];
}
