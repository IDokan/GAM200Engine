/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Physics.cpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.15.2019

    Source file for Physics
******************************************************************************/

#include <Component/Component.hpp>
#include "Vector2.hpp"
#include "Physics.hpp"
#include "matrix3.hpp"

void Physics::Init(Object* obj)
{

}

void Physics::Update(float dt)
{
    matrix3 vel = MATRIX3::build_translation(velocity);
    matrix3 gra = MATRIX3::build_translation(gravity);
    matrix3 total = vel * gra;
    vector2 vectorTranslation = GetTranslation(total);
}

void Physics::Clear()
{

}

void Physics::SetVelocity(vector2 velocity)
{
    this->velocity = velocity;
}

void Physics::SetVelocity(float x, float y)
{
    this->velocity.x = x;
    this->velocity.y = y;
}

void Physics::SetGravity(vector2 gravity)
{
    this->gravity = gravity;
}

void Physics::SetGravity(float x, float y)
{
    this->gravity.x = x;
    this->gravity.y = y;
}

bool Physics::IsCollideWith(Object * object)
{
    return false;
}

vector2 Physics::GetTranslation(matrix3 matrix3)
{
    return vector2{ matrix3.column2.x, matrix3.column2.y };
}