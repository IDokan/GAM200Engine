/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MenuObject.hpp
Author
        rtd99062@gmail.com
Creation Date: 05.11.2020

    Declaration for Menu Object
    Menu Object is an abstract object that is designed to be drived by Menu Object
******************************************************************************/
#include <Object/Menu/MenuObject.hpp>

MenuObject::~MenuObject()
{

}

MenuObject::MenuObject()
    :Object(), isLerpIn(false), isLerpOut(false), lerpTimer(0.f)
{
    SetObjectType(ObjectType::Menu);
}

MenuObject* MenuObject::Update(float dt)
{
    // Only update lerp when lerpTimer is valid
    if (lerpTimer >= 0.f && lerpTimer < 1.f)
    {
        lerpTimer += dt;
        // If isLerpOut is true,
        if (isLerpOut)
        {
            LerpOut(lerpTimer);
        }
        // In order to LerpIn, isLerpOut should be false, and isLerpIn is true
        else if (isLerpIn)
        {
            LerpIn(lerpTimer);
        }
    }

    // Else then, do an Update
    return MenuUpdate(dt);
}

void MenuObject::StartLerpIn()
{
    isLerpIn = true;
    isLerpOut = false;
    lerpTimer = 0.f;
}

void MenuObject::StartLerpOut()
{
    isLerpIn = false;
    isLerpOut = true;
    lerpTimer = 0.f;
}
