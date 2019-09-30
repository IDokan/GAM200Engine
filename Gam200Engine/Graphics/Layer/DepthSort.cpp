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


//Error	C2664	'bool (Object,Object)': cannot convert argument 1 from 'std::shared_ptr<Object>' to 'Object'	

bool Compare( const shared_ptr<Object> &x, const shared_ptr<Object> &y)
{
    return (x->GetTransform().GetDepth() <= y->GetTransform().GetDepth());
}

//trunk 안의 layer를 불러와서 비교시키는 기능을 넣어야 함.
bool operator<(const shared_ptr<Object> &x, const shared_ptr<Object> &y)
{
    return (x->GetTransform().GetDepth() < y->GetTransform().GetDepth());
}

void SortingDepth(vector<shared_ptr<Object>> layer)
{
    //layer[0]->GetTransform().GetDepth();
    sort(layer.begin(), layer.end());
}