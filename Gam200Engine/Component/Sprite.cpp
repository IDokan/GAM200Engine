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
#include <Graphics/Vertices.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Texture.hpp>
#include "Sprite.hpp"
#include <Object/Transform.hpp>
#include <Graphics/StockShaders.hpp>
#include <GL/glew.h>
#include <Object/Object.hpp>
#include "Graphics/GL.hpp"
#include <iostream>
#include "Application.hpp"

Sprite::Sprite(Object* obj) noexcept
	: Component(obj), mesh(std::make_shared<Graphics::Mesh>()), vertices(std::make_shared<Graphics::Vertices>()), 
		material(std::make_shared<Graphics::material>()), texture(std::make_shared<Graphics::Texture>())
{
	mesh->Clear();
}

void Sprite::Init()
{
	material->shader = &Graphics::SHADER::textured();
	const auto& windowSize = Application::GetApplication()->GetWindowSize;
	// TODO: What if window size is changed?
	material->matrix3Uniforms[Graphics::SHADER::Uniform_ToNDC] = MATRIX3::build_scale(2.f / windowSize.x, 2.f / windowSize.y);


	mesh->SetPointListType(Graphics::PointListPattern::TriangleFan);

	mesh.get()->AddPoint(vector2{ -0.5f, 0.5f });
	mesh.get()->AddPoint(vector2{0.5f });
	mesh.get()->AddPoint(vector2{ 0.5f, -0.5f });
	mesh.get()->AddPoint(vector2{ -0.5f });

	material->color4fUniforms[Graphics::SHADER::Uniform_Color] = Graphics::Color4f{1.f};

	// TODO: To Modify for animation or special shader
	mesh->AddTextureCoordinate(vector2{ 0.f, 1.f });
	mesh->AddTextureCoordinate(vector2{ 1.f });
	mesh->AddTextureCoordinate(vector2{ 1.f, 0.f });
	mesh->AddTextureCoordinate(vector2{ 0.f});

	SetImage("../texture/rect.png");
	vertices->InitializeWithMeshAndLayout(*mesh.get(), Graphics::SHADER::textured_vertex_layout());
}

void Sprite::Update(float /*dt*/)
{
}

void Sprite::Clear()
{
	mesh->Clear();
}

void Sprite::SetColor(const Graphics::Color4f& color) noexcept
{
	material->color4fUniforms[Graphics::SHADER::Uniform_Color] = color;
}

// TODO: In order to improve engine, I should make a sprite storage to get a already loaded image file.
void Sprite::SetImage(const std::filesystem::path& filepath) noexcept
{
	if (texture->LoadFromPNG(filepath))
	{
		const Graphics::texture_uniform container{ texture.get(), 0 };
		material->textureUniforms[Graphics::SHADER::Uniform_Texture] = container;
	}
	else
	{
		std::cout << "Image Loading Failed!\n";
	}
}

void Sprite::UpdateUniforms(const matrix3& toNDC, float depth) noexcept
{
	material->matrix3Uniforms[Graphics::SHADER::Uniform_ToNDC] = toNDC;
	material->floatUniforms[Graphics::SHADER::Uniform_Depth] = depth;
}

Graphics::Vertices* Sprite::GetVertices() const noexcept
{
	return vertices.get();
}

Graphics::material* Sprite::GetMaterial() const noexcept
{
	return material.get();
}
