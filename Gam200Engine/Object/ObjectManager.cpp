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
	layerContainer.clear();
}

void ObjectManager::Update(float dt)
{
	for (const auto & element : layerContainer)
	{
		element->Update(dt);
	}
}

void ObjectManager::Clear()
{
	for (const auto& element : layerContainer)
	{
		element->Clear();
	}
	layerContainer.clear();
}
void ObjectManager::AddLayer(LayerNames layerName)
{
	Layer* tmp = new Layer();
	tmp->Init();
	tmp->SetName(layerName);
	layerContainer.push_back(tmp);
}

Layer* ObjectManager::FindLayer(LayerNames name)
{
	const int size = layerContainer.size();
	for (int i = 0; i < size; ++i)
	{
		if (layerContainer.at(i)->GetName() == name)
		{
			return layerContainer.at(i);
		}
	}
	return nullptr;
}

