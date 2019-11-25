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
				auto objectCollisionBox = object->GetComponentByTemplate<Physics>()->GetCollisionBox();

				objectPoint.leftBottom = vector2{ objectCollisionBox.Translation.x - objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.y - objectCollisionBox.Scale.y / 2 };
				IsBendPointInstantiated(stringPhysicsOwner->vertices.at(i), stringPhysicsOwner->vertices.at(i + 1), i + 1, objectPoint.leftBottom);
				objectPoint.leftTop = vector2{ objectCollisionBox.Translation.x - objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.y + objectCollisionBox.Scale.y / 2 };
				IsBendPointInstantiated(stringPhysicsOwner->vertices.at(i), stringPhysicsOwner->vertices.at(i + 1), i + 1, objectPoint.leftTop);
				objectPoint.rightBottom = vector2{ objectCollisionBox.Translation.x + objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.y - objectCollisionBox.Scale.y / 2 };
				IsBendPointInstantiated(stringPhysicsOwner->vertices.at(i), stringPhysicsOwner->vertices.at(i + 1), i + 1, objectPoint.rightBottom);
				objectPoint.rightTop = vector2{ objectCollisionBox.Translation.x + objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.y + objectCollisionBox.Scale.y / 2 };
				IsBendPointInstantiated(stringPhysicsOwner->vertices.at(i), stringPhysicsOwner->vertices.at(i + 1), i + 1, objectPoint.rightTop);
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

void StringPhysics::IsBendPointInstantiated(vector2 point1, vector2 point2, int index, vector2 targetPoint)
{
	auto compare = abs(norVector.x) > abs(norVector.y) ? abs(norVector.x) : abs(norVector.y);

	vector2 RP{ targetPoint - point1 };
	vector2 QP{ point2 - point1 };

	// Check target point is between the edge. 
	if (!(0 <= dot(RP, QP) && dot(RP, QP) <= dot(QP, QP)))
	{
		return;
	}
	const float resultWithTarget = dot(norVector, targetPoint);
	const float resultWithPointOnLine = dot(norVector, point1);
	const float collisionResult = resultWithTarget - resultWithPointOnLine;
	if (collisionResult <= compare
		&& collisionResult >= -compare)
	{
		if (point1 != targetPoint && point2 != targetPoint)
		{
			printf("Line collision detected in\ntarget point = {%f, %f}\n", targetPoint.x, targetPoint.y);
			printf("Current normal vector is = {%f, %f}\n", norVector.x, norVector.y);
			printf("string point 1 is = {%f, %f}\n", point1.x, point1.y);
			printf("string point 2 is = {%f, %f}\n", point2.x, point2.y);
			printf("collision equation result is %f\n", dot(norVector, targetPoint) - dot(norVector, point2));
			owner->GetComponentByTemplate<StringSprite>()->SetColor(Graphics::Color4f{ 0.f });
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

