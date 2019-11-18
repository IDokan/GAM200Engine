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
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Graphics/StockShaders.hpp>

StringSprite::StringSprite(Object* obj) noexcept
	: Sprite(obj), stringOwner(dynamic_cast<String*>(obj)), stringHeight(5.f)
{
}

void StringSprite::Init()
{
	Sprite::Init();

	SetImage("../assets/textures/rope.png");
	owner->SetDepth(-500.f);

	mesh->ClearPoints();

	size_t maxVertexSize = stringOwner->GetVertexSize();

	for (size_t i = 0; i < maxVertexSize; ++i)
	{
		// 0 and 1 are an indicator that that point is higher or lower.
		float index = static_cast<float>(i);
		mesh->AddPoint(vector2{ index, 0 });
		mesh->AddPoint(vector2{ index, 1 });
	}

	material->shader = &Graphics::SHADER::StringShader();
}

void StringSprite::Update(float dt)
{
	Sprite::Update(dt);
}

void StringSprite::Clear()
{
	Sprite::Clear();
}

void StringSprite::UpdateUniforms()
{
	
}

float StringSprite::GetStringHeight() const noexcept
{
	return stringHeight;
}

void StringSprite::SetStringHeight(float height) noexcept
{
	stringHeight = height;
}
