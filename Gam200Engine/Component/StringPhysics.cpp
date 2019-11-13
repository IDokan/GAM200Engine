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

StringPhyscis::StringPhyscis(Object* object) : Physics(object)
{
}

StringPhyscis::StringPhyscis(Object* obj, Object* player1, Object* player2) : Physics(obj), player1(player1), player2(player2)
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
    const auto& physicsObject = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
    for (const auto& object : physicsObject)
    {
        if (object->GetObjectType() == Object::ObjectType::OBSTACLE)
            Iscollide(&*object, player1, player2);
    }

    //if (manageVertex.size() == 1)
    //{
    //    const float dx = (player1->GetTranslation().x - manageVertex[0].x);
    //    const float dy = (player1->GetTranslation().y - manageVertex[0].y);
    //    float stringSize = sqrt(dx * dx + dy * dy);
    //    float stringAngle = (dx) / stringSize;

    //    if (isTest == true)
    //    {
    //        auto objManager = ObjectManager::GetObjectManager();
    //        newPlayer1String = new Object;
    //        newPlayer1String->SetObjectType(Object::ObjectType::STRING);
    //        newPlayer1String->SetObjectName("player1String");
    //        newPlayer1String->AddComponent(new Sprite(newPlayer1String));
    //        newPlayer1String->AddComponent(new StringPhyscis(newPlayer1String));
    //        objManager->FindLayer(LayerNames::Stage)->AddObject(newPlayer1String);
    //    }
    //    newPlayer1String->SetTranslation((player1->GetTranslation() + manageVertex[0]) / 2);
    //    newPlayer1String->SetScale(vector2{ stringSize, 5.0f });
    //    if (player1->GetTranslation().y < manageVertex[0].y)
    //        newPlayer1String->SetRotation(acos(-stringAngle));
    //    else
    //        newPlayer1String->SetRotation(acos(stringAngle));


    //}
    //else
    //{
    //    const float dx = (player1->GetTranslation().x - player2->GetTranslation().x);
    //    const float dy = (player1->GetTranslation().y - player2->GetTranslation().y);
    //    float stringSize = sqrt(dx * dx + dy * dy);
    //    float stringAngle = (dx) / stringSize;

    //    owner->SetTranslation(vector2{ (player1->GetTranslation() + player2->GetTranslation()) / 2 });
    //    owner->SetScale(vector2{ stringSize, 5.0f });
    //    if (player1->GetTranslation().y < player2->GetTranslation().y)
    //        owner->SetRotation(acos(-stringAngle));
    //    else
    //        owner->SetRotation(acos(stringAngle));
    //}


  /*  if (manageVertex.size() == 1)
    {
        const float dx = (player1->GetTranslation().x - manageVertex[0].x);
        const float dy = (player1->GetTranslation().y - manageVertex[0].y);
        float stringSize = sqrt(dx * dx + dy * dy);
        float stringAngle = (dx) / stringSize;
        newPlayer1String->SetTranslation((player1->GetTranslation() + manageVertex[0]) / 2);
        newPlayer1String->SetScale(vector2{ stringSize, 5.0f });
        if (player1->GetTranslation().y < manageVertex[0].y)
            newPlayer1String->SetRotation(acos(-stringAngle));
        else
            newPlayer1String->SetRotation(acos(stringAngle));
    }
    else
    {
        const float dx = (player1->GetTranslation().x - player2->GetTranslation().x);
        const float dy = (player1->GetTranslation().y - player2->GetTranslation().y);
        float stringSize = sqrt(dx * dx + dy * dy);
        float stringAngle = (dx) / stringSize;

        owner->SetTranslation(vector2{ (player1->GetTranslation() + player2->GetTranslation()) / 2 });
        owner->SetScale(vector2{ stringSize, 5.0f });
        if (player1->GetTranslation().y < player2->GetTranslation().y)
            owner->SetRotation(acos(-stringAngle));
        else
            owner->SetRotation(acos(stringAngle));
    }*/

}

void StringPhyscis::SetStringPosition(vector2 pos)
{
    position = pos;
}

void StringPhyscis::StringCollision()
{

}

