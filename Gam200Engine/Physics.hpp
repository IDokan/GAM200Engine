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
struct matrix3;
struct vector2;
class Object;
class Component;

class Physics : public Component
{
public:
    virtual void Init(Object* obj) override;
    virtual void Update(float dt) override;
    virtual void Clear() override;

    void SetVelocity(vector2 velocity);
    void SetVelocity(float x, float y);
    void SetGravity(vector2 gravity);
    void SetGravity(float x, float y);
    bool IsCollideWith(Object* object);
    
    vector2 GetTranslation(matrix3 matrix);

private:
    vector2 velocity{};
    vector2 gravity{};
};
