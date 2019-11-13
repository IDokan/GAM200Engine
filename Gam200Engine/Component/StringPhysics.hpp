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

class StringPhyscis : public Physics
{
public:
    
    enum class Point
    {
        LeftBottom,
        RightBottom,
        LeftTop,
        RightTop,
        Default,
    };
    virtual void Init() override;
    virtual void Update(float dt) override;
    virtual void Clear() override;

    StringPhyscis(Object* object);
    StringPhyscis(Object* object, Object* player1, Object* player2);
    ~StringPhyscis();

    void SetStringPosition(vector2 pos);
    void StringCollision();
    void Iscollide(Object* object, Object* player2, Object* player1);
    void SetVertex(vector2 vertex);

private:
    bool IsBendPointInstantiated(vector2 norVector, vector2 point1, vector2 point2);
    
private:
    std::vector<vector2> manageVertex{};

    bool isFirst = true;
    bool isTest = true;

    Point point;

    Object* newPlayer1String;
    //Object* newPlayer2String;
    //ObjectManager* objManager = ObjectManager::GetObjectManager();
    Object* player1;
    Object* player2;
    vector2 position{};
    vector2 oldPosition{};

    vector2 objectLeftBottom;
    vector2 objectLeftTop;
    vector2 objectRightBottom;
    vector2 objectRightTop;
};
