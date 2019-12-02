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

StringPhysics::StringPhysics(Object* object, Object* player1, Object* player2) : Component(object), stringPhysicsOwner(dynamic_cast<String*>(object)), player1(player1), player2(player2)
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

	float distanceResultContainer = 0;
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

				// Left-Bottom
				PushbackIfBended(stringVertex1, stringVertex2, i + 1,
					center + vector2{ - objectCollisionBox.Scale.x / 2,  - objectCollisionBox.Scale.y / 2 }, center);
				// Left-Top
				PushbackIfBended(stringVertex1, stringVertex2, i + 1,
					center + vector2{ - objectCollisionBox.Scale.x / 2, + objectCollisionBox.Scale.y / 2 }, center);
				// Right-Bottom
				PushbackIfBended(stringVertex1, stringVertex2, i + 1,
					center + vector2{ + objectCollisionBox.Scale.x / 2, - objectCollisionBox.Scale.y / 2 }, center);
				// Right-Top
				PushbackIfBended(stringVertex1, stringVertex2, i + 1,
					center + vector2{ + objectCollisionBox.Scale.x / 2, + objectCollisionBox.Scale.y / 2 }, center);
			}
		}
	}
	if (addCount != 0)
	{
		InsertPoint();
	}

	*stringPhysicsOwner->vertices.begin() = player1->GetTranslation();
	*(stringPhysicsOwner->vertices.end() - 1) = player2->GetTranslation();
	addCount = 0;


	vertexSize = stringPhysicsOwner->vertices.size(); // will be changed.

	for (size_t i = 0; i < vertexSize - 2; ++i)
	{
		SetNormalVector(stringPhysicsOwner->vertices.at(i).position, stringPhysicsOwner->vertices.at(i + 2).position);
		//If detected,
		if (IsDetached(stringPhysicsOwner->vertices.at(i), stringPhysicsOwner->vertices.at(i + 2), stringPhysicsOwner->vertices.at(i + 1)))
		{
			vertexContainer.emplace_back(std::pair{ i + 1, stringPhysicsOwner->vertices.at(i + 1) });
		}
	}
	if (vertexContainer.empty() == false)
	{
		DeletePoint();
	}
}

bool StringPhysics::IsBendPointInstantiated(vector2 point1, vector2 point2, int index, vector2 targetPoint) const
{
	const auto compare = 2*(abs(norVector.x) > abs(norVector.y) ? abs(norVector.x) : abs(norVector.y));

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

void StringPhysics::InsertPoint()
{
	for (int i = 0; i < addCount; i++)
	{
		const auto& begin = stringPhysicsOwner->vertices.begin();
		stringPhysicsOwner->vertices.insert(begin + vertexContainer.at(i).first, StringVertex{ vertexContainer.at(i).second});
	}
	vertexContainer.clear();
	vertexSize = stringPhysicsOwner->vertices.size();
}

void StringPhysics::DeletePoint()
{
    for (const auto& elem : vertexContainer)
    {
        const auto it = std::find(std::begin(stringPhysicsOwner->vertices), std::end(stringPhysicsOwner->vertices), elem.second);
        stringPhysicsOwner->vertices.erase(it);
    }
    vertexContainer.clear();
    vertexSize = stringPhysicsOwner->vertices.size();
}

void StringPhysics::PushbackIfBended(vector2 point1, vector2 point2, int index, vector2 targetPoint, vector2 centerPosition)
{
	if (IsBendPointInstantiated(point1, point2, index, targetPoint))
	{
		++addCount;
		vertexContainer.emplace_back(std::pair(index, StringVertex{ targetPoint, centerPosition }));
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
	vector2 ToCenter { targetPoint.centerPositionOfCollidedObject - point1.position };
	vector2 ToNextVertex { point2.position - point1.position };

	if (cross(ToTargetPosition, ToCenter) > 0)
	{
		return cross(ToTargetPosition, ToNextVertex) < 0;
	}
	else if(cross(ToTargetPosition, ToCenter) < 0)
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

