/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CrushableObject.cpp
Author: dbsqhd106@gmail.com

Creation Date: DEC/11st/2019

    Header file for the test object whether interact work or not
******************************************************************************/


#include <Object/InteractiveObject/ObstacleObject.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Scenes/SceneManager.hpp>

ObstacleObject::ObstacleObject(vector2 _objPos, vector2 _objScale,
    Physics::ObjectType _objType):
InteractiveObject(),objPos(_objPos),objScale(_objScale),objType(_objType)
{
    Object::AddComponent(new Sprite(this));
    SetTranslation(objPos);
    SetScale(objScale);
    Object::AddComponent(new Physics(this));
    GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, objType);
    SetDepth(-0.1f);
}

ObstacleObject::~ObstacleObject()
{
}

void ObstacleObject::DoSomethingWhenAttached()
{
    SceneManager::GetSceneManager()->GameRestart();
}

void ObstacleObject::DoSomethingWhenDetached()
{
}
