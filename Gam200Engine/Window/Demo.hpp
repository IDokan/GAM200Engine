/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Demo.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Header file for Demo graphics code
******************************************************************************/
#pragma once

#include <Graphics/Material.hpp>
#include <Graphics/Shader.hpp>
#include "Graphics/Vertices.hpp"

class Demo
{
public:
	Demo() = default;
	virtual ~Demo() = default;

	void Init();
	void Update(float dt);
	void Clear();

	bool ShouldClose() const noexcept;

	void Draw();

private:
	bool isDone = false;

	Graphics::material testMaterial;
	Graphics::Vertices testVertices;
};

