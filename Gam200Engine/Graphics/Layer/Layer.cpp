#include "Layer.hpp"

void Layer::Init()
{
	layer.second.clear();
	delete_obj.clear();
}

void Layer::Update(float dt)
{
	delete_obj.clear();

	for (const auto& obj : layer.second) {
		for (const auto& comp : obj->GetComponentContainer())
		{
			comp->Update(dt);
		}
		if (obj->GetDead()) {
			delete_obj.push_back(obj);
		}
	}

	for (const auto& obj : delete_obj) {
		DeleteObject(obj);
	}
}

void Layer::Clear()
{
	layer.second.clear();
	delete_obj.clear();
}

void Layer::AddObject(Object* obj)
{
	layer.second.push_back(std::shared_ptr<Object>(obj));
}

void Layer::DeleteObject(std::shared_ptr<Object> obj)
{
	const auto tmp = std::find(layer.second.begin(), layer.second.end(), obj);
	if (tmp == layer.second.end())
	{
		return;
	}
	layer.second.erase(tmp);
}

void Layer::SetName(const std::string name)
{
	layer.first = name;
}

const std::string& Layer::GetName() const
{
	return layer.first;
}

std::vector<std::shared_ptr<Object>>& Layer::GetObjContainer()
{
	return layer.second;
}


/*
 * brief
 * Hyerin Jung
 */
bool operator<(const std::shared_ptr<Object> &x, const std::shared_ptr<Object> &y)
{
    return (x->GetTransform().GetDepth() < y->GetTransform().GetDepth());
}

void Layer::SortingDepth(std::vector<std::shared_ptr<Object>> layer)
{
    sort(layer.begin(), layer.end());
}