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
#include <Window/Demo.hpp>
#include <Graphics/StockShaders.hpp>
#include <Graphics/Color4ub.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/GL.hpp>
#include <matrix3.hpp>

void Demo::Init()
{
	using namespace Graphics;
	testMaterial.shader = &Graphics::SHADER::interpolated_colors();
	// send uniform matrix variable named "to_ndc"	// Should change arbitrary value into variable
	testMaterial.matrix3Uniforms["to_ndc"] =  MATRIX3::build_scale(2.f / 1920, 2.f / 1080);

	VertexLayoutDescription testLayout = SHADER::interpolated_colors_vertex_layout();

	Mesh triangle;
	triangle.SetPointListType(PointListPattern::Triangles);
	triangle.AddPoint( vector2{ 0.f, 100.f });
	triangle.AddPoint( vector2{ 100.f, 0.f });
	triangle.AddPoint( vector2{ -100.f, 0.f });
	triangle.AddColor(Color4ub{ 165 });

	testVertices.InitializeWithMeshAndLayout(triangle, testLayout);
}

void Demo::Update(float /*dt*/)
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
