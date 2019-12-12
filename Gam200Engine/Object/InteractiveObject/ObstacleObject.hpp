/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CrushableObject.cpp
Author: dbsqhd106@gmail.com

Creation Date: DEC/11st/2019

    Header file for the test object whether interact work or not
******************************************************************************/

#include <Object/InteractiveObject/InteractiveObject.hpp>
#include <Component/Physics.hpp>

class ObstacleObject : public InteractiveObject
{

public:
    ObstacleObject(vector2 _objPos, vector2 _objScale,
        Physics::ObjectType _objType);

    ~ObstacleObject();

    void DoSomethingWhenAttached() override;
    void DoSomethingWhenDetached() override;

private:
    vector2 objPos;
    vector2 objScale;
    Physics::ObjectType objType;
};
