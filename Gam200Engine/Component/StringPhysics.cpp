/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringPhysics.cpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 11.04.2019

    Source file for StringPhysics
******************************************************************************/
#include <iostream>
#include "Component/Component.hpp"
#include "Component/StringPhysics.hpp"
#include "Object/ObjectManager.hpp"
#include "Component/Sprite.hpp"

StringPhyscis::StringPhyscis(Object* object) : Component(object)
{
}

StringPhyscis::~StringPhyscis()
{
}

void StringPhyscis::Init()
{

}

void StringPhyscis::Update(float dt)
{

}


void StringPhyscis::IsBendPointInstantiated(vector2 point1, vector2 point2)
{
    auto compare = norVector.x > norVector.y ? norVector.x : norVector.y;

    if (dot(norVector, objectPoint.leftBottom) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectPoint.leftBottom) - dot(norVector, point2) >= -abs(compare))
    {
    }
    if (dot(norVector, objectPoint.leftTop) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectPoint.leftTop) - dot(norVector, point2) >= -abs(compare))
    {

    }
    if (dot(norVector, objectPoint.rightBottom) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectPoint.rightBottom) - dot(norVector, point2) >= -abs(compare))
    {

    }
    if (dot(norVector, objectPoint.rightTop) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectPoint.rightTop) - dot(norVector, point2) >= -abs(compare))
    {
    }
}

void StringPhyscis::SetObjectPoint(Object* obj)
{
    auto objectCollisionBox = obj->GetComponentByTemplate<Physics>()->GetCollisionBox();

    objectPoint.leftBottom = vector2{ objectCollisionBox.Translation.x - objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.x - objectCollisionBox.Scale.y / 2};
    objectPoint.leftTop = vector2{ objectCollisionBox.Translation.x - objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.x + objectCollisionBox.Scale.y / 2};
    objectPoint.rightBottom = vector2{ objectCollisionBox.Translation.x + objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.x - objectCollisionBox.Scale.y / 2};
    objectPoint.rightTop = vector2{ objectCollisionBox.Translation.x + objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.x + objectCollisionBox.Scale.y / 2};
}

void StringPhyscis::SetNormalVector(vector2 point1, vector2 point2)
{
    norVector = { point1.x - point2.x, point1.y - point2.y };
    norVector = { norVector.x, -norVector.y };
}

void StringPhyscis::Clear()
{

}

