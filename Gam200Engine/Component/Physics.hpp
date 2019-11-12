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
#include "Vector2.hpp"
#include "matrix3.hpp"
#include "Component.hpp"
#include "Object/Object.hpp"

class Physics : public Component
{
public:

    struct CollsionBox
    {
        vector2 Translation{};
        vector2 Scale{};
        vector2 TranslationAmount{};
    };

    enum  class ObjectType
    {
        CIRCLE,
        RECTANGLE,
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

    void SetCollisionBoxAndObjectType(Object* object, ObjectType objType, vector2 positionAdj = vector2{ 0.f,0.f }, vector2 scaleAdj = vector2{ 0.f,0.f });
    void SetCollisionBoxAndObjectType(Object* object, ObjectType objType, float positionX, float positionY = 0.f, float scaleX = 0.f, float scaleY = 0.f);
    void SetCollisionBoxPosition(vector2 originPos);
    void ActiveGhostCollision(bool active);
    void SetIsCollide(bool collide);
    void SetVectorTranslation(vector2 translation);

    bool IsCollideWith(Object* object);
    void ManageCollision();
    
    void AddForce(vector2 frc);
    void AddForce(float x, float y);

    const vector2 GetTranslation(const matrix3 &matrix) const;
    /**
	 * \brief Implemented by Il.
	 * \return velocity
	 */
	vector2 GetVelocity() const noexcept;
    /**
	 * \brief Implemented by Il.
	 * \return gravity
	 */
	vector2 GetGravity() const noexcept;
    /**
	 * \brief Implemented by Il.
	 * \return force
	 */
	vector2 GetForce() const noexcept;

    const CollsionBox &GetCollisionBox() const
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

    vector2 GetVectorTranslation() const; 

protected:
    vector2 velocity{};
    vector2 gravity{};
    vector2 force{};
    vector2 vectorTranslation{};
    vector2 position{};
    vector2 oldPosition{};
    vector2 initializedPosition{};

    ObjectType objectType{};
    CollsionBox collisionBox{};

    float friction;
   
    bool hasCollisionBox;
    bool isGhost;
    bool isCollide;
};
