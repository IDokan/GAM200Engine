/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Mesh.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Header file for Mesh
******************************************************************************/
#pragma once
#include <Graphics/Color4ub.hpp>
#include <Vector2.hpp>
#include <cstddef>
#include <vector>
#include <matrix3.hpp>

namespace Graphics
{
    enum class [[nodiscard]] PointListPattern
    {
        Lines, LineStrip, LineLoop, Triangles, TriangleStrip, TriangleFan
    };

    class [[nodiscard]] Mesh
    {
    public:
        std::size_t GetPointCount() const noexcept;
         vector2     GetPoint(std::size_t index) const noexcept;
        Graphics::Color4ub    GetColor(std::size_t index = 0) const noexcept;
         vector2     GetTextureCoordinate(std::size_t index) const noexcept;

        PointListPattern GetPointListPattern() const noexcept;
        void             SetPointListType(PointListPattern type) noexcept;

        void AddColor(Graphics::Color4ub color) noexcept;
        void AddPoint( vector2 point) noexcept;
        void AddTextureCoordinate( vector2 texture_coordinate) noexcept;

        void ClearColors() noexcept;
        bool HasMoreThanOneColor() const noexcept;

        void ClearTextureCoordinates() noexcept;
        void ClearPoints() noexcept;
        void Clear() noexcept;

        // Instancing functions
        std::size_t GetInstancedMatrixCount() const noexcept;
        matrix3 GetInstancedMatrix(std::size_t index) const noexcept;
        std::vector <matrix3>* GetPointerToInstancedMatrix() const noexcept;
        bool IsInstanceMatrixInvalid() const noexcept;
        void ChangeReferenceInstancedMatrices(std::vector<matrix3>* matrix) noexcept;

        std::size_t GetInstancedTextureCoordinateCount() const noexcept;
        vector2 GetInstancedTextureCoordinate(std::size_t index) const noexcept;
        std::vector<vector2>* GetPointerToInstancedTextureCoordinate() const noexcept;
        bool IsInstanceTextureCoordinateInvalid() const noexcept;
        void ChangeReferenceInstancedTextureCoordinates(std::vector<vector2>* newReference) noexcept;

        std::size_t GetInstancedColorCount() const noexcept;
        Graphics::Color4ub GetInstancedColors(std::size_t index) const noexcept;
        std::vector<Graphics::Color4ub>* GetPointerToInstancedColors() const noexcept;
        bool IsInstancedColorsInvalid() const noexcept;
        void ChangeReferenceInstancedColors(std::vector<Graphics::Color4ub>* newReference) noexcept;

    private:
        std::vector<vector2>  points{};
        std::vector<Graphics::Color4ub> colors{};
        std::vector<vector2>  textureCoordinates{};
        PointListPattern      pointListType = PointListPattern::Lines;

		/* Below variables are storage to save data to implement with Instancing */
		std::vector <matrix3>* instancedMatrices = nullptr;
        std::vector<vector2>* instancedTextureCoordinates = nullptr;
        std::vector <Graphics::Color4ub>* instancedColors = nullptr;
    };

    namespace MESH
    {
        Mesh create_circle(float radius = 1, Graphics::Color4ub color = Graphics::Color4ub{255}, std::size_t point_count = 30) noexcept;
        Mesh create_wire_circle(float radius = 1, Graphics::Color4ub color = Graphics::Color4ub{255},
                                std::size_t point_count = 30) noexcept;
        Mesh create_box(float dimension = 1, Graphics::Color4ub color = Graphics::Color4ub{255}) noexcept;
        Mesh create_rectangle(float width = 1, float height = 1, Graphics::Color4ub color = Graphics::Color4ub{255}) noexcept;
        Mesh create_wire_rectangle(float width = 1, float height = 1, Graphics::Color4ub color = Graphics::Color4ub{255}) noexcept;
        Mesh create_wire_box(float dimension = 1, Graphics::Color4ub color = Graphics::Color4ub{255}) noexcept;
        Mesh create_line( vector2 a = {0, 0},  vector2 b = {1, 0}, Graphics::Color4ub color = Graphics::Color4ub{255}) noexcept;
    }
}
