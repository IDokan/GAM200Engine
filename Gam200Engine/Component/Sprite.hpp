/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Sprite.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.14.2019

	Header file for Graphic Component
******************************************************************************/
#pragma once

class Component;

namespace Graphics
{
	class Mesh;
	class Vertices;
	struct material;
}

class Sprite :
	public Component
{
public:
	Sprite();
	virtual ~Sprite();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Clear() override;

	void SetColor(const Graphics::Color4f& color) noexcept;

private:
	Graphics::Color4f color;

	Graphics::Mesh mesh;
	Graphics::Vertices vertices;
	Graphics::material material;
};

