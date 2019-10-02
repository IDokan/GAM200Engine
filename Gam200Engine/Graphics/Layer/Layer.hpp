#pragma once
#include <algorithm>    //sorting
#include <vector>
#include <string>
#include <memory>
#include <Object/Object.hpp>

class Layer
{
public:
	void Init();
	void Update(float dt);
	void Clear();

	
	void AddObject(Object* obj);
	void DeleteObject(std::shared_ptr<Object> obj);

	void SetName(const std::string name);
	[[nodiscard]] const std::string& GetName() const;

	std::vector<std::shared_ptr<Object>> & GetObjContainer();
    void SortingDepth();

private:
	std::pair<std::string, std::vector<std::shared_ptr<Object>>> layer;

	std::vector<std::shared_ptr<Object>>delete_obj{};
};

