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
#include "Sprite.hpp"
#include <Object/Transform.hpp>
#include <Graphics/StockShaders.hpp>
#include <GL/glew.h>
#include <Object/Object.hpp>
#include <Graphics/GL.hpp>
#include <iostream>
#include <Window/Application.hpp>
#include <Component/Physics.hpp>

#pragma warning (push)
#pragma warning (disable : 4458)

Sprite::Sprite(Object* obj) noexcept
	: Component(obj), mesh(std::make_shared<Graphics::Mesh>()), vertices(std::make_shared<Graphics::Vertices>()), 
		material(std::make_shared<Graphics::material>()), texture(std::make_shared<Graphics::Texture>()),
		imageFilePath("../assets/textures/rect.png"), isBackground(false), isInstancing(false)
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

	mesh->AddTextureCoordinate(vector2{ 0.f });
	mesh->AddTextureCoordinate(vector2{ 1.f, 0.f });
	mesh->AddTextureCoordinate(vector2{ 1.f });
	mesh->AddTextureCoordinate(vector2{ 0.f, 1.f });

	SetImage(imageFilePath);
	vertices->InitializeWithMeshAndLayout(*mesh.get(), Graphics::SHADER::textured_vertex_layout());
}

void Sprite::Update(float /*dt*/)
{
	if (Physics* p = owner->GetComponentByTemplate<Physics>())
	{
		Graphics::Color4f currentColor = GetColor();
		SetColor(Graphics::Color4f{static_cast<float>(!p->IsCollided()), currentColor.green, currentColor.blue, currentColor.alpha});
	}
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
bool Sprite::SetImage(const std::filesystem::path& filepath) noexcept
{
	if (texture->LoadFromPNG(filepath))
	{
		imageFilePath = filepath.string();
		Graphics::Texture* txt = texture.get();
		const Graphics::texture_uniform container{ txt, 0 };
		material->textureUniforms[Graphics::SHADER::Uniform_Texture] = container;
		material->vector2Uniforms[Graphics::SHADER::Uniform_ImageSize] = vector2{ float(txt->GetWidth()), float(txt->GetHeight()) };
	}
	else
	{
		std::cout << "Image Loading Failed!\n";
		std::cout << "Owner object name is " << owner->GetObjectName() << std::endl;
		std::cout << "Path is " << filepath << std::endl;
        return false;
	}
    return true;
}

void Sprite::SetIsBackground(bool isBackGround) noexcept
{
	isBackground = isBackGround;
	if(isBackground)
	{
		material->shader = &Graphics::SHADER::background();
	}
}

void Sprite::ExpandTextureCoordinate(float scale) noexcept
{
	mesh->ClearTextureCoordinates();
	mesh->AddTextureCoordinate(vector2{ 0.f });
	mesh->AddTextureCoordinate(vector2{ 1.f * scale, 0.f });
	mesh->AddTextureCoordinate(vector2{ 1.f * scale});
	mesh->AddTextureCoordinate(vector2{ 0.f, 1.f *scale});
	vertices->InitializeWithMeshAndLayout(*mesh.get(), Graphics::SHADER::textured_vertex_layout());
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

const Graphics::Color4f& Sprite::GetColor() const noexcept
{
	return material->color4fUniforms[Graphics::SHADER::Uniform_Color];
}

const std::string& Sprite::GetImagePath() const noexcept
{
	return imageFilePath;
}

unsigned Sprite::GetTextureHandle() const noexcept
{
	return texture->GetTextureHandle();
}

unsigned* Sprite::GetRefTextureHandle() noexcept
{
	return texture->GetRefTextureHandle();
}

void Sprite::SetInstancingMode(bool isOn) noexcept
{
	isInstancing = isOn;

	if (isInstancingMode())
	{
		vertices->InitializeWithMeshAndLayout(*mesh, Graphics::SHADER::instancing_vertex_layout());
		material->shader = &Graphics::SHADER::Instancing();
	}
}

bool Sprite::isInstancingMode() const noexcept
{
	return isInstancing;
}

void Sprite::UpdateInstancingValues(std::vector<matrix3>* matrices, float depth) const noexcept
{
	if (isInstancing == false)
	{
		static_assert("UpdateInstancingValues is called in only instancing mode");
	}
	
	mesh->ChangeReferenceInstancedMatrices(matrices);
	vertices->UpdateVerticesFromMesh(*mesh);

	material->floatUniforms[Graphics::SHADER::Uniform_Depth] = depth;
}
#pragma warning (pop)
