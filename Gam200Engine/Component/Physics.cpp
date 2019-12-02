/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Physics.cpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.15.2019

    Source file for Physics
******************************************************************************/

#include "Component/Physics.hpp"
#include <Object/ObjectManager.hpp>
#include <cmath>
#include <iostream>

Physics::Physics(Object* obj) : Component(obj)
{
    hasCollisionBox = false;
    isGhost = false;
    isCollide = false;
}

Physics::~Physics()
{
}

void Physics::Init()
{
    friction = 0.8f;
    initializedPosition = owner->GetTranslation();
    position = owner->GetTranslation();
}

void Physics::Update(float dt)
{
    matrix3 vel = MATRIX3::build_translation(velocity);
    matrix3 gra = MATRIX3::build_translation(gravity);
    matrix3 finalTranslation = vel * gra;

    if (gravity.y >= -50.f && gravity.y != 0) // 종단속도
    {
        gravity.y += -dt * 10.f;
    }

    //GetCollisionBox().Translation;
    force *= friction;

    if (isCollide == false)
    {
        oldPosition = owner->GetComponentByTemplate<Physics>()->GetCollisionBox().Translation;
        //oldPosition = owner->GetTranslation();
        //oldPosition = position;
        vectorTranslation += GetTranslation(finalTranslation);
        vectorTranslation += force;
        position = initializedPosition + vectorTranslation;
    }
    else
    {
        SetWorldForceZero();
        vectorTranslation = oldPosition - initializedPosition;
        position = oldPosition;
        isCollide = false;
    }
    owner->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(position);
}

void Physics::Clear()
{
}

void Physics::SetVelocity(vector2 vel)
{
    this->velocity = vel;
}

void Physics::SetVelocity(float x, float y)
{
    this->velocity.x = x;
    this->velocity.y = y;
}

void Physics::SetGravity(vector2 gra)
{
    this->gravity = gra;
}

void Physics::SetGravity(float x, float y)
{
    this->gravity.x = x;
    this->gravity.y = y;
}

void Physics::SetWorldForceZero()
{
    force = vector2{ 0.f,0.f };
    gravity = vector2{ 0.f,0.f };
    velocity = vector2{ 0.f,0.f };
}

void Physics::SetCollisionBoxAndObjectType(Object* object, ObjectType objType, vector2 positionAdj, vector2 scaleAdj)
{
    objectType = objType;
    collisionBox.TranslationAmount = positionAdj;
    collisionBox.Translation = object->GetTranslation() + positionAdj;
    collisionBox.Scale = object->GetScale() + scaleAdj;
    hasCollisionBox = true;
}

void Physics::SetCollisionBoxAndObjectType(Object* object, ObjectType objType, float positionX, float positionY, float scaleX, float scaleY)
{
    objectType = objType;
    collisionBox.TranslationAmount.x = positionX;
    collisionBox.TranslationAmount.y = positionY;
    collisionBox.Translation.x = object->GetTranslation().x + positionX;
    collisionBox.Translation.y = object->GetTranslation().y + positionY;
    collisionBox.Scale.x = scaleX;
    collisionBox.Scale.y = scaleY;
    hasCollisionBox = true;
}

void Physics::SetCollisionBoxPosition(vector2 originPos)
{
    collisionBox.Translation = originPos + collisionBox.TranslationAmount;
}

void Physics::ActiveGhostCollision(bool active)
{
    isGhost = active;
}

void Physics::SetIsCollide(bool collide)
{
    isCollide = collide;
}

void Physics::SetVectorTranslation(vector2 translation)
{
    vectorTranslation = translation;
}

void Physics::ManageCollision()
{
    const auto& physicsObject = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
    for (const auto& object1 : physicsObject)
    {
        for (const auto& object2 : physicsObject)
        {
            if (object1->GetComponentByTemplate<Physics>() && object2->GetComponentByTemplate<Physics>())
            if (object1->GetObjectType() != object2->GetObjectType())
            {
                if (object1->GetComponentByTemplate<Physics>()->IsCollideWith(&*object2) == true)
                {
                    if (object1->GetComponentByTemplate<Physics>()->GetIsGhost() != true && object2->GetComponentByTemplate<Physics>()->GetIsGhost() != true)
                    {
                        if (object1->GetObjectType() == Object::ObjectType::PLAYER_1)
                        {
                            object1->GetComponentByTemplate<Physics>()->SetIsCollide(true);
                            object1->SetTranslation(object1->GetComponentByTemplate<Physics>()->GetOldPosition());
                        }
                        else if (object1->GetObjectType() == Object::ObjectType::PLAYER_2)
                        {
                            object1->GetComponentByTemplate<Physics>()->SetIsCollide(true);
                            object1->SetTranslation(object1->GetComponentByTemplate<Physics>()->GetOldPosition());
                        }
                        if (object2->GetObjectType() == Object::ObjectType::PLAYER_1)
                        {
                            object2->GetComponentByTemplate<Physics>()->SetIsCollide(true);
                            object2->SetTranslation(object2->GetComponentByTemplate<Physics>()->GetOldPosition());
                        }
                        else if (object2->GetObjectType() == Object::ObjectType::PLAYER_2)
                        {
                            object2->GetComponentByTemplate<Physics>()->SetIsCollide(true);
                            object2->SetTranslation(object2->GetComponentByTemplate<Physics>()->GetOldPosition());
                        }
                    }
                }
            }
        }
    }
}

