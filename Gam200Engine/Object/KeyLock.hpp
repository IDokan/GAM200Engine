/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   KeyLock.hpp
Author
        Hyerin Jung : junghl0621@gmail.com

Creation Date
        2020.03.16

    Header file for the KeyLock.cpp
******************************************************************************/

#pragma once
#include  <Object/Object.hpp>
#include <Component/Sprite/Animation.hpp>
#include <Component/Physics.hpp>

class KeyLock : public Object
{
public:
    enum class Identifier
    {
        KEY_RED,
        KEY_YELLOW,
        LOCK_RED,
        LOCK_YELLOW,
        UNDEFINED,
    };
public:
    //constructor
    //KeyLock(Identifier keylock, );
    //destructor
    ~KeyLock();

    //Key

    //Lock

private:

};