/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Vertices.hpp
Author
    - Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

    Header file for Vertex functions
******************************************************************************/
#pragma once
#include <Graphics/VertexLayoutDescription.hpp>

namespace Graphics
{
    class Mesh;

    class [[nodiscard]] Vertices
    {
	public:
		static constexpr unsigned int NOT_GENERATED = 0U;
    public:
        Vertices() noexcept = default;
        Vertices(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept;
        ~Vertices() noexcept;
        Vertices(Vertices && other) noexcept;
        void operator=(Vertices&& other) noexcept;

        void InitializeWithMeshAndLayout(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept;
        void UpdateVerticesFromMesh(const Mesh& mesh);

        static void        Select(const Vertices& vertices);
        constexpr unsigned GetVerticesListPattern() const noexcept { return verticesListPattern; }
		constexpr int      GetVerticesCount() const noexcept { return static_cast<int>(verticesCount); }
		constexpr int      GetInstanceDataCount() const noexcept { return static_cast<int>(instanceDataCount); }
        static void        SelectNothing();

		VertexLayoutDescription GetLayout() const;
		unsigned int GetVerticesHandle() const;
		unsigned int GetDataBufferHandle() const;

    public:
        Vertices(const Vertices& other) = delete;
        void operator=(const Vertices& other) = delete;

    public:
        void DeleteVerticesOnGPU() noexcept;
        void WriteMeshDataToVertexBuffer(const Mesh& mesh) const noexcept;

    private:
        unsigned int            verticesHandle       = NOT_GENERATED;
        unsigned int            dataBufferHandle     = NOT_GENERATED;
		unsigned int			instanceDataBufferHandle = NOT_GENERATED;
        size_t                     verticesCount        = 0;
		size_t						instanceDataCount = 0;
        unsigned int            verticesListPattern  = 0;
		size_t                     bufferVertexCapacity = 0;
        VertexLayoutDescription layout{};
    };
}
