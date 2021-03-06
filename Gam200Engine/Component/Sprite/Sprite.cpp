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

#include <Systems/Input.hpp>

#pragma warning (push)
#pragma warning (disable : 4458)

Sprite::Sprite(Object* obj) noexcept
	: Component(obj), mesh(std::make_shared<Graphics::Mesh>()), vertices(std::make_shared<Graphics::Vertices>()), 
		material(std::make_shared<Graphics::material>()), texture(std::make_shared<Graphics::Texture>()),
		imageFilePath("../assets/textures/rect.png"), isBackground(false), isInstancing(InstanceModes::OFF), shouldUpdateVertices (false)
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

void Sprite::Update(float dt)
{
	if (shouldUpdateVertices == true || input.IsKeyTriggered(GLFW_KEY_9)
		 /*|| vertices->GetVerticesHandle() > vertices->GetDataBufferHandle()*/)
	{
		vertices->InitializeWithMeshAndLayout(*mesh.get(), vertices->GetLayout());
		shouldUpdateVertices = false;
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

void Sprite::ExpandTextureCoordinate(vector2 scale) noexcept
{
	mesh->ClearTextureCoordinates();
	mesh->AddTextureCoordinate(vector2{ 0.f });
	mesh->AddTextureCoordinate(vector2{ scale.x, 0.f });
	mesh->AddTextureCoordinate(scale);
	mesh->AddTextureCoordinate(vector2{ 0.f, scale.y });
	vertices->InitializeWithMeshAndLayout(*mesh.get(), Graphics::SHADER::textured_vertex_layout());
}

void Sprite::UpdateUniforms(const matrix3& toNDC, float depth) noexcept
{
	material->matrix3Uniforms[Graphics::SHADER::Uniform_ToNDC] = toNDC;
	material->floatUniforms[Graphics::SHADER::Uniform_Depth] = depth / 5000.f;
}

Graphics::Mesh * Sprite::GetMesh() const noexcept
{
	return mesh.get();
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

void Sprite::SetInstancingMode(InstanceModes isOn) noexcept
{
	isInstancing = isOn;

	switch (isInstancing)
	{
	case Sprite::InstanceModes::OFF:
		break;
	case Sprite::InstanceModes::ON:
		vertices->InitializeWithMeshAndLayout(*mesh, Graphics::SHADER::instancing_vertex_layout());
		material->shader = &Graphics::SHADER::Instancing();
		break;
	case Sprite::InstanceModes::ADVANCED:
		vertices->InitializeWithMeshAndLayout(*mesh, Graphics::SHADER::Advanced_instancing_vertex_layout());
		material->shader = &Graphics::SHADER::AdvancedInstancing();
		break;
	default:
		break;
	}
}

bool Sprite::isInstancingMode() const noexcept
{
	if (isInstancing == InstanceModes::OFF)
	{
		return false;
	}
	return true;
}

void Sprite::UpdateInstancingValues(std::vector<matrix3>* matrices, float depth) const noexcept
{
	std::vector < Graphics::Color4ub> colors;
	colors.emplace_back(Graphics::Color4ub{ 255 });

	std::vector <vector2> textureCoordinates;
	textureCoordinates.emplace_back(vector2{ 0.f });
	textureCoordinates.emplace_back(vector2{ 1.f, 0.f });
	textureCoordinates.emplace_back(vector2{ 1.f });
	textureCoordinates.emplace_back(vector2{ 0.f, 1.f });

	switch (isInstancing)
	{
	case Sprite::InstanceModes::OFF:
		static_assert("UpdateInstancingValues is called in only instancing mode");
		break;
	case Sprite::InstanceModes::ON:
		mesh->ChangeReferenceInstancedMatrices(matrices);
		vertices->InitializeWithMeshAndLayout(*mesh, Graphics::SHADER::instancing_vertex_layout());

		material->floatUniforms[Graphics::SHADER::Uniform_Depth] = depth;
		break;
	case Sprite::InstanceModes::ADVANCED:
		mesh->ChangeReferenceInstancedMatrices(matrices);
		mesh->ChangeReferenceInstancedColors(&colors);
		mesh->ChangeReferenceInstancedTextureCoordinates(&textureCoordinates);
		vertices->InitializeWithMeshAndLayout(*mesh, Graphics::SHADER::Advanced_instancing_vertex_layout());

		material->floatUniforms[Graphics::SHADER::Uniform_Depth] = depth / 5000.f;
		break;
	default:
		break;
	}
}
void Sprite::UpdateInstancingValues(std::vector<vector2>* textureCoordinates, std::vector<Graphics::Color4ub>* colors, std::vector<matrix3>* matrices, float depth) const noexcept
{
	switch (isInstancing)
	{
	case Sprite::InstanceModes::OFF:
		static_assert("UpdateInstancingValues is called in only instancing mode");
		break;
	case Sprite::InstanceModes::ON:
		mesh->ChangeReferenceInstancedMatrices(matrices);
		vertices->InitializeWithMeshAndLayout(*mesh, Graphics::SHADER::instancing_vertex_layout());

		material->floatUniforms[Graphics::SHADER::Uniform_Depth] = depth;
		break;
	case Sprite::InstanceModes::ADVANCED:
		mesh->ChangeReferenceInstancedMatrices(matrices);
		mesh->ChangeReferenceInstancedColors(colors);
		mesh->ChangeReferenceInstancedTextureCoordinates(textureCoordinates);
		vertices->InitializeWithMeshAndLayout(*mesh, Graphics::SHADER::Advanced_instancing_vertex_layout());

		material->floatUniforms[Graphics::SHADER::Uniform_Depth] = depth / 5000.f;
		break;
	default:
		break;
	}
}
void Sprite::SetShouldUpdateVertices(bool should)
{
	shouldUpdateVertices = should;
}
void Sprite::DeleteVertices()
{
	vertices->DeleteVerticesOnGPU();
}
void Sprite::GenerateVertices()
{
	vertices->InitializeWithMeshAndLayout(*mesh.get(), vertices->GetLayout());
}
#pragma warning (pop)
