/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Sprite.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.14.2019

	Source file for Graphic Component
******************************************************************************/
#include <Component/Component.hpp>
#include <Graphics/Mesh.hpp>
#include "Sprite.hpp"
#include <Object/Transform.hpp>
#include <Graphics/StockShaders.hpp>
#include <GL/glew.h>
#include <Object/Object.hpp>
#include "Graphics/GL.hpp"

// Helper function to update mesh
void UpdateMeshPoint(const Transform& transform, Graphics::Mesh& mesh) noexcept
{
	mesh.ClearPoints();

	const int rectSize = 4;
	
	vector3 rectangle[rectSize] = {
		vector3{-0.5f, 0.5f, 0.f},
		vector3{0.5f, 0.5f, 0.f},
		vector3{0.5f, -0.5f, 0.f},
		vector3{-0.5f, -0.5f, 0.f}
	};

	const matrix3 tmp = transform.GetModelToWorld();
	for (int i = 0; i < rectSize; i++)
	{
		rectangle[i] = tmp * rectangle[i];
		mesh.AddPoint(vector2{ rectangle[i].x, rectangle[i].y });
	}
}

Sprite::Sprite(Object* obj) noexcept
	: Component(obj)
{
	mesh.Clear();
}

void Sprite::Init()
{
	const Transform transform = owner->GetTransform();
	material.shader = &Graphics::SHADER::textured();
	material.matrix3Uniforms["to_ndc"] = MATRIX3::build_scale(2.f / 1920.f, 2.f / 1080.f);
	material.floatUniforms["to_depth"] = transform.CalculateWorldDepth();

	mesh.SetPointListType(Graphics::PointListPattern::TriangleFan);
	
	UpdateMeshPoint(transform, mesh);

	material.color4fUniforms["color"] = Graphics::Color4f{1.f};

	// TODO: To Modify for animation or special shader
	mesh.AddTextureCoordinate(vector2{ 0.f, 1.f });
	mesh.AddTextureCoordinate(vector2{ 1.f });
	mesh.AddTextureCoordinate(vector2{ 1.f, 0.f });
	mesh.AddTextureCoordinate(vector2{ 0.f});

	//SetImage("texture/rect.png");

	vertices.InitializeWithMeshAndLayout(mesh, Graphics::SHADER::textured_vertex_layout());
}

void Sprite::Update(float /*dt*/)
{
	Transform transform = owner->GetTransform();

	if (transform.GetIsChanged())
	{
		UpdateMeshPoint(transform, mesh);

		vertices.UpdateVerticesFromMesh(mesh);
	}

	// TODO: Should Change where Draw
	//Graphics::GL::begin_drawing();
	//Graphics::GL::draw(vertices, material);
	//Graphics::GL::end_drawing();
}

void Sprite::Clear()
{
	mesh.Clear();
}

void Sprite::SetColor(const Graphics::Color4f& color) noexcept
{
	material.color4fUniforms["color"] = color;
}

//void Sprite::SetImage(const std::filesystem::path& filepath) noexcept
//{
//	texture.LoadFromPNG(filepath);
//	Graphics::texture_uniform container{ &texture, 0 };
//	material.textureUniforms["texture_to_sample"] = container;
//}
