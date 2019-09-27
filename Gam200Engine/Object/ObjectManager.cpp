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
#include "Graphics/Layer/Layer.hpp"

ObjectManager::~ObjectManager()
{
}

ObjectManager* ObjectManager::GetObjectManager()
{
    static ObjectManager *obj_manager = new ObjectManager();
    return obj_manager;
}

void ObjectManager::Init()
{
	trunks.clear();
}

void ObjectManager::Update(float dt)
{
	for (const auto & element : trunks)
	{
		element->Update(dt);
	}
}

void ObjectManager::Clear()
{
	for (const auto& element : trunks)
	{
		element->Clear();
	}
	trunks.clear();
}
void ObjectManager::AddLayer(const std::string & layerName)
{
	Layer* tmp = new Layer();
	tmp->Init();
	tmp->SetName(layerName);
	trunks.push_back(tmp);
}

Layer* ObjectManager::FindLayer(const std::string & name)
{
	const int size = trunks.size();
	for (int i = 0; i < size; ++i)
	{
		if (trunks.at(i)->GetName() == name)
		{
			return trunks.at(i);
		}
	}
	return nullptr;
}

