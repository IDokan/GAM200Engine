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

#include <Component/Physics.hpp>
#include <Object/ObjectManager.hpp>
#include <cmath>
#include <Angle.hpp>
#include <vector>
#include <iostream>
#include <Scenes/SceneManager.hpp>
#include <States/PlayerStates/UpdateAnimation.hpp>
#include <Systems/MessageSystem/MessageDispatcher.hpp>

SoundManager sm;
Physics::Physics(Object* obj) : Component(obj)
{
    shouldResolveResolution = false;
    hasCollisionBox = false;
    isGhost = false;
    isCollide = false;
    velocity = { 0.f,0.f };
    gravity = { 0.f, 0.f };
    position = { 0.f, 0.f };
    oldPosition = { 0.f, 0.f };
    initializedPosition = { 0.f, 0.f };
    objectType = ObjectType::DEFAULT;
    collisionBox = { vector2{0.f,0.f}, vector2{0.f,0.f} };
    hasCollisionBox = true;
    isGhost = false;
    isCollide = false;
    sm = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
}

Physics::~Physics()
{
}

void Physics::Init()
{
    force = { 0.f, 0.f };
    friction = 1.f;
    initializedPosition = owner->GetTranslation();
    position = owner->GetTranslation();
    oldPosition = owner->GetTranslation();
}

void Physics::Update(float dt)
{
    matrix3 vel = MATRIX3::build_translation(velocity);
    matrix3 gra = MATRIX3::build_translation(gravity);
    matrix3 finalTranslation = vel * gra;

    if (gravity.y >= -50.f && gravity.y != 0)
    {
        gravity.y += -dt * 10.f;
    }

    if (shouldResolveResolution == false)
    {
        oldPosition = owner->GetComponentByTemplate<Physics>()->GetCollisionBox().Translation;
        vectorTranslation = GetTranslation(finalTranslation) * friction;
        position = owner->GetTranslation() + vectorTranslation + force;
    }
    else
    {
        SetWorldForceZero();
        position = oldPosition;
        shouldResolveResolution = false;
    }
    isCollide = false;
    force = vector2{ 0.f,0.f };
    friction = 1.f;
    owner->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(position);
    owner->GetComponentByTemplate<Physics>()->collisionBox.Angle = owner->GetRotation();
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
    gravity = vector2{ 0.f,0.f };
    velocity = vector2{ 0.f,0.f };
}

void Physics::SetPosition(vector2 pos)
{
    position = pos;
}

void Physics::SetOldPosition(vector2 pos)
{
    oldPosition = pos;
}

void Physics::SetCollisionBoxAndObjectType(Object* object, ObjectType objType, vector2 positionAdj, vector2 scaleAdj)
{
    objectType = objType;
    collisionBox.TranslationAmount = positionAdj;
    collisionBox.Translation = object->GetTranslation() + positionAdj;
    collisionBox.Scale = object->GetScale() + scaleAdj;
    collisionBox.Angle = object->GetRotation();
    hasCollisionBox = true;
}

void Physics::SetCollisionBoxAndObjectType(Object* object, ObjectType objType, float scaleX, float scaleY, float positionX, float positionY)
{
    objectType = objType;
    collisionBox.TranslationAmount.x = positionX;
    collisionBox.TranslationAmount.y = positionY;
    collisionBox.Translation.x = object->GetTranslation().x + positionX;
    collisionBox.Translation.y = object->GetTranslation().y + positionY;
    collisionBox.Scale.x = object->GetScale().x + scaleX;
    collisionBox.Scale.y = object->GetScale().y + scaleY;
    collisionBox.Angle = object->GetRotation();
    hasCollisionBox = true;
}

void Physics::SetCollisionBoxPosition(vector2 originPos)
{
    collisionBox.Translation = originPos + collisionBox.TranslationAmount;
}

void Physics::SetCollisionBoxScale(vector2 scale)
{
    this->collisionBox.Scale = { scale };
}

void Physics::SetFriction(float fric)
{
    this->friction = fric;
}

void Physics::SetCollisionResolution(bool condition)
{
    shouldResolveResolution = condition;
}

void Physics::SetDirtFlag(bool condition)
{
    dirtyFlag = condition;
}