bool Physics::IsCollideWith(Object* object)
{
    if (owner->GetComponentByTemplate<Physics>() && object->GetComponentByTemplate<Physics>())
    if ((owner->GetComponentByTemplate<Physics>()->GetHasCollisionBox() && object->GetComponentByTemplate<Physics>()->GetHasCollisionBox()  == true) && (owner->GetComponentByTemplate<Physics>()->GetHasCollisionBox() != NULL  && object->GetComponentByTemplate<Physics>()->GetHasCollisionBox() != NULL) )
    {
        CollsionBox ownerCollisionBox = owner->GetComponentByTemplate<Physics>()->GetCollisionBox();
        CollsionBox objectCollisionBox = object->GetComponentByTemplate<Physics>()->GetCollisionBox();

        if (owner->GetComponentByTemplate<Physics>()->GetObjectType() == object->GetComponentByTemplate<Physics>()->GetObjectType())
        {
            if (owner->GetComponentByTemplate<Physics>()->GetObjectType() == ObjectType::RECTANGLE)
            {
                float objectLeft = objectCollisionBox.Translation.x - (objectCollisionBox.Scale.width / 2);
                float objectRight = objectCollisionBox.Translation.x + (objectCollisionBox.Scale.width / 2);
                float objectBottom = objectCollisionBox.Translation.y - (objectCollisionBox.Scale.height / 2);
                float objectTop = objectCollisionBox.Translation.y + (objectCollisionBox.Scale.height / 2);

                float ownerLeft = ownerCollisionBox.Translation.x - (ownerCollisionBox.Scale.width / 2);
                float ownerRight = ownerCollisionBox.Translation.x + (ownerCollisionBox.Scale.width / 2);
                float ownerBottom = ownerCollisionBox.Translation.y - (ownerCollisionBox.Scale.height / 2);
                float ownerTop = ownerCollisionBox.Translation.y + (ownerCollisionBox.Scale.height / 2);

                if (objectRight >= ownerLeft && objectLeft <= ownerRight && objectTop >= ownerBottom && objectBottom <= ownerTop)
                {
                    return true;
                }
            }
            else if (owner->GetComponentByTemplate<Physics>()->GetObjectType() == ObjectType::CIRCLE)
            {
                float xDistance = objectCollisionBox.Translation.x - ownerCollisionBox.Translation.x;
                float yDistance = objectCollisionBox.Translation.y - ownerCollisionBox.Translation.y;
                float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                if (distance < (objectCollisionBox.Scale.x / 2) + (ownerCollisionBox.Scale.x / 2))
                {
                    return true;
                }
            }
        }
        else
        {
            if (owner->GetComponentByTemplate<Physics>()->GetObjectType() == ObjectType::RECTANGLE)
            {
                float rectangleLeft = ownerCollisionBox.Translation.x - (ownerCollisionBox.Scale.width / 2);
                float rectangleRight = ownerCollisionBox.Translation.x + (ownerCollisionBox.Scale.width / 2);
                float rectangleBottom = ownerCollisionBox.Translation.y - (ownerCollisionBox.Scale.height / 2);
                float rectangleTop = ownerCollisionBox.Translation.y + (ownerCollisionBox.Scale.height / 2);

                float circleX = objectCollisionBox.Translation.x;
                float circleY = objectCollisionBox.Translation.y;
                float circleRadius = objectCollisionBox.Scale.x / 2;

                if (circleX >= rectangleLeft && circleX <= rectangleRight && circleY >= rectangleBottom && circleY <= rectangleTop)
                {
                    return true;
                }

                else if (circleX <= rectangleLeft)
                {
                    if (circleY <= rectangleTop && circleY >= rectangleBottom)
                    {
                        float distance = std::abs(circleX - rectangleLeft);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                    else if (circleY >= rectangleTop)
                    {
                        float xDistance = circleX - rectangleLeft;
                        float yDistance = circleY - rectangleTop;
                        float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                    else if (circleY <= rectangleBottom)
                    {
                        float xDistance = circleX - rectangleLeft;
                        float yDistance = circleY - rectangleBottom;
                        float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                }
                else if (circleY >= rectangleTop)
                {
                    if (circleX >= rectangleLeft && circleX <= rectangleRight)
                    {
                        float distance = std::abs(circleY - rectangleTop);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                    else if (circleX >= rectangleRight)
                    {
                        float xDistance = circleX - rectangleRight;
                        float yDistance = circleY - rectangleTop;
                        float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                }
                else if (circleX >= rectangleRight)
                {
                    if (circleY >= rectangleBottom && circleY <= rectangleTop)
                    {
                        float distance = std::abs(circleX - rectangleRight);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                    else if (circleY <= rectangleBottom)
                    {
                        float xDistance = circleX - rectangleRight;
                        float yDistance = circleY - rectangleBottom;
                        float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                }
                else if (circleY <= rectangleBottom)
                {
                    if (circleX >= rectangleLeft && circleX <= rectangleRight)
                    {
                        float distance = std::abs(circleY - rectangleBottom);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                }
            }
            if (owner->GetComponentByTemplate<Physics>()->GetObjectType() == ObjectType::CIRCLE)
            {
                float rectangleLeft = objectCollisionBox.Translation.x - (objectCollisionBox.Scale.width / 2);
                float rectangleRight = objectCollisionBox.Translation.x + (objectCollisionBox.Scale.width / 2);
                float rectangleBottom = objectCollisionBox.Translation.y - (objectCollisionBox.Scale.height / 2);
                float rectangleTop = objectCollisionBox.Translation.y + (objectCollisionBox.Scale.height / 2);

                float circleX = ownerCollisionBox.Translation.x;
                float circleY = ownerCollisionBox.Translation.y;
                float circleRadius = ownerCollisionBox.Scale.x / 2;

                if (circleX >= rectangleLeft && circleX <= rectangleRight && circleY >= rectangleBottom && circleY <= rectangleTop)
                {
                    return true;
                }

                else if (circleX <= rectangleLeft)
                {
                    if (circleY <= rectangleTop && circleY >= rectangleBottom)
                    {
                        float distance = std::abs(circleX - rectangleLeft);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                    else if (circleY >= rectangleTop)
                    {
                        float xDistance = circleX - rectangleLeft;
                        float yDistance = circleY - rectangleTop;
                        float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                    else if (circleY <= rectangleBottom)
                    {
                        float xDistance = circleX - rectangleLeft;
                        float yDistance = circleY - rectangleBottom;
                        float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                }
                else if (circleY >= rectangleTop)
                {
                    if (circleX >= rectangleLeft && circleX <= rectangleRight)
                    {
                        float distance = std::abs(circleY - rectangleTop);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                    else if (circleX >= rectangleRight)
                    {
                        float xDistance = circleX - rectangleRight;
                        float yDistance = circleY - rectangleTop;
                        float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                }
                else if (circleX >= rectangleRight)
                {
                    if (circleY >= rectangleBottom && circleY <= rectangleTop)
                    {
                        float distance = std::abs(circleX - rectangleRight);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                    else if (circleY <= rectangleBottom)
                    {
                        float xDistance = circleX - rectangleRight;
                        float yDistance = circleY - rectangleBottom;
                        float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                }
                else if (circleY <= rectangleBottom)
                {
                    if (circleX >= rectangleLeft && circleX <= rectangleRight)
                    {
                        float distance = std::abs(circleY - rectangleBottom);

                        if (distance <= circleRadius)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Physics::AddForce(vector2 frc)
{
    force = frc;
}

void Physics::AddForce(float x, float y)
{
    force.x = x;
    force.y = y;
}

vector2 Physics::GetTranslation(const matrix3& matrix3) const
{
    return vector2{ matrix3.column2.x, matrix3.column2.y };
}

vector2 Physics::GetVelocity() const noexcept
{
    return velocity;
}

vector2 Physics::GetGravity() const noexcept
{
    return gravity;
}

vector2 Physics::GetForce() const noexcept
{
    return force;
}

bool Physics::IsCollided() const noexcept
{
	return isCollide;
}

vector2 Physics::GetVectorTranslation() const
{
    return vectorTranslation;
}