void StringPhyscis::Iscollide(Object* object, Object* player2, Object* player1)
{
    vector2 objectCollisionBoxPosition = object->GetComponentByTemplate<Physics>()->GetCollisionBox().Translation;
    vector2 objectCollisionBoxScale = object->GetComponentByTemplate<Physics>()->GetCollisionBox().Scale;

    objectLeftBottom = { objectCollisionBoxPosition.x - (objectCollisionBoxScale.x / 2), objectCollisionBoxPosition.y - (objectCollisionBoxScale.y / 2) };
    objectLeftTop = { objectCollisionBoxPosition.x - (objectCollisionBoxScale.x / 2), objectCollisionBoxPosition.y + (objectCollisionBoxScale.y / 2) };
    objectRightBottom = { objectCollisionBoxPosition.x + (objectCollisionBoxScale.x / 2), objectCollisionBoxPosition.y - (objectCollisionBoxScale.y / 2) };
    objectRightTop = { objectCollisionBoxPosition.x + (objectCollisionBoxScale.x / 2), objectCollisionBoxPosition.y + (objectCollisionBoxScale.y / 2) };

    vector2 point1 = player1->GetTranslation();
    vector2 point2 = player2->GetTranslation();

    vector2 dirVector = vector2{ point1.x - point2.x, point1.y - point2.y };
    vector2 norVector = vector2{ dirVector.y, -dirVector.x };

    if (IsBendPointInstantiated(norVector, point1, point2) == true)
    {
        switch (point)
        {
        case Point::LeftBottom:
        {
            if (isFirst == true)
            {
                auto objManager = ObjectManager::GetObjectManager();
                manageVertex.push_back(objectLeftBottom);

                const float dx = (player1->GetTranslation().x - manageVertex[0].x);
                const float dy = (player1->GetTranslation().y - manageVertex[0].y);
                float stringSize = sqrt(dx * dx + dy * dy);
                float stringAngle = (dx) / stringSize;

                newPlayer1String = new Object;
                newPlayer1String->SetObjectType(Object::ObjectType::STRING);
                newPlayer1String->SetObjectName("player1String");
                newPlayer1String->SetTranslation((player1->GetTranslation() + manageVertex[0]) / 2);
                newPlayer1String->SetScale(vector2{ stringSize, 5.0f });
                newPlayer1String->AddComponent(new Sprite(newPlayer1String));
                newPlayer1String->AddComponent(new StringPhyscis(newPlayer1String, player1, player2));
                newPlayer1String->GetComponentByTemplate<StringPhyscis>()->SetVertex(objectLeftBottom);
                objManager->FindLayer(LayerNames::Stage)->AddObjectDynamically(newPlayer1String);

                isFirst = false;
            }
            break;
        }
        case Point::LeftTop:
        {

        }
        case Point::RightTop:
        {

        }
        case Point::RightBottom:
        {

        }
        }
        const float dx = (player1->GetTranslation().x - manageVertex[0].x);
        const float dy = (player1->GetTranslation().y - manageVertex[0].y);
        float stringSize = sqrt(dx * dx + dy * dy);
        float stringAngle = (dx) / stringSize;

        newPlayer1String->SetTranslation((player1->GetTranslation() + manageVertex[0]) / 2);
        if (player1->GetTranslation().y < manageVertex[0].y)
        {
            newPlayer1String->SetRotation(acos(-stringAngle));
        }
        else
        {
            newPlayer1String->SetRotation(acos(stringAngle));
        }
    }
     else
     {
        
         const float dx = (player1->GetTranslation().x - player2->GetTranslation().x);
         const float dy = (player1->GetTranslation().y - player2->GetTranslation().y);
         float stringSize = sqrt(dx * dx + dy * dy);
         float stringAngle = (dx) / stringSize;

         owner->SetTranslation(vector2{ (player1->GetTranslation() + player2->GetTranslation()) / 2 });
         owner->SetScale(vector2{ stringSize, 5.0f });
         if (player1->GetTranslation().y < player2->GetTranslation().y)
             owner->SetRotation(acos(-stringAngle));
         else
             owner->SetRotation(acos(stringAngle));
     }
}

void StringPhyscis::SetVertex(vector2 vertex)
{
    manageVertex.push_back(vertex);
}

bool StringPhyscis::IsBendPointInstantiated(vector2 norVector, vector2 point1, vector2 point2)
{
    auto compare = norVector.x > norVector.y ? norVector.x : norVector.y;

    if (dot(norVector, objectLeftBottom) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectLeftBottom) - dot(norVector, point2) >= -abs(compare))
    {
        point = Point::LeftBottom;
        return true;
    }
    if (dot(norVector, objectLeftTop) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectLeftTop) - dot(norVector, point2) >= -abs(compare))
    {
        point = Point::LeftTop;
        return true;
    }
    if (dot(norVector, objectRightBottom) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectRightBottom) - dot(norVector, point2) >= -abs(compare))
    {
        point = Point::RightBottom;
        return true;
    }
    if (dot(norVector, objectRightTop) - dot(norVector, point2) <= abs(compare)
        && dot(norVector, objectRightTop) - dot(norVector, point2) >= -abs(compare))
    {
        point = Point::RightTop;
        return true;
    }
    point = Point::Default;
    return false;
}

void StringPhyscis::Clear()
{

}

