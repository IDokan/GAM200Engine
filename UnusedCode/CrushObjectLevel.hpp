/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CrushObjectLevel.hpp
Author: dbsqhd106@gmail.com

Creation Date: DEC/11th/2019

    Header file for the test object whether interact work or not
******************************************************************************/

#pragma once
#include <Scenes/Scene.hpp>
#include <Object/InteractiveObject/CrushableObject.hpp>

class Object;
class String;

class CrushObjectLevel : public Scene
{
public:
    CrushObjectLevel();
    void UpdateCollisionBox(Object* obj1, Object* obj2);
    virtual ~CrushObjectLevel();

    void Update(float dt) override;

protected:
    void GameRestart() override;
    void Load() override;
    void Unload() override;

    void Input();
    void Collision();
    void InitObject();
private:
    Object* background;
    Object* startPoint{};
    Object* goalPoint{};

    CrushableObject* object1;
    CrushableObject* object2;
    CrushableObject* object3;
    CrushableObject* object4;
    CrushableObject* object5;
    CrushableObject* object6;
};
