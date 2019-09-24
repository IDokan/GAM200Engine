/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Demo.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	code file for Demo graphics code
******************************************************************************/
#include "Demo.hpp"
#include <Graphics/StockShaders.hpp>
#include <Graphics/Color4ub.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/GL.hpp>
#include <matrix3.hpp>

void Demo::Init()
{
	using namespace Graphics;
	testMaterial.shader = &Graphics::SHADER::solid_color();
	// send uniform matrix variable named "to_ndc"
	testMaterial.color4fUniforms["color"] = to_color4f(Color4ub{ 255, 0, 0 });
	testMaterial.matrix3Uniforms["to_ndc"] = Math::MATRIX3::build_scale(2.f / 1920, 2.f / 1080);

	VertexLayoutDescription testLayout = SHADER::solid_color_vertex_layout();

	Mesh triangle;
	triangle.SetPointListType(PointListPattern::Triangles);
	triangle.AddPoint(Math::vector2{ 0.f, 100.f });
	triangle.AddPoint(Math::vector2{ 100.f, 0.f });
	triangle.AddPoint(Math::vector2{ -100.f, 0.f });

	testVertices.InitializeWithMeshAndLayout(triangle, testLayout);
}

void Demo::Update(float dt)
{
}

void Demo::Clear()
{
}

bool Demo::ShouldClose() const noexcept
{
	return isDone;
}

void Demo::Draw()
{
	Graphics::GL::begin_drawing();

	Graphics::GL::draw(testVertices, testMaterial);

	Graphics::GL::end_drawing();
}
