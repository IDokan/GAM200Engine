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

Object::Object()
{
}


Object::~Object()
{
	for (auto& comp : component)
	{
		delete comp;
	}
}

void Object::AddComponent(Component * comp)
{
    comp->Init();
    component.push_back(comp);
}

void Object::DeleteComponent(Component * comp)
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

void Object::SetDepth(float depth)
{
    transform.SetDepth(depth);
}

void Object::SetObjectName(std::string name)
{
    objectName = name;
}

std::string Object::GetObjectName()
{
    return objectName;
}

vector2 Object::GetTranslation()
{
    return transform.GetTranslation();
}

vector2 Object::GetScale()
{
    return transform.GetScale();
}
