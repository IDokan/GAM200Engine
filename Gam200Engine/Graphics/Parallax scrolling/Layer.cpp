/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Layer.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 10.02.2019

	Source file for Layer to Implement Parallax scrolling
******************************************************************************/

#include <algorithm>
#include "Layer.hpp"

void Layer::Init()
{
	layer.second.clear();
	delete_obj.clear();
}

void Layer::Update(float dt)
{
	delete_obj.clear();

	auto& vector = layer.second;
	for (const auto& obj : willBeAdded.second)
	{
		vector.push_back(obj);
	}
	willBeAdded.second.clear();

	for (const auto& obj : layer.second) {
		if (obj->GetDead()) {
			delete_obj.push_back(obj);
			continue;
		}
		for (const auto& comp : obj->GetComponentContainer())
		{
			comp->Update(dt);
		}
	}

	for (const auto& obj : delete_obj) {
		DeleteObject(obj.get());
	}
}

void Layer::Clear()
{
	layer.second.clear();
	delete_obj.clear();
}

void Layer::AddObjectDynamically(Object* obj)
{
	willBeAdded.second.push_back(std::shared_ptr<Object>(obj));
}

void Layer::AddObject(Object* obj)
{
	layer.second.push_back(std::shared_ptr<Object>(obj));
}


bool Layer::DeleteObject(Object* obj)
{
	size_t index = 0;
	for (auto iterator = layer.second.begin(); iterator < layer.second.end(); ++iterator)
	{
		if (layer.second.at(index).get() == obj)
		{
			layer.second.erase(iterator);
			return true;
		}
		++index;
	}
	return false;
}

bool Layer::DeleteObject(std::string objName)
{
	size_t index = 0;
	for (auto iterator = layer.second.begin(); iterator < layer.second.end(); ++iterator)
	{
		if (layer.second.at(index)->GetObjectName() == objName)
		{
			layer.second.erase(iterator);
			return true;
		}
		++index;
	}
	return false;
}

void Layer::SetName(LayerNames name)
{
	layer.first = name;
}

LayerNames Layer::GetName() const
{
	return layer.first;
}

std::string Layer::GetNameAsString() const
{
	std::string result;
	switch (layer.first)
	{
	case BackGround:
		result = "BackGround";
		break;
	case Stage:
		result = "Stage";
		break;
	case HUD:
		result = "HUD";
		break;
	case NumOfLayers:
    default:
        result = "Error";
	}
	return result;
}

std::vector<std::shared_ptr<Object>>& Layer::GetObjContainer()
{
	return layer.second;
}



/**
 * \brief implemented by Hyerin Jung
 * \return
 */
bool operator<(const std::shared_ptr<Object>& x, const std::shared_ptr<Object>& y)
{
	return (x->GetDepth() > y->GetDepth());
}
void Layer::SortingDepth()
{
	std::sort(layer.second.begin(), layer.second.end());
}