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

enum  class ObjectType
{
    CIRCLE,
    RECTANGLE,
};

struct CollsionBox
{
    vector2 Translation{};
    vector2 Scale{};
    vector2 TranslationAmount{};
};

struct matrix3;
struct vector2;
class Object;
class Component;

class Physics : public Component
{
public:
    Physics(Object* obj);
    ~Physics();
    virtual void Init() override;
    virtual void Update(float dt) override;
    virtual void Clear() override;

    void SetVelocity(vector2 velocity);
    void SetVelocity(float x, float y);
    void SetGravity(vector2 gravity);
    void SetGravity(float x, float y);

    void SetCollisionBoxAndObjectType(Object* object, ObjectType objType, vector2 positionAdj = vector2{ 0.f,0.f }, vector2 scaleAdj = vector2{ 0.f,0.f });
    void SetCollisionBoxAndObjectType(Object* object, ObjectType objType, float positionX, float positionY = 0.f, float scaleX = 0.f, float scaleY = 0.f);
    void SetCollisionBoxPosition(vector2 originPos);

    bool IsCollideWith(Object* object);
    
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
private:
    vector2 velocity{};
    vector2 gravity{};
    vector2 force{};
    vector2 vectorTranslation{};
    vector2 position{};

    ObjectType objectType;
    CollsionBox collisionBox{};
    bool hasCollisionBox = false;
};
