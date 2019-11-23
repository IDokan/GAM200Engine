/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   String.cpp
Author
		
Creation Date:

	Source file for the String Object
******************************************************************************/
#include <Object/Strings/String.hpp>
#include "Component/StringSprite.hpp"
#include <Component/StringPhysics.hpp>
#include <Object/ObjectManager.hpp>
#include "Component/Physics.hpp"

String::String(Object* player1, Object* player2)
	:verticesCapacity(0)
{
	AddComponent(new StringSprite(this));
	// should ctor need three pointers?
	//string->AddComponent(new StringPhysics(string, object1, object2));
	AddComponent(new StringPhysics(this, player1, player2));

	
	vertices.push_back(player1->GetTranslation());
	vertices.push_back(player2->GetTranslation());
}

void String::Update(float dt)
{
    //const auto& physicsObject = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();

    //for (std::vector<vector2>::iterator it = vertices.begin(); it != vertices.end() - 1; it++)
    //{
    //    this->GetComponentByTemplate<StringPhysics>()->SetNormalVector(*it, *(it + 1));
    //        for (const auto& object : physicsObject)
    //        {
    //            if (object->GetComponentByTemplate<Physics>()->GetHasCollisionBox() == true)
    //            {
    //                this->GetComponentByTemplate<StringPhysics>()->SetObjectPoint(&*object);
    //                this->GetComponentByTemplate<StringPhysics>()->IsBendPointInstantiated(*it, *(it + 1), it+1);
    //            }
    //        }
    //}
	// Check -> collision
	// vertices draw - Il
}

std::vector<vector2>& String::GetVertices() noexcept
{
	return maxVertexSize;
}


