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
#include "Component/Component.hpp"
#include "Component/StringPhysics.hpp"
#include "Object/Strings/String.hpp"
#include "Component/Physics.hpp"
#include "Object/ObjectManager.hpp"
#include <vector>

StringPhysics::StringPhysics(Object* object, Object* player1, Object* player2) : Component(object) , stringPhysicsOwner(dynamic_cast<String*>(object)), player1(player1), player2(player2)
{
    
}


StringPhysics::~StringPhysics()
{
}

void StringPhysics::Init()
{
    addCount = 0;
}

void StringPhysics::Update(float dt)
{
    const auto& physicsObject = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
 
    vertexSize = stringPhysicsOwner->vertices.size(); // will be changed.
    for (auto i = 0; i < vertexSize - 1; i++)
    {
        SetNormalVector(stringPhysicsOwner->vertices.at(i), stringPhysicsOwner->vertices.at(i + 1));

        for (const auto& object : physicsObject)
        {
			
				if (object->GetComponentByTemplate<Physics>() != 0 && object->GetComponentByTemplate<Physics>()->GetHasCollisionBox() == true)
				{
					SetObjectPoint(&*object);
					IsBendPointInstantiated(stringPhysicsOwner->vertices.at(i), stringPhysicsOwner->vertices.at(i + 1), i + 1);
				}
	
        }
    }
    if (addCount !=0)
    {
        InsertPoint();
    }

    *stringPhysicsOwner->vertices.begin() = player1->GetTranslation();
    *(stringPhysicsOwner->vertices.end()-1) = player2->GetTranslation();
    addCount = 0;
}

void StringPhysics::IsBendPointInstantiated(vector2 point1, vector2 point2, int index)
{
    std::vector<vector2>::iterator begin = stringPhysicsOwner->vertices.begin();
    auto compare = norVector.x > norVector.y ? norVector.x : norVector.y;

    if (dot(norVector, objectPoint.leftBottom) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectPoint.leftBottom) - dot(norVector, point2) >= -abs(compare))
    {
        if (point1 != objectPoint.leftBottom && point2 != objectPoint.leftBottom)
        {
            vertexContainer.push_back(std::pair(index, objectPoint.leftBottom));
            addCount++;
        }
    }
    if (dot(norVector, objectPoint.leftTop) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectPoint.leftTop) - dot(norVector, point2) >= -abs(compare))
    {
        if (point1 != objectPoint.leftTop && point2 != objectPoint.leftTop)
        {
            vertexContainer.push_back(std::pair(index, objectPoint.leftTop));
            addCount++;
        }
    }
    if (dot(norVector, objectPoint.rightBottom) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectPoint.rightBottom) - dot(norVector, point2) >= -abs(compare))
    {
        if (point1 != objectPoint.rightBottom && point2 != objectPoint.rightBottom)
        {
            vertexContainer.push_back(std::pair(index, objectPoint.rightBottom));
            addCount++;
        }
    }
    if (dot(norVector, objectPoint.rightTop) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectPoint.rightTop) - dot(norVector, point2) >= -abs(compare))
    {
        if (point1 != objectPoint.rightTop && point2 != objectPoint.rightTop)
        {
            vertexContainer.push_back(std::pair(index,objectPoint.rightTop));
            addCount++;
        }
    }
}

void StringPhysics::SetObjectPoint(Object* obj)
{
    auto objectCollisionBox = obj->GetComponentByTemplate<Physics>()->GetCollisionBox();

    objectPoint.leftBottom = vector2{ objectCollisionBox.Translation.x - objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.x - objectCollisionBox.Scale.y / 2};
    objectPoint.leftTop = vector2{ objectCollisionBox.Translation.x - objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.x + objectCollisionBox.Scale.y / 2};
    objectPoint.rightBottom = vector2{ objectCollisionBox.Translation.x + objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.x - objectCollisionBox.Scale.y / 2};
    objectPoint.rightTop = vector2{ objectCollisionBox.Translation.x + objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.x + objectCollisionBox.Scale.y / 2};
}

void StringPhysics::SetNormalVector(vector2 point1, vector2 point2)
{
    norVector = { point1.x - point2.x, point1.y - point2.y };
    norVector = { norVector.x, -norVector.y };
}

void StringPhysics::InsertPoint()
{
    for (int i = 0; i < addCount; i++)
    {
        std::vector<vector2>::iterator begin = stringPhysicsOwner->vertices.begin();
        stringPhysicsOwner->vertices.insert(begin + vertexContainer.at(i).first, vertexContainer.at(i).second);
    }
    vertexContainer.clear();
    vertexSize = stringPhysicsOwner->vertices.size();
}

void StringPhysics::Clear()
{

}

