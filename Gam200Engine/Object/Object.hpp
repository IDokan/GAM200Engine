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
#pragma once
#include "Transform.hpp"
#include "Graphics/Mesh.hpp"
#include <vector>
#include "Component/Component.hpp"


class Object
{
public:
    virtual ~Object();
    Object();

public:
    void SetDead(bool condition) 
    {
        is_dead = condition;
    }
    bool GetDead()const
    {
        return is_dead;
    }
    Transform GetTransform() 
    {
        return transform;
    }
    std::vector<Component*> GetComponentContainer() 
    {
        return component;
    }

    template <typename COMPONENT>
    COMPONENT* GetComponentByTemplate()const;

public:
    virtual void AddComponent(Component* comp);
    virtual void DeleteComponent(Component* comp);

    void SetTranslation(vector2 pos);
    void SetRotation(float angle);
    void SetScale(vector2 scale);
    void SetScale(float scale);
    void SetDepth(float depth);

private:
    Transform transform;
    std::vector<Component*> component;
    bool is_dead = false;
};

template <typename COMPONENT>
COMPONENT* Object::GetComponentByTemplate() const
{
    for (const auto& i : component)
    {
        if (typeid(COMPONENT) == typeid(*i))
        {
            return dynamic_cast<COMPONENT*>(i);
        }
    }
    return nullptr;
}