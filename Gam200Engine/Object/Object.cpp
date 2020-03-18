/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
        dbsqhd106@gmail.com
Creation Date: 08.12.2019

    Header file for the Application.cpp
******************************************************************************/
#include "Object.hpp"
#include <iostream>

Object::Object() : objType()
{
}

Object::~Object()
{
    for (auto& comp : component)
    {
        delete comp;
    }
}

void Object::AddComponent(Component* comp)
{
    comp->Init();
    component.push_back(comp);
}

void Object::DeleteComponent(Component* comp)
{
    const auto tmp = std::find(component.begin(), component.end(), comp);
    if (tmp == component.end()) {
        return;
    }
    component.erase(tmp);
}

void Object::SetTranslation(vector2 pos)
{
    transform.SetTranslation(pos);
}

void Object::SetRotation(float angle)
{
    transform.SetRotation(angle);
}

void Object::SetScale(vector2 scale)
{
    transform.SetScale(scale);
}

void Object::SetScale(float scale)
{
    transform.SetScale(vector2{ scale });
}

// Depth value should be between [-5000, 5000).
void Object::SetDepth(float depth)
{
    transform.SetDepth(depth / 5000.f);
}

void Object::SetObjectName(std::string name)
{
    objectName = name;
}


std::string Object::GetObjectName()
{
    return objectName;
}

void Object::SetObjectType(ObjectType objType_)
{
    objType = objType_;
}

std::string Object::GetStringOfObjectType() const noexcept
{
    std::string result{};
    switch (objType) {
    case ObjectType::PLAYER_1:
        result = "PLAYER_1";
        break;
    case ObjectType::PLAYER_2:
        result = "PLAYER_2";
        break;
    case ObjectType::OBSTACLE:
        result = "OBSTACLE";
        break;
    case ObjectType::STRING:
        result = "STRING";
        break;
    default:
        result = "UNKNOWN";
    }
    return result;
}

vector2 Object::GetTranslation() const noexcept
{
    return transform.GetTranslation();
}

vector2 Object::GetScale() const noexcept
{
    return transform.GetScale();
}

float Object::GetRotation() const noexcept
{
    return transform.GetRotation();
}

float Object::GetDepth() const noexcept
{
    return transform.GetDepth() * 5000.f;
}
