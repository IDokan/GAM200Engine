/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Button.cpp
Author
		jjwon6218@gmail.com
Creation Date: March 16th, 2020

	Source file for buttons in menu scene
******************************************************************************/
#include <Object/Button.hpp>
#include <Object/DepthStandard.hpp>
#include <Component/Physics.hpp>

Button::Button(ButtonIdentifier button, const Transform& buttonTransformData)
	:Object(), id(button)
{
	Object::SetTranslation(buttonTransformData.GetTranslation());
	SetScale(buttonTransformData.GetScale());
	SetRotation(buttonTransformData.GetRotation());
	SetDepth(Depth_Standard::Button);

	Object::AddComponent(new Physics(this));
	GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, Physics::ObjectType::RECTANGLE);
	Object::SetObjectType(ObjectType::BUTTON);
}
