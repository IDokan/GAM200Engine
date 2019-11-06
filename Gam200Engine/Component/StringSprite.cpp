/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringSprite.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 11.04.2019

	Header file for Sprite implementation for string graphics
******************************************************************************/
#include <Component/StringSprite.hpp>

StringSprite::StringSprite(Object* obj) noexcept
	: Sprite(obj)
{
}

void StringSprite::Init()
{
	Sprite::Init();

	SetImage("../assets/textures/rope.png");
}

void StringSprite::Update(float dt)
{
	Sprite::Update(dt);
}

void StringSprite::Clear()
{
	Sprite::Clear();
}
