/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   DepthSort.cpp
Author
        junghl0621@gmail.com
Creation Date: 09.26.2019

    Sorting the layer with Depth.
******************************************************************************/
#include <algorithm>
#include "DepthSort.hpp"

//to use sort() function
//template <typename T>
//void sort(T start, T end);
//template <typename T>
//void sort(T start, T end, greater<T>());

bool Compare(Object x, Object y)
{
    if (x.GetTransform().GetDepth() == y.GetTransform().GetDepth())
    {
        return x.GetObjectName() < y.GetObjectName();
    }
    else
    {
        return x.GetTransform().GetDepth() < y.GetTransform().GetDepth();
    }
}

void SortingDepth(vector<Layer*> trunks)
{
    sort(trunks.begin(), trunks.end(), Compare);
}
