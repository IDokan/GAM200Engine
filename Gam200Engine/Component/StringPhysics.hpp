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
#include "Component/Component.hpp"
#include "Object/Object.hpp"
#include "Object//Strings/String.hpp"
#include <vector>

class StringPhysics : public Component
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

    StringPhysics(Object* object, Object* player1, Object* player2);
    ~StringPhysics();

    bool IsBendPointInstantiated(vector2 point1, vector2 point2, int index, vector2 targetPoint) const;
    void SetObjectPoint(Object* obj);
    void SetNormalVector(vector2 point1, vector2 point2);


private:
	void InsertPoint();
	void DeletePoint();
private:
    ObjectPoint objectPoint{};
    vector2 norVector{};
    String* stringPhysicsOwner;
    Object* player1;
    Object* player2;
    unsigned int vertexSize;
    bool isDelete;

    int addCount;
    std::vector < std::pair<int, vector2>> vertexContainer{};
};
