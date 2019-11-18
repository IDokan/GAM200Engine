/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringPhysics.hpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 11.04.2019

    Header file for StringPhysics
******************************************************************************/

#pragma once
#include "Component/Physics.hpp"
#include <vector>

class StringPhyscis : public Component
{
public:
    struct ObjectPoint
    {
        vector2 leftBottom{};
        vector2 rightBottom{};
        vector2 leftTop{};
        vector2 rightTop{};
    };

    virtual void Init() override;
    virtual void Update(float dt) override;
    virtual void Clear() override;

    StringPhyscis(Object* object);
    ~StringPhyscis();

    void IsBendPointInstantiated(vector2 point1, vector2 point2);
    void SetObjectPoint(Object* obj);
    void SetNormalVector(vector2 point1, vector2 point2);

private:
    //std::vector<vector2> vertex{};
    ObjectPoint objectPoint{};
    vector2 norVector{};
};
