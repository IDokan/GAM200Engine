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
#include <Component/StringSprite.hpp>
#include <Object/InteractiveObject/InteractiveObject.hpp>

StringPhysics::StringPhysics(Object* object, Object* player1, Object* player2) : Component(object), stringPhysicsOwner(dynamic_cast<String*>(object)), player1(player1), player2(player2)
{

}


StringPhysics::~StringPhysics()
{
}

void StringPhysics::Init()
{
}

void StringPhysics::Update(float /*dt*/)
{
    const auto& physicsObject = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();

    size_t vertexSize = stringPhysicsOwner->vertices.size(); // will be changed.

    // Add collided point
    for (size_t i = 0; i < vertexSize - 1; i++)
    {
        SetNormalVector(stringPhysicsOwner->vertices.at(i).position, stringPhysicsOwner->vertices.at(i + 1).position);

        for (const auto& object : physicsObject)
        {
            if (object->GetObjectType() == Object::ObjectType::PLAYER_1 || object->GetObjectType() == Object::ObjectType::PLAYER_2)
            {
                continue;
            }

            if (object->GetComponentByTemplate<Physics>() != 0 && object->GetComponentByTemplate<Physics>()->GetHasCollisionBox() == true)
            {
                const auto objectCollisionBox = object->GetComponentByTemplate<Physics>()->GetCollisionBox();
                vector2 stringVertex1 = stringPhysicsOwner->vertices.at(i).position;
                vector2 stringVertex2 = stringPhysicsOwner->vertices.at(i + 1).position;

                vector2 center{ objectCollisionBox.Translation.x, objectCollisionBox.Translation.y };

                InteractiveObject* interactiveObject = dynamic_cast<InteractiveObject*>(object.get());
                // Left-Bottom
                PushbackIfBended(stringVertex1, stringVertex2, i + 1,
                    center + vector2{ -objectCollisionBox.Scale.x / 2,  -objectCollisionBox.Scale.y / 2 }, center, interactiveObject);
                // Left-Top
                PushbackIfBended(stringVertex1, stringVertex2, i + 1,
                    center + vector2{ -objectCollisionBox.Scale.x / 2, +objectCollisionBox.Scale.y / 2 }, center, interactiveObject);
                // Right-Bottom
                PushbackIfBended(stringVertex1, stringVertex2, i + 1,
                    center + vector2{ +objectCollisionBox.Scale.x / 2, -objectCollisionBox.Scale.y / 2 }, center, interactiveObject);
                // Right-Top
                PushbackIfBended(stringVertex1, stringVertex2, i + 1,
                    center + vector2{ +objectCollisionBox.Scale.x / 2, +objectCollisionBox.Scale.y / 2 }, center, interactiveObject);
            }
        }
    }
    if (vertexContainer.empty() == false)
    {
        InsertPoint();
    }
    DeleteVerticesInContainer();

    *stringPhysicsOwner->vertices.begin() = player1->GetTranslation();
    *(stringPhysicsOwner->vertices.end() - 1) = player2->GetTranslation();


    Detach();
}

bool StringPhysics::IsBendPointInstantiated(vector2 point1, vector2 point2, vector2 targetPoint) const
{
    const auto compare = 2 * (abs(norVector.x) > abs(norVector.y) ? abs(norVector.x) : abs(norVector.y));

    vector2 RP{ targetPoint - point1 };
    vector2 QP{ point2 - point1 };

    // Check target point is between the edge. 
    if (!(0 < dot(RP, QP) && dot(RP, QP) < dot(QP, QP)))
    {
        return false;
    }
    const float resultWithTarget = dot(norVector, targetPoint);
    const float resultWithPointOnLine = dot(norVector, point1);
    const float collisionResult = resultWithTarget - resultWithPointOnLine;
    if (collisionResult <= compare
        && collisionResult >= -compare)
    {
        if (point1 != targetPoint && point2 != targetPoint)
        {
            return true;
        }
    }
    return false;
}

void StringPhysics::SetNormalVector(vector2 point1, vector2 point2)
{
    norVector = { point1.x - point2.x, point1.y - point2.y };
    norVector = { norVector.y, -norVector.x };
}

