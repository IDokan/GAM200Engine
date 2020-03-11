/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CrushableObject.hpp
Author
        dbsqhd106@gmail.com
Creation Date: DEC/11st/2019

    Header file for the test object whether interact work or not
******************************************************************************/

#pragma once

#include <Object/InteractiveObject/InteractiveObject.hpp>
#include <Component/StringPhysics.hpp>
#include <Component/Physics.hpp>


class CrushableObject : public InteractiveObject
{
public:
    CrushableObject(vector2 _objPos, vector2 _objScale,Physics::ObjectType _objType, String  *_currentString);
   ~CrushableObject();

    void DoSomethingWhenAttached() override;
    void DoSomethingWhenDetached() override;

	//
	void Crushed() noexcept;

private:
    vector2 objPos;
    vector2 objScale;
    Physics::ObjectType objType;
    String* currentString;

};
