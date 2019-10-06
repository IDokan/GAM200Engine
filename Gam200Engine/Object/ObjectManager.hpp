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
#include <vector>
#include "Object.hpp"
#include <memory>
#include <unordered_map>
#include <string>
#include <Graphics/Parallax scrolling/Layer.hpp>

class ObjectManager
{
public:
    ~ObjectManager();

    static ObjectManager* GetObjectManager();

    void Init();
    void Update(float dt);
    void Clear();

	// I don't know it will be deleted.
	// Temporary, commented it out.
    std::vector<Layer*>& GetLayerContainer() { return layerContainer; }

	// return nullptr, when finding layer is failed.
	Layer* FindLayer(LayerNames name);
private:
    ObjectManager() {};
	void AddLayer();

	std::vector<Layer*> layerContainer{};
};