void StringPhysics::DeletePositionsWithObject(Object* obj)
{
    // Iteration to find what vertices' attached object is same with given object pointer
    std::for_each(std::begin(stringPhysicsOwner->vertices), std::end(stringPhysicsOwner->vertices),
        [&](const StringVertex& vertex) mutable
    {
        if (vertex.attachedObject == obj)
        {
            deletedVertices.emplace_back(vertex);
        }
    });
}

void StringPhysics::DeleteVerticesInContainer()
{
    // Based on saved string vertex, find it in vertices and erase it!
    std::for_each(std::begin(deletedVertices), std::end(deletedVertices),
        [&](const StringVertex& vertex) mutable
    {
        if (const auto& it = std::find(std::begin(stringPhysicsOwner->vertices), std::end(stringPhysicsOwner->vertices), vertex);
            it != stringPhysicsOwner->vertices.end())
        {
            stringPhysicsOwner->vertices.erase(it);
        }
    });

}

void StringPhysics::Detach()
{
    const size_t vertices_size = stringPhysicsOwner->vertices.size();
    if (vertices_size < 3)
    {
        return;
    }
    if (IsDetached(stringPhysicsOwner->vertices.at(vertices_size - 3), stringPhysicsOwner->vertices.back(), stringPhysicsOwner->vertices.at(vertices_size - 2)))
    {
        std::swap(stringPhysicsOwner->vertices.at(vertices_size - 2), stringPhysicsOwner->vertices.back());
        if (InteractiveObject* obj = dynamic_cast<InteractiveObject*>(stringPhysicsOwner->vertices.back().attachedObject);
            obj != nullptr)
        {
            obj->Detached();
        }
        stringPhysicsOwner->vertices.pop_back();
    }

    if (stringPhysicsOwner->vertices.size() < 3)
    {
        return;
    }

    if (IsDetached(stringPhysicsOwner->vertices.front(), stringPhysicsOwner->vertices.at(2), stringPhysicsOwner->vertices.at(1)))
    {
        std::swap(stringPhysicsOwner->vertices.front(), stringPhysicsOwner->vertices.at(1));
        if (InteractiveObject* obj = dynamic_cast<InteractiveObject*>(stringPhysicsOwner->vertices.front().attachedObject);
            obj != nullptr)
        {
            obj->Detached();
        }
        stringPhysicsOwner->vertices.pop_front();
    }
}

void StringPhysics::InsertPoint()
{
    size_t verticesSize = vertexContainer.size();
    for (size_t i = 0; i < verticesSize; i++)
    {
        const auto& begin = stringPhysicsOwner->vertices.begin();
        stringPhysicsOwner->vertices.insert(begin + vertexContainer.at(i).first, vertexContainer.at(i).second);
    }
    vertexContainer.clear();
}

void StringPhysics::DeletePoint()
{
    for (const auto& elem : vertexContainer)
    {
        const auto it = std::find(std::begin(stringPhysicsOwner->vertices), std::end(stringPhysicsOwner->vertices), elem.second);
        stringPhysicsOwner->vertices.erase(it);
    }
    vertexContainer.clear();
}

void StringPhysics::PushbackIfBended(vector2 point1, vector2 point2, size_t index, vector2 targetPoint, vector2 centerPosition, InteractiveObject* objPtr)
{
    if (IsBendPointInstantiated(point1, point2, targetPoint))
    {
        if (objPtr != nullptr)
        {
            objPtr->Attached();
        }
        vertexContainer.emplace_back(std::pair(index, StringVertex{ targetPoint, centerPosition, objPtr }));
    }
}

/*
 *    https://bowbowbow.tistory.com/14
 *    The Key Point is
 *    We can get an sign of angle between two vector via 2 dimensional cross product
*/
bool StringPhysics::IsDetached(StringVertex point1, StringVertex point2, StringVertex targetPoint) const
{
    vector2 ToTargetPosition{ targetPoint.position - point1.position };
    vector2 ToCenter{ targetPoint.centerPositionOfCollidedObject - point1.position };
    vector2 ToNextVertex{ point2.position - point1.position };

    if (cross(ToTargetPosition, ToCenter) > 0)
    {
        return cross(ToTargetPosition, ToNextVertex) < 0;
    }
    else if (cross(ToTargetPosition, ToCenter) < 0)
    {
        return cross(ToTargetPosition, ToNextVertex) > 0;
    }
    else
    {
        return true;
    }
}

void StringPhysics::Clear()
{

}

