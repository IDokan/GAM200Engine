/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MenuObject.hpp
Author
        rtd99062@gmail.com
Creation Date: 05.11.2020

    Header file for the MenuObject.cpp
******************************************************************************/
#pragma once
#include <Object/Object.hpp>


class MenuObject : public Object
{
public:
    virtual ~MenuObject();
    MenuObject();

public:
    // Return value is various
        // nullptr -> Pop once
        // ptr to this -> Do nothing
        // ptr to other menu object -> push the ptr to stack
    virtual MenuObject* MenuUpdate(float dt) = 0;
    virtual void AddChildObjectsDynamically() = 0;
    virtual void CleanChildObjects() = 0;

protected:

};