/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Physics.hpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.15.2019

    Header file for Physics
******************************************************************************/

#pragma once
#include <Vector2.hpp>
#include <matrix3.hpp>
#include <Component/Component.hpp>
#include <Object/Object.hpp>

class Physics : public Component
{
public:

    struct CollisionBox
    {
        vector2 Translation{};
        vector2 Scale{};
        vector2 TranslationAmount{};
        float Angle;
    };

    enum  class ObjectType
    {
        CIRCLE,
        RECTANGLE,
        DEFAULT,
    };

    Physics(Object* obj);
    ~Physics();

    virtual void Init() override;
    virtual void Update(float dt) override;
    virtual void Clear() override;

    void SetVelocity(vector2 velocity);
    void SetVelocity(float x, float y);
    void SetGravity(vector2 gravity);
    void SetGravity(float x, float y);
    void SetWorldForceZero();
    void SetPosition(vector2 pos);
    void SetOldPosition(vector2 pos);
    void SetCollisionBoxAndObjectType(Object* object, ObjectType objType, vector2 positionAdj = vector2{ 0.f,0.f }, vector2 scaleAdj = vector2{ 0.f,0.f });
    void SetCollisionBoxAndObjectType(Object* object, ObjectType objType, float positionX, float positionY = 0.f, float scaleX = 0.f, float scaleY = 0.f);
    void SetCollisionBoxPosition(vector2 originPos);
    void SetCollisionBoxScale(vector2 scale);
    void SetFriction(float friction);

    void ActiveGhostCollision(bool active);
    void SetIsCollide(bool collide);
    void SetVectorTranslation(vector2 translation);
    bool IsCollideWith(Object* object);
    bool IsCollideWithRotatedObject(Object* object);
    void ManageCollision();

    vector2 GetTranslation(const matrix3& matrix) const;
    vector2 GetVelocity() const noexcept;
    vector2 GetGravity() const noexcept;
    bool IsCollided() const noexcept;


    const CollisionBox& GetCollisionBox() const
    {
        return collisionBox;
    }

    bool GetHasCollisionBox() const
    {
        return hasCollisionBox;
    }

    ObjectType GetObjectType() //Woo
    {
        return objectType;
    }

    vector2 GetPosition() const
    {
        return position;
    }

    vector2 GetOldPosition() const
    {
        return oldPosition;
    }

    bool GetIsGhost() const
    {
        return isGhost;
    }

    bool GetIsCollide() const
    {
        return isCollide;
    }

    vector2 GetVectorTranslation() const;
    vector2 force{};
private:
    void CalculateSeperateAxisVectorOf(Object* obj);
    void CalculateXaxisVector(Object* obj);
    void CalculateYaxisVector(Object* obj);
    void CalculateObjectVertex(Object* obj);
    vector2 CalculateRotatedObjectVertex(vector2 vertex, float angle);

    vector2 velocity{};
    vector2 gravity{};
    vector2 vectorTranslation{};
    vector2 position{};
    vector2 oldPosition{};
    vector2 initializedPosition{};

    float friction;

    ObjectType objectType{};
    CollisionBox collisionBox{};

    bool hasCollisionBox;
    bool isGhost;
    bool isCollide;

    std::vector<vector2> SAT;
};