void Physics::AddForce(vector2 force_)
{
    force = force_;
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

void Physics::SetObjectCollidingSide(ObjectSide objSide_)
{
    objSide = objSide_;
}

void Physics::collisionHelperFunction(Object* object1, Object* object2)
{
    const auto& physicsObject = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();

    if (object1->GetComponentByTemplate<Physics>()->GetIsGhost() != true
        && object2->GetComponentByTemplate<Physics>()->GetIsGhost() != true)
    {
        object1->GetComponentByTemplate<Physics>()->SetCollisionResolution(true);
        object1->GetComponentByTemplate<Physics>()->SetPosition(object1->GetComponentByTemplate<Physics>()->GetOldPosition());
        object1->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(object1->GetComponentByTemplate<Physics>()->GetOldPosition());

        object2->GetComponentByTemplate<Physics>()->SetCollisionResolution(true);
        object2->GetComponentByTemplate<Physics>()->SetPosition(object2->GetComponentByTemplate<Physics>()->GetOldPosition());
        object2->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(object2->GetComponentByTemplate<Physics>()->GetOldPosition());

        for (const auto& object3 : physicsObject)
        {
            if ((object3->GetObjectType() == Object::ObjectType::PLAYER_1 && object1->GetObjectType() == Object::ObjectType::PLAYER_2) || (object3->GetObjectType() == Object::ObjectType::PLAYER_2 && object1->GetObjectType() == Object::ObjectType::PLAYER_1))
            {
                if (object1->GetComponentByTemplate<Physics>()->IsCollideWith(&*object3) == true)
                {
                    object3->GetComponentByTemplate<Physics>()->SetCollisionResolution(true);
                    object3->GetComponentByTemplate<Physics>()->SetPosition(object3->GetComponentByTemplate<Physics>()->GetOldPosition());
                    object3->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(object3->GetComponentByTemplate<Physics>()->GetOldPosition());
                }
            }
            else if ((object3->GetObjectType() == Object::ObjectType::PLAYER_1 && object2->GetObjectType() == Object::ObjectType::PLAYER_2) || object3->GetObjectType() == Object::ObjectType::PLAYER_2 && object2->GetObjectType() == Object::ObjectType::PLAYER_1)
            {
                if (object2->GetComponentByTemplate<Physics>()->IsCollideWith(&*object3) == true)
                {
                    object3->GetComponentByTemplate<Physics>()->SetCollisionResolution(true);
                    object3->GetComponentByTemplate<Physics>()->SetPosition(object3->GetComponentByTemplate<Physics>()->GetOldPosition());
                    object3->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(object3->GetComponentByTemplate<Physics>()->GetOldPosition());
                }
            }
        }
    }
}

void Physics::ManageCollision()
{
    const auto& physicsObject = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
    for (const auto& object1 : physicsObject)
    {
        for (const auto& object2 : physicsObject)
        {
            if (object1->GetComponentByTemplate<Physics>() && object2->GetComponentByTemplate<Physics>() && !(object1->GetObjectType() == Object::ObjectType::STRING && object2->GetObjectType() == Object::ObjectType::STRING))
            {
                if (!(object1->GetObjectType() == Object::ObjectType::PLAYER_1 && object2->GetObjectType() == Object::ObjectType::PLAYER_2) && !(object1->GetObjectType() == Object::ObjectType::PLAYER_2 && object2->GetObjectType() == Object::ObjectType::PLAYER_1))
                {
                    if (object1->GetObjectType() != object2->GetObjectType())
                    {
                        if (object1->GetComponentByTemplate<Physics>()->GetCollisionBox().Angle != 0.f || object2->GetComponentByTemplate<Physics>()->GetCollisionBox().Angle != 0.f)
                        {
                            if (object1->GetComponentByTemplate<Physics>()->IsCollideWithRotatedObject(&*object2) == true)
                            {
                                object1->GetComponentByTemplate<Physics>()->SetIsCollide(true);
                                object2->GetComponentByTemplate<Physics>()->SetIsCollide(true);
                                collisionHelperFunction(&*object1, &*object2);
                            }
                        }
                        else
                        {
                            if (object1->GetComponentByTemplate<Physics>()->IsCollideWith(&*object2) == true)
                            {
                                object1->GetComponentByTemplate<Physics>()->SetIsCollide(true);
                                object2->GetComponentByTemplate<Physics>()->SetIsCollide(true);
                                collisionHelperFunction(&*object1, &*object2);
                            }
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
    {
        if ((owner->GetComponentByTemplate<Physics>()->GetHasCollisionBox() && object->GetComponentByTemplate<Physics>()->GetHasCollisionBox() == true) && (owner->GetComponentByTemplate<Physics>()->GetHasCollisionBox() != NULL && object->GetComponentByTemplate<Physics>()->GetHasCollisionBox() != NULL))
        {
            CollisionBox ownerCollisionBox = owner->GetComponentByTemplate<Physics>()->GetCollisionBox();
            CollisionBox objectCollisionBox = object->GetComponentByTemplate<Physics>()->GetCollisionBox();

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
    }

    return false;
}

bool Physics::IsCollideWithRotatedObject(Object* object)
{
    CollisionBox ownerCollisionBox = owner->GetComponentByTemplate<Physics>()->GetCollisionBox();
    CollisionBox objectCollisionBox = object->GetComponentByTemplate<Physics>()->GetCollisionBox();

    vector2 ownerCollisionBoxCenter = vector2{ ownerCollisionBox.Translation.x, ownerCollisionBox.Translation.y };
    vector2 objectCollisionBoxCenter = vector2{ objectCollisionBox.Translation.x, objectCollisionBox.Translation.y };

    CalculateSeperateAxisVectorOf(owner);
    CalculateSeperateAxisVectorOf(object);

    vector2 ownerLeftTop = CalculateLeftTop(owner);
    vector2 ownerLeftBottom = CalculateLeftBottom(owner);
    vector2 ownerRightTop = CalculateRightTop(owner);
    vector2 ownerRightBottom = CalculateRightBottom(owner);

    vector2 objectLeftTop = CalculateLeftTop(object);
    vector2 objectLeftBottom = CalculateLeftBottom(object);
    vector2 objectRightTop = CalculateRightTop(object);
    vector2 objectRightBottom = CalculateRightBottom(object);

    ownerLeftTop = CalculateRotatedObjectVertex(ownerLeftTop, ownerCollisionBox);
    ownerLeftBottom = CalculateRotatedObjectVertex(ownerLeftBottom, ownerCollisionBox);
    ownerRightTop = CalculateRotatedObjectVertex(ownerRightTop, ownerCollisionBox);
    ownerRightBottom = CalculateRotatedObjectVertex(ownerRightBottom, ownerCollisionBox);

    objectLeftTop = CalculateRotatedObjectVertex(objectLeftTop, objectCollisionBox);
    objectLeftBottom = CalculateRotatedObjectVertex(objectLeftBottom, objectCollisionBox);
    objectRightTop = CalculateRotatedObjectVertex(objectRightTop, objectCollisionBox);
    objectRightBottom = CalculateRotatedObjectVertex(objectRightBottom, objectCollisionBox);

    std::vector<vector2> ownerCoordinateContainer;
    std::vector<vector2> objectCoordinateContainer;

    ownerCoordinateContainer.push_back(ownerLeftTop);
    ownerCoordinateContainer.push_back(ownerLeftBottom);
    ownerCoordinateContainer.push_back(ownerRightTop);
    ownerCoordinateContainer.push_back(ownerRightBottom);

    objectCoordinateContainer.push_back(objectLeftTop);
    objectCoordinateContainer.push_back(objectLeftBottom);
    objectCoordinateContainer.push_back(objectRightTop);
    objectCoordinateContainer.push_back(objectRightBottom);

    float ownerMax = 0.f;
    float ownerMin = 0.f;
    float ownerTemp = 0.f;
    float objectMax = 0.f;
    float objectMin = 0.f;
    float objectTemp = 0.f;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ownerTemp = dot(SAT[i], ownerCoordinateContainer[j]);
            objectTemp = dot(SAT[i], objectCoordinateContainer[j]);

            if (j == 0)
            {
                ownerMax = ownerTemp;
                ownerMin = ownerTemp;

                objectMax = objectTemp;
                objectMin = objectTemp;
            }
            else
            {
                if (ownerTemp <= ownerMin)
                {
                    ownerMin = ownerTemp;
                }
                else if (ownerTemp >= ownerMax)
                {
                    ownerMax = ownerTemp;
                }

                if (objectTemp <= objectMin)
                {
                    objectMin = objectTemp;
                }
                else if (objectTemp >= objectMax)
                {
                    objectMax = objectTemp;
                }
            }
        }
        if (objectMax <= ownerMin || ownerMax <= objectMin)
        {
            SAT.clear();
            return false;
        }
    }

    SAT.clear();
    return true;
}

void Physics::IsCollideWithMovedObject()
{
    const auto ownerVelocity = owner->GetComponentByTemplate<Physics>()->GetVelocity();
    const auto& physicsObject = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
    for (auto object1 : physicsObject)
    {
        if (object1->GetComponentByTemplate<Physics>())
        {
            if (object1->GetObjectType() == Object::ObjectType::MOVING_OBJECT)
            {
                if (owner->GetComponentByTemplate<Physics>()->IsCollideWith(&*object1))
                {
                    if (owner->GetScale().x >= UpdateAnimation::maximum_scaling_limit * 0.8f)
                    {
                        switch (object1->GetComponentByTemplate<Physics>()->GetObjectCollidingSide())
                        {
                        case Physics::ObjectSide::UP_SIDE:
                        {
                            if (ownerVelocity.y < 0.f && ownerVelocity.x == 0.f)
                            {
                                if (dirtyFlag == true)
                                {
                                    lastCollidingSide = Physics::ObjectSide::UP_SIDE;
                                    sm.Play_Sound(PUSHABLE_BOX_SOUND);
                                }
                                object1->GetComponentByTemplate<Physics>()->SetPosition(object1->GetComponentByTemplate<Physics>()->GetPosition() + vector2{ 0.f, ownerVelocity.y });
                                object1->SetTranslation(object1->GetComponentByTemplate<Physics>()->GetPosition());
                                object1->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(object1->GetComponentByTemplate<Physics>()->GetPosition());
                                dirtyFlag = false;
                            }
                            else
                            {
                                if (movingObjectFlag == true)
                                {
         
                                    if (Player* player = dynamic_cast<Player*>(owner);
                                        player != nullptr)
                                    {
                                        player->SetIsBlock(true);
                                    }
                                    
                                    movingObjectFlag = false;
                                }

                            }

                            break;
                        }
                        case Physics::ObjectSide::BOTTOM_SIDE:
                        {
                            if (ownerVelocity.y > 0.f && ownerVelocity.x == 0.f)
                            {
                                if (dirtyFlag == true)
                                {
                                    lastCollidingSide = Physics::ObjectSide::BOTTOM_SIDE;
                                    sm.Play_Sound(PUSHABLE_BOX_SOUND);
                                }
                                object1->GetComponentByTemplate<Physics>()->SetPosition(object1->GetComponentByTemplate<Physics>()->GetPosition() + vector2{ 0.f, ownerVelocity.y });
                                object1->SetTranslation(object1->GetComponentByTemplate<Physics>()->GetPosition());
                                object1->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(object1->GetComponentByTemplate<Physics>()->GetPosition());
                                dirtyFlag = false;
                            }
                            else
                            {
                                if (movingObjectFlag == true)
                                {
                                    if (Player* player = dynamic_cast<Player*>(owner);
                                        player != nullptr)
                                    {
                                        player->SetIsBlock(true);
                                    }
                                    movingObjectFlag = false;
                                }
                            }
                            break;
                        }
                        case Physics::ObjectSide::RIGHT_SIDE:
                        {
                            if (ownerVelocity.x < 0.f && ownerVelocity.y == 0.f)
                            {
                                if (dirtyFlag == true)
                                {
                                    lastCollidingSide = Physics::ObjectSide::RIGHT_SIDE;
                                    sm.Play_Sound(PUSHABLE_BOX_SOUND);
                                }
                                object1->GetComponentByTemplate<Physics>()->SetPosition(object1->GetComponentByTemplate<Physics>()->GetPosition() + vector2{ ownerVelocity.x, 0.f });
                                object1->SetTranslation(object1->GetComponentByTemplate<Physics>()->GetPosition());
                                object1->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(object1->GetComponentByTemplate<Physics>()->GetPosition());
                                dirtyFlag = false;
                            }
                            else
                            {
                                if (movingObjectFlag == true)
                                {
                                    if (Player* player = dynamic_cast<Player*>(owner);
                                        player != nullptr)
                                    {
                                        player->SetIsBlock(true);
                                    }
                                    movingObjectFlag = false;
                                }
                            }
                            break;
                        }
                        case Physics::ObjectSide::LEFT_SIDE:
                        {
                            if (ownerVelocity.x > 0.f && ownerVelocity.y == 0.f)
                            {
                                if (dirtyFlag == true)
                                {
                                    lastCollidingSide = Physics::ObjectSide::LEFT_SIDE;
                                    sm.Play_Sound(PUSHABLE_BOX_SOUND);
                                }

                                object1->GetComponentByTemplate<Physics>()->SetPosition(object1->GetComponentByTemplate<Physics>()->GetPosition() + vector2{ ownerVelocity.x, 0.f });
                                object1->SetTranslation(object1->GetComponentByTemplate<Physics>()->GetPosition());
                                object1->GetComponentByTemplate<Physics>()->SetCollisionBoxPosition(object1->GetComponentByTemplate<Physics>()->GetPosition());
                                dirtyFlag = false;
                            }
                            else
                            {
                                if (movingObjectFlag == true)
                                {
                                    if (Player* player = dynamic_cast<Player*>(owner);
                                        player != nullptr)
                                    {
                                        player->SetIsBlock(true);
                                    }
                                    movingObjectFlag = false;
                                }
                            }
                            break;
                        }
                        default:
                            break;
                        }
                    }
                    else
                    {
                    if (movingObjectFlag == true)
                    {
                        if (Player* player = dynamic_cast<Player*>(owner);
                            player != nullptr)
                        {
                            player->SetIsBlock(true);
                        }
                        movingObjectFlag = false;
                    }
                    }
                }
                else
                {
                    if (owner->GetComponentByTemplate<Physics>()->GetVelocity() == vector2{ 0.f, 0.f } && movingObjectFlag == false)
                    {
                        if (Player* player = dynamic_cast<Player*>(owner);
                            player != nullptr)
                        {
                            player->SetIsBlock(false);
                        }
                        movingObjectFlag = true;
                    }
                    if (owner->GetComponentByTemplate<Physics>()->GetVelocity() == vector2{ 0.f, 0.f } && dirtyFlag == false && lastCollidingSide == Physics::ObjectSide::UP_SIDE)
                    {
                        dirtyFlag = true;
                        sm.Stop_Sound(PUSHABLE_BOX_SOUND);
                    }
                    else if (owner->GetComponentByTemplate<Physics>()->GetVelocity() == vector2{ 0.f, 0.f } && dirtyFlag == false && lastCollidingSide == Physics::ObjectSide::BOTTOM_SIDE)
                    {
                        dirtyFlag = true;
                        sm.Stop_Sound(PUSHABLE_BOX_SOUND);
                    }
                    else if (owner->GetComponentByTemplate<Physics>()->GetVelocity() == vector2{ 0.f, 0.f } && dirtyFlag == false && lastCollidingSide == Physics::ObjectSide::RIGHT_SIDE)
                    {
                        dirtyFlag = true;
                        sm.Stop_Sound(PUSHABLE_BOX_SOUND);
                    }
                    else if (owner->GetComponentByTemplate<Physics>()->GetVelocity() == vector2{ 0.f, 0.f } && dirtyFlag == false && lastCollidingSide == Physics::ObjectSide::LEFT_SIDE)
                    {
                        dirtyFlag = true;
                        sm.Stop_Sound(PUSHABLE_BOX_SOUND);
                    }
                }
            }
        }
    }
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

bool Physics::IsCollided() const noexcept
{
    return isCollide;
}

vector2 Physics::GetVectorTranslation() const
{
    return vectorTranslation;
}

void Physics::CalculateSeperateAxisVectorOf(Object* obj)
{
    CalculateXaxisVector(obj);
    CalculateYaxisVector(obj);
}

void Physics::CalculateXaxisVector(Object* obj)
{
    CollisionBox objectCollisionBox = obj->GetComponentByTemplate<Physics>()->GetCollisionBox();
    vector2 xAxisVector = vector2{ objectCollisionBox.Translation.x + objectCollisionBox.Scale.x / 2, objectCollisionBox.Translation.y } -vector2{ objectCollisionBox.Translation.x, objectCollisionBox.Translation.y };
    xAxisVector = CalculateRotatedObjectVector(xAxisVector, objectCollisionBox.Angle);
    SAT.push_back(xAxisVector);
}

void Physics::CalculateYaxisVector(Object* obj)
{
    CollisionBox objectCollisionBox = obj->GetComponentByTemplate<Physics>()->GetCollisionBox();
    vector2 yAxisVector = vector2{ objectCollisionBox.Translation.x, objectCollisionBox.Translation.y + objectCollisionBox.Scale.y / 2 } -vector2{ objectCollisionBox.Translation.x, objectCollisionBox.Translation.y };
    yAxisVector = CalculateRotatedObjectVector(yAxisVector, objectCollisionBox.Angle);
    SAT.push_back(yAxisVector);
}

vector2 Physics::CalculateLeftTop(Object* obj)
{
    CollisionBox collisionBox = obj->GetComponentByTemplate<Physics>()->GetCollisionBox();
    vector2 collisionBoxCenter = vector2{ collisionBox.Translation.x, collisionBox.Translation.y };
    return vector2{ vector2{ collisionBox.Translation.x - collisionBox.Scale.x / 2, collisionBox.Translation.y + collisionBox.Scale.y / 2 } -collisionBoxCenter };
}

vector2 Physics::CalculateRightTop(Object* obj)
{
    CollisionBox collisionBox = obj->GetComponentByTemplate<Physics>()->GetCollisionBox();
    vector2 collisionBoxCenter = vector2{ collisionBox.Translation.x, collisionBox.Translation.y };
    return vector2{ vector2{ collisionBox.Translation.x + collisionBox.Scale.x / 2, collisionBox.Translation.y + collisionBox.Scale.y / 2 } -collisionBoxCenter };
}

vector2 Physics::CalculateLeftBottom(Object* obj)
{
    CollisionBox collisionBox = obj->GetComponentByTemplate<Physics>()->GetCollisionBox();
    vector2 collisionBoxCenter = vector2{ collisionBox.Translation.x, collisionBox.Translation.y };
    return vector2{ vector2{ collisionBox.Translation.x - collisionBox.Scale.x / 2, collisionBox.Translation.y - collisionBox.Scale.y / 2 } -collisionBoxCenter };
}

vector2 Physics::CalculateRightBottom(Object* obj)
{
    CollisionBox collisionBox = obj->GetComponentByTemplate<Physics>()->GetCollisionBox();
    vector2 collisionBoxCenter = vector2{ collisionBox.Translation.x, collisionBox.Translation.y };
    return vector2{ vector2{ collisionBox.Translation.x + collisionBox.Scale.x / 2, collisionBox.Translation.y - collisionBox.Scale.y / 2 } -collisionBoxCenter };
}

vector2 Physics::CalculateRotatedObjectVector(vector2 vertex, float angle)
{
    vector2 rotatedVertex = vector2{ vertex.x * std::cos(angle) - vertex.y * std::sin(angle), vertex.x * std::sin(angle) + vertex.y * std::cos(angle) };
    return rotatedVertex;
}

vector2 Physics::CalculateRotatedObjectVertex(vector2 vertex, CollisionBox coliisionBox)
{
    vector2 rotatedVertex = vector2{ vertex.x * std::cos(coliisionBox.Angle) - vertex.y * std::sin(coliisionBox.Angle), vertex.x * std::sin(coliisionBox.Angle) + vertex.y * std::cos(coliisionBox.Angle) } +vector2{ coliisionBox.Translation.x , coliisionBox.Translation.y };
    return rotatedVertex;
}