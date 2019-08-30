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
#include <cmath>

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
            force.y += 5+dt;
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
            float objectLeft = object->GetTranslation().x - (object->GetScale().width / 2);
            float objectRight = object->GetTranslation().x + (object->GetScale().width / 2);
            float objectBottom = object->GetTranslation().y - (object->GetScale().height / 2);
            float objectTop = object->GetTranslation().y + (object->GetScale().height / 2);

            float ownerLeft = owner->GetTranslation().x - (owner->GetScale().width / 2);
            float ownerRight = owner->GetTranslation().x + (owner->GetScale().width / 2);
            float ownerBottom = owner->GetTranslation().y - (owner->GetScale().height / 2);
            float ownerTop = owner->GetTranslation().y + (owner->GetScale().height / 2);

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
            float xDistance = object->GetTranslation().x - owner->GetTranslation().x;
            float yDistance = object->GetTranslation().y - owner->GetTranslation().y;
            float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

            if (distance < (object->GetScale().x / 2) + (owner->GetScale().x / 2))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        if (owner->GetObjectType() == Object::ObjectType::RECTANGLE)
        {
            float rectangleLeft = owner->GetTranslation().x - (owner->GetScale().width / 2);
            float rectangleRight = owner->GetTranslation().x + (owner->GetScale().width / 2);
            float rectangleBottom = owner->GetTranslation().y - (owner->GetScale().height / 2);
            float rectangleTop = owner->GetTranslation().y + (owner->GetScale().height / 2);
            float circleX = object->GetTranslation().x;
            float circleY = object->GetTranslation().y;
            float circleRadius = object->GetScale().x / 2;

            if (circleX >= rectangleLeft && circleX <= rectangleRight && circleY >= rectangleBottom && circleY <= rectangleTop)
            {
                return true;
            }
            else if (circleX <= rectangleLeft)
            {
                if (circleY <= rectangleTop && circleY >= rectangleBottom)
                {
                    float distance = std::abs(circleX - rectangleLeft);
                   
                    return distance <= circleRadius ? true : false;
                }
                else if (circleY >= rectangleTop)
                {
                    float xDistance = circleX - rectangleLeft;
                    float yDistance = circleY - rectangleTop;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
                    
                    return distance <= circleRadius ? true : false;
                }
                else if (circleY <= rectangleBottom)
                {
                    float xDistance = circleX - rectangleLeft;
                    float yDistance = circleY - rectangleBottom;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
                    
                    return distance <= circleRadius ? true : false;
                }
            }
            else if (circleY >= rectangleTop)
            {
                if (circleX >= rectangleLeft && circleX <= rectangleRight)
                {
                    float distance = std::abs(circleY - rectangleTop);
                   
                    return distance <= circleRadius ? true : false;
                }
                else if (circleX <= rectangleLeft)
                {
                    float xDistance = circleX - rectangleLeft;
                    float yDistance = circleY - rectangleTop;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
                    
                    return distance <= circleRadius ? true : false;
                }
                else if (circleX >= rectangleRight)
                {
                    float xDistance = circleX - rectangleRight;
                    float yDistance = circleY - rectangleTop;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
                    
                    return distance <= circleRadius ? true : false;
                }
            }
            else if (circleX >= rectangleRight)
            {
                if (circleY >= rectangleBottom && circleY <= rectangleTop)
                {
                    float distance = std::abs(circleX - rectangleRight);
                    
                    return distance <= circleRadius ?  true :  false;
                }
                else if (circleY <= rectangleBottom)
                {
                    float xDistance = circleX - rectangleRight;
                    float yDistance = circleY - rectangleBottom;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
                    
                    return distance <= circleRadius ? true : false;
                }
                else if (circleY >= rectangleTop)
                {
                    float xDistance = circleX - rectangleRight;
                    float yDistance = circleY - rectangleTop;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
                    
                    return distance <= circleRadius ? true : false;
                }
            }
            else if (circleY <= rectangleBottom)
            {
                if (circleX >= rectangleLeft && circleX <= rectangleRight)
                {
                    float distance = std::abs(circleY - rectangleBottom);

                    return distance <= circleRadius ? true : false;
                }
                else if (circleX <= rectangleLeft)
                {
                    float xDistance = circleX - rectangleLeft;
                    float yDistance = circleY - rectangleBottom;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true: false;
                }
                else if (circleX >= rectangleRight)
                {
                    float xDistance = circleX - rectangleRight;
                    float yDistance = circleY - rectangleBottom;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true : false;
                }
            }
        }
        if (owner->GetObjectType() == Object::ObjectType::CIRCLE)
        {
            float rectangleLeft = object->GetTranslation().x - (owner->GetScale().width / 2);
            float rectangleRight = object->GetTranslation().x + (owner->GetScale().width / 2);
            float rectangleBottom = object->GetTranslation().y - (owner->GetScale().height / 2);
            float rectangleTop = object->GetTranslation().y + (owner->GetScale().height / 2);
            float circleX = owner->GetTranslation().x;
            float circleY = owner->GetTranslation().y;
            float circleRadius = owner->GetScale().x / 2;
           
            if (circleX >= rectangleLeft && circleX <= rectangleRight && circleY >= rectangleBottom && circleY <= rectangleTop)
            {
                return true;
            }
            else if (circleX <= rectangleLeft)
            {
                if (circleY <= rectangleTop && circleY >= rectangleBottom)
                {
                    float distance = std::abs(circleX - rectangleLeft);

                    return distance <= circleRadius ? true : false;
                }
                else if (circleY >= rectangleTop)
                {
                    float xDistance = circleX - rectangleLeft;
                    float yDistance = circleY - rectangleTop;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true : false;
                }
                else if (circleY <= rectangleBottom)
                {
                    float xDistance = circleX - rectangleLeft;
                    float yDistance = circleY - rectangleBottom;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true : false;
                }
            }
            else if (circleY >= rectangleTop)
            {
                if (circleX >= rectangleLeft && circleX <= rectangleRight)
                {
                    float distance = std::abs(circleY - rectangleTop);

                    return distance <= circleRadius ? true : false;
                }
                else if (circleX <= rectangleLeft)
                {
                    float xDistance = circleX - rectangleLeft;
                    float yDistance = circleY - rectangleTop;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true : false;
                }
                else if (circleX >= rectangleRight)
                {
                    float xDistance = circleX - rectangleRight;
                    float yDistance = circleY - rectangleTop;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true : false;
                }
            }
            else if (circleX >= rectangleRight)
            {
                if (circleY >= rectangleBottom && circleY <= rectangleTop)
                {
                    float distance = std::abs(circleX - rectangleRight);

                    return distance <= circleRadius ? true : false;
                }
                else if (circleY <= rectangleBottom)
                {
                    float xDistance = circleX - rectangleRight;
                    float yDistance = circleY - rectangleBottom;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true : false;
                }
                else if (circleY >= rectangleTop)
                {
                    float xDistance = circleX - rectangleRight;
                    float yDistance = circleY - rectangleTop;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true : false;
                }
            }
            else if (circleY <= rectangleBottom)
            {
                if (circleX >= rectangleLeft && circleX <= rectangleRight)
                {
                    float distance = std::abs(circleY - rectangleBottom);

                    return distance <= circleRadius ? true : false;
                }
                else if (circleX <= rectangleLeft)
                {
                    float xDistance = circleX - rectangleLeft;
                    float yDistance = circleY - rectangleBottom;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true : false;
                }
                else if (circleX >= rectangleRight)
                {
                    float xDistance = circleX - rectangleRight;
                    float yDistance = circleY - rectangleBottom;
                    float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                    return distance <= circleRadius ? true : false;
                }
            }
        }
    }
    return false;
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