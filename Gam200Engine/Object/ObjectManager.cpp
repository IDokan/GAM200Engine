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
#include "ObjectManager.hpp"
#include "States/StateManager.hpp"
#include <iostream>

ObjectManager* ObjectManager::obj_manager = nullptr;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

ObjectManager& ObjectManager::GetObjectManager()
{
    static ObjectManager *obj_manager = new ObjectManager();
    return *obj_manager;
}

void ObjectManager::Init()
{
    objects.clear();
    delete_obj.clear();
}

void ObjectManager::Update(float dt)
{
    if (StateManager::GetStateManager()->is_restart) {
        
        delete_obj.clear();
        for (const auto &obj : objects) {
            for (const auto &comp : obj->GetComponentContainer()) 
            {
                comp->Update(dt);
            }
            if (obj->GetDead()) {
                delete_obj.push_back(obj);
            }
        }

        for (const auto &obj : delete_obj) {
            DeleteObject(obj);
        }
    }
    else {
        std::cout << "Object Manager is stopped!" << std::endl;
    }
}

void ObjectManager::Clear()
{
    objects.clear();
    delete_obj.clear();

    delete GetObjectManager();
    obj_manager = nullptr;
}

void ObjectManager::AddObject(Object * obj)
{
    //왜 괄호안에 Shared_ptr을 써야하는거지?
    objects.push_back(std::shared_ptr<Object>(obj));
}

void ObjectManager::DeleteObject(std::shared_ptr<Object> obj)
{
    const auto tmp = std::find(objects.begin(), objects.end(), obj);
    if (tmp == objects.end()) 
    {
        return;
    }
    objects.erase(tmp);
}

