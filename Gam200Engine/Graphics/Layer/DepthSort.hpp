/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   DepthSort.hpp
Author
        junghl0621@gmail.com
Creation Date: 09.26.2019

    Header file for the DepthSort.cpp
******************************************************************************/

#pragma once
#include <vector>
#include "Object/Object.hpp"
#include "Graphics/Layer/Layer.hpp"

using namespace std;

bool Compare(Object x, Object y);
void SortingDepth(vector<Layer*>trunks);
