/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Mesh.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Source file for Mesh
******************************************************************************/
#include <Graphics/Mesh.hpp>
#include <Angle.hpp>
#include <cmath>

namespace Graphics
{
    void AddRectanglePoint(Graphics::Mesh& mesh, float width, float height)
    {
        float x = width / 2.f;
        float y = height / 2.f;
        mesh.AddPoint( vector2{-x, -y});
        mesh.AddPoint( vector2{-x, y});
        mesh.AddPoint( vector2{x, y});
        mesh.AddPoint( vector2{x, -y});
    };

    void AddBoxPoint(Graphics::Mesh& mesh, float dimension)
    {
        float point = dimension / 2.f;
        mesh.AddPoint( vector2{-point});
        mesh.AddPoint( vector2{-point, point});
        mesh.AddPoint( vector2{point});
        mesh.AddPoint( vector2{point, -point});
    };

    void AddTexturePoint(Graphics::Mesh& mesh)
    {
        mesh.AddTextureCoordinate( vector2{0.f, 1.f});
        mesh.AddTextureCoordinate( vector2{0.f});
        mesh.AddTextureCoordinate( vector2{1.f, 0.f});
        mesh.AddTextureCoordinate( vector2{1.f});
    }

    std::size_t Mesh::GetPointCount() const noexcept
    {
        return points.size();
    }

     vector2 Graphics::Mesh::GetPoint(std::size_t index) const noexcept
    {
        return points.at(index);
    }
    Color4ub Graphics::Mesh::GetColor(std::size_t index) const noexcept 
    {
        if (colors.empty())
        {
            return Color4ub{0};
        }
        if (index >= colors.size())
        {
            return colors.back();
        }
        return colors.at(index);
    }
     vector2 Graphics::Mesh::GetTextureCoordinate(std::size_t index) const noexcept
    {
        if (textureCoordinates.empty())
        {
            return  vector2{0.f};
        }
        else if (index >= textureCoordinates.size())
        {
            return textureCoordinates.back();
        }
        return textureCoordinates.at(index);
    }

    matrix3 Mesh::GetInstancedMatrix(std::size_t index) const noexcept
    {
	    if (instancedMatrices->empty())
	    {
			return matrix3{ vector3{0.f}, vector3{0.f}, vector3{0.f} };
	    }
		else if	(index >= instancedMatrices->size())
		{
			return instancedMatrices->back();
		}
	    else
	    {
			return instancedMatrices->at(index);
	    }
    }

    PointListPattern Graphics::Mesh::GetPointListPattern() const noexcept { return pointListType; }
    void             Graphics::Mesh::SetPointListType(PointListPattern type) noexcept
    { 
        pointListType = type;
    }
    void             Graphics::Mesh::AddColor(Color4ub color) noexcept
    { colors.push_back(color);
    }
    void Graphics::Mesh::AddPoint( vector2 point) noexcept
    { points.push_back(point);
    }
    void Graphics::Mesh::AddTextureCoordinate( vector2 texture_coordinate) noexcept
    {
        textureCoordinates.push_back(texture_coordinate);
    }

    void Mesh::ChangeReferenceInstancedMatrices(std::vector<matrix3>* matrix) noexcept
    {
		instancedMatrices = matrix;
    }

    void Graphics::Mesh::ClearColors() noexcept
    { colors.clear();
    }
    bool Graphics::Mesh::HasMoreThanOneColor() const noexcept
    {
        return (colors.size() > 1);
    }

    void Graphics::Mesh::ClearTextureCoordinates() noexcept
    { textureCoordinates.clear();
    }

    void Mesh::ClearPoints() noexcept
    { points.clear();
    }

    void Mesh::Clear() noexcept
    {
        ClearPoints();
        ClearColors();
        ClearTextureCoordinates();
    }

    Mesh MESH::create_circle(float radius, Color4ub color, std::size_t point_count) noexcept
    { 
        Mesh circle;
        circle.SetPointListType(PointListPattern::TriangleFan);
        circle.AddColor(color);

         circle.AddPoint( vector2{0.f});

        float temp = MATH::TWO_PI / point_count;

        for (std::size_t count = 0; count <= point_count; ++count)
        {
            circle.AddPoint(
                 vector2{radius * cos((temp * count) - MATH::HALF_PI), radius * sin((temp * count) - MATH::HALF_PI)});
        }

        return circle;
    }
    Mesh MESH::create_wire_circle(float radius, Color4ub color, std::size_t point_count) noexcept
    {
        Mesh circle;
        circle.SetPointListType(PointListPattern::LineLoop);
        circle.AddColor(color);

        float temp = MATH::TWO_PI / point_count;

        for (std::size_t count = 0; count < point_count; ++count)
        {
            circle.AddPoint(
                 vector2{radius * cos((temp * count) - MATH::HALF_PI), radius * sin((temp * count) - MATH::HALF_PI)});
        }

        return circle;
    }
    Mesh MESH::create_box(float dimension, Color4ub color) noexcept
    { 
        return create_rectangle(dimension, dimension, color);
    }
    Mesh MESH::create_rectangle(float width, float height, Color4ub color) noexcept
    {
        Mesh rectangle;
        rectangle.SetPointListType(PointListPattern::TriangleFan);
        rectangle.AddColor(color);

        AddRectanglePoint(rectangle, width, height);

        AddTexturePoint(rectangle);

        return rectangle;
    }
    Mesh MESH::create_wire_rectangle(float width, float height, Color4ub color) noexcept
    {
        Mesh rectangle;
        rectangle.SetPointListType(PointListPattern::LineLoop);
        rectangle.AddColor(color);

        AddRectanglePoint(rectangle, width, height);

        return rectangle;
    }
    Mesh MESH::create_wire_box(float dimension, Color4ub color) noexcept
    {
        return create_wire_rectangle(dimension, dimension, color);
    }
    Mesh MESH::create_line( vector2 a,  vector2 b, Color4ub color) noexcept
    { 
        Mesh line;
        line.SetPointListType(PointListPattern::Lines);
        line.AddColor(color);
        line.AddPoint(a);
        line.AddPoint(b);

        return line;
    }
}
