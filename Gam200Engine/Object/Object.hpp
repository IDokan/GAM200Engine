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
        Default,
		// Below 2 object types are for Player class
		// Location: <Object/Players/Player.h>
        PLAYER_1,
        PLAYER_2,
        /*  For collision check
            Physics.cpp*/
        OBSTACLE,
        KEY_1,
        KEY_2,
        LOCK_1,
        LOCK_2,
        /*  For moving object
            Physics.cpp
        */
        MOVING_OBJECT,
        /*For button*/\
        BUTTON,
        /*For door*/
        DOOR,
        JAIL,
        SavedCheese,
    	TEST,
		// This is type to designate for String Object
		// Location: <Object/Strings/String.hpp>
        STRING,
		// Only Scene state manager can hold this type
		// Location: <Object/SceneStateManager>
		SCENE_STATE_MANAGER,
        // All UI object have this type.
        UI,
        // The object that derived by MenuObject should be declared this type.
        // Location: <Object/Menu/>
        Menu,
		NUM_OF_OBJECT_TYPE,
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

    Transform& GetTransform()
    {
        return transform;
    }

    std::vector<Component*> GetComponentContainer() 
    {
        return component;
    }
    template <typename COMPONENT>
    COMPONENT* GetComponentByTemplate()const;

    [[nodiscard]] ObjectType GetObjectType() const // test fuction for Woo
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
    void SetDirtyFlag(bool flag);
    void SetTimer(float dt);
    void SetIsTimerOn(bool flag);
    void ResetTimer(float time);

    void SetObjectType(ObjectType objType); // test function Woo

    [[nodiscard]] std::string GetStringOfObjectType() const noexcept;
    
    vector2 GetTranslation() const noexcept; // Woo
    vector2 GetScale() const noexcept; // Woo
	float GetRotation() const noexcept; // Sinil
	float GetDepth() const noexcept; //Jiwon
    bool GetDirtyFlag() const;
    bool GetIsTImerOn() const;
    float GetTimer() const;

protected:
    Transform transform;
    std::vector<Component*> component;
    std::string objectName;
    bool is_dead = false;

    bool dirtyFlagForDoor = true;
    bool isTimerOn = false;
    float timer = 0.f;
    ObjectType objType;

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
	//throw "There is nothing to get component!";
}