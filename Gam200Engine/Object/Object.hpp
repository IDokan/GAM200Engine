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

    enum class ObjectType
    {
        PLAYER_1,
        PLAYER_2,
        OBSTACLE,
        STRING,
    };

    void SetDead(bool condition) 
    {
        is_dead = condition;
    }
    bool GetDead()const
    {
        return is_dead;
    }

    Transform GetTransform() const
    {
        return transform;
    }

    std::vector<Component*> GetComponentContainer() 
    {
        return component;
    }
    template <typename COMPONENT>
    COMPONENT* GetComponentByTemplate()const;

    ObjectType GetObjectType() const // test fuction for Woo
    {
        return objType;
    }

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

    void SetObjectType(ObjectType objType); // test function Woo
    
    vector2 GetTranslation(); // Woo
    vector2 GetScale(); // Woo
	float GetRotation() const noexcept; // Sinil

protected:
    Transform transform;
    std::vector<Component*> component;
    std::string objectName;
    bool is_dead = false;
    ObjectType objType; // test variable Woo
};

template <typename COMPONENT>
COMPONENT* Object::GetComponentByTemplate() const
{
    for (const auto& i : component)
    {
		COMPONENT* iterator = dynamic_cast<COMPONENT*>(i);
		if (iterator != nullptr)
		{
			if (typeid(COMPONENT*) == typeid(iterator))
			{
				return iterator;
			}
		}
    }
    return nullptr;
}