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
#include <map>

struct CollsionBox
{
    vector2 Translation{};
    vector2 Scale{};
    vector2 TranslationAmount{};
};

class Object
{
public:
    virtual ~Object();
    Object();

public:
    enum  class ObjectType
    {
        CIRCLE,
        RECTANGLE,
    };
    ObjectType GetObjectType() //Woo
    {
        return objectType;
    }
    void SetDead(bool condition) 
    {
        is_dead = condition;
    }
    bool GetDead()const
    {
        return is_dead;
    }
    bool GetHasCollisionBox() const
    {
        return hasCollisionBox;
    }
    Transform GetTransform() const
    {
        return transform;
    }
    CollsionBox GetCollisionBox() const
    {
        return collisionBox;
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
    void SetObjectName(std::string name); // Woo
    std::string GetObjectName(); // Woo

    void SetCollisionBoxAndObjectType(Object* object, ObjectType objType, vector2 positionAdj = vector2{0.f,0.f}, vector2 scaleAdj = vector2{ 0.f,0.f });
    void SetCollisionBoxAndObjectType(Object* object, ObjectType objType, float positionX, float positionY = 0.f, float scaleX = 0.f, float scaleY = 0.f);
    void SetCollisionBoxPosition(vector2 originPos);
    
    vector2 GetTranslation(); // Woo
    vector2 GetScale(); // Woo
	float GetRotation() const noexcept; // Sinil

private:
    Transform transform;
    std::vector<Component*> component;
    std::string objectName;
    ObjectType objectType;
    bool is_dead = false;
    bool hasCollisionBox = false;
    CollsionBox collisionBox{};
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