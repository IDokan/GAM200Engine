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

#include "Vector2.hpp"
#include <Component/Component.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include "matrix3.hpp"

Physics::Physics(Object * obj) : Component(obj) 
{
}

Physics::~Physics()
{
}

void Physics::Init()
{
    position = owner->GetTranslation();
}

void Physics::Update(float dt)
{
    matrix3 vel = MATRIX3::build_translation(velocity);
    matrix3 dir = MATRIX3::build_translation(direction);
    matrix3 gra = MATRIX3::build_translation(gravity);
    matrix3 total = vel * dir * gra;

    if (gravity.y >= -50.f && gravity.y != 0) // 종단속도
    {
        gravity.y += -dt * 10.f;
    }

    if (force.x != 0 || force.y != 0)
    {
        if (force.y <= 20.f)
        {
            force.y += 180*dt;
        }
    }
    vectorTranslation = GetTranslation(total);
    vectorTranslation += force;
    position = owner->GetTranslation();
    position = position + vectorTranslation;
    owner->SetTranslation(position);
}

void Physics::Clear()
{
}

void Physics::SetVelocity(vector2 vel)
{
    this->velocity = vel;
}

void Physics::SetVelocity(float x, float y)
{
    this->velocity.x = x;
    this->velocity.y = y;
}

void Physics::SetGravity(vector2 gra)
{
    this->gravity = gra;
}

void Physics::SetGravity(float x, float y)
{
    this->gravity.x = x;
    this->gravity.y = y;
}

bool Physics::IsCollideWith(Object * object)
{
    if (owner->GetObjectType() == object->GetObjectType())
    {
        if (owner->GetObjectType() == Object::ObjectType::RECTANGLE)
        {
            float objectLeft = object->GetTranslation().width - (object->GetScale().width / 2);
            float objectRight = object->GetTranslation().width + (object->GetScale().width / 2);
            float objectBottom = object->GetTranslation().height - (object->GetScale().height / 2);
            float objectTop = object->GetTranslation().height + (object->GetScale().height / 2);

            float ownerLeft = owner->GetTranslation().width - (owner->GetScale().width / 2);
            float ownerRight = owner->GetTranslation().width + (owner->GetScale().width / 2);
            float ownerBottom = owner->GetTranslation().height - (owner->GetScale().height / 2);
            float ownerTop = owner->GetTranslation().height + (owner->GetScale().height / 2);

            if (objectRight >= ownerLeft && objectLeft <= ownerRight && objectTop >= ownerBottom && objectBottom <= ownerTop)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (owner->GetObjectType() == Object::ObjectType::CIRCLE)
        {

        }
    }
   
}

void Physics::SetDirection(vector2 dir)
{
    this->direction = dir;
}

void Physics::SetDirection(float x, float y)
{
    direction.x = x;
    direction.y = y;
}

void Physics::AddForce(vector2 frc)
{
    force += frc;
}

void Physics::AddForce(float x, float y)
{
    force.x += x;
    force.y += y;
}

vector2 Physics::GetTranslation(matrix3 matrix3)
{
    return vector2{ matrix3.column2.x, matrix3.column2.y };
}