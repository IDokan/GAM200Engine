/*  1. sinil.gang
 *  2. Shapes Programming Assignment
 *  3. CS230
 *  4. Spring 2019
 */
#include <Graphics/Mesh.hpp>
#include <Graphics/VertexLayoutDescription.hpp>
#include <Graphics/Vertices.hpp>
#include <Graphics/glCheck.hpp>
#include <GL/glew.h>
#include <cassert>

namespace Graphics
{
	int FindVerticesListPattern(const Mesh& mesh)
	{
		switch (mesh.GetPointListPattern())
		{
		case PointListPattern::Lines:
			return GL_LINES;
		case PointListPattern::LineStrip:
			return GL_LINE_STRIP;
		case PointListPattern::LineLoop:
			return GL_LINE_LOOP;
		case PointListPattern::Triangles:
			return GL_TRIANGLES;
		case PointListPattern::TriangleStrip:
			return GL_TRIANGLE_STRIP;
		case PointListPattern::TriangleFan:
			return GL_TRIANGLE_FAN;
		default:
			return 0;
		}
	}

	Vertices::Vertices(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept
	{
		InitializeWithMeshAndLayout(mesh, vertex_layout);
	}

	Vertices::~Vertices() noexcept
	{
		DeleteVerticesOnGPU();
	}

	Vertices::Vertices(Vertices&& other) noexcept
	{
		verticesHandle = other.verticesHandle;
		dataBufferHandle = other.dataBufferHandle;
		verticesCount = other.verticesCount;
		verticesListPattern = other.verticesListPattern;
		layout = other.layout;
		bufferVertexCapacity = other.bufferVertexCapacity;
		other.verticesHandle = 0;
		other.dataBufferHandle = 0;
		other.verticesCount = 0;
		other.bufferVertexCapacity = 0;
	}

	void Vertices::operator=(Vertices&& other) noexcept
	{
		if (this == &other)
			return;
		DeleteVerticesOnGPU();
		verticesHandle = other.verticesHandle;
		dataBufferHandle = other.dataBufferHandle;
		verticesCount = other.verticesCount;
		verticesListPattern = other.verticesListPattern;
		layout = other.layout;
		bufferVertexCapacity = other.bufferVertexCapacity;
		other.verticesHandle = 0;
		other.dataBufferHandle = 0;
		other.verticesCount = 0;
		other.bufferVertexCapacity = 0;
	}

	void Vertices::InitializeWithMeshAndLayout(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept
	{
		DeleteVerticesOnGPU();

		layout = vertex_layout;

		verticesListPattern = FindVerticesListPattern(mesh);
		verticesCount = static_cast<int>(mesh.GetPointCount());
		bufferVertexCapacity = verticesCount;

		glCheck(glGenVertexArrays(1, &verticesHandle));

		glCheck(glGenBuffers(1, &dataBufferHandle));

		glCheck(glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle));

		Select(*this);

		glCheck(glBufferData(GL_ARRAY_BUFFER, (verticesCount * layout.GetVertexSize()), nullptr, GL_STATIC_DRAW));

		layout.SendVertexDescriptionToOpenGL();

		WriteMeshDataToVertexBuffer(mesh);

		SelectNothing();
	}

	void Vertices::UpdateVerticesFromMesh(const Mesh& mesh)
	{
		if (static_cast<int>(mesh.GetPointCount()) <= bufferVertexCapacity)
		{
			verticesCount = static_cast<unsigned int>(mesh.GetPointCount());

			verticesListPattern = FindVerticesListPattern(mesh);
		}
		else
		{
			DeleteVerticesOnGPU();
			InitializeWithMeshAndLayout(mesh, layout);
		}

		WriteMeshDataToVertexBuffer(mesh);
	}

	void Vertices::Select(const Vertices& vertices)
	{
		glBindVertexArray(vertices.verticesHandle);

	}

	void Vertices::SelectNothing()
	{
		glCheck(glBindVertexArray(NULL));
	}

	void Vertices::DeleteVerticesOnGPU() noexcept
	{
		if (verticesHandle != 0)
		{
			glCheck(glDeleteBuffers(1, &verticesHandle));
			verticesHandle = 0;
			glCheck(glDeleteVertexArrays(1, &dataBufferHandle));
		}
	}

	void Vertices::WriteMeshDataToVertexBuffer(const Mesh& mesh) const noexcept
	{
		if (mesh.GetPointCount() == 0)
		{
			return;
		}

		Select(*this);

		glCheck(glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle));
		void* pointer;
		glCheck(pointer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

		GLuint offset = 0;
		char* destination = nullptr;
		for (std::size_t index = 0; index < mesh.GetPointCount(); ++index)
		{
			for (const auto& element : layout.GetFieldTypes())
			{
				destination = reinterpret_cast<char*>(pointer) + offset;
				switch (element)
				{
				case VertexLayoutDescription::Position2WithFloats:
				{
					vector2 position = mesh.GetPoint(index);
					const unsigned long long size = sizeof(position);
					std::memcpy(destination, &position, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::TextureCoordinates2WithFloats:
				{
					vector2 textureCoordinate = mesh.GetTextureCoordinate(index);
					const unsigned long long size = sizeof(textureCoordinate);
					std::memcpy(destination, &textureCoordinate, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::Color4WithUnsignedBytes:
				{
					Color4ub color = mesh.GetColor(index);
					const unsigned long long size = sizeof(color);
					std::memcpy(destination, &color, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::InstancedMatrix9WithFloats1:
				{
					vector3 instancedMatrix = mesh.GetInstancedMatrix(index).column0;
					const unsigned long long size = sizeof(instancedMatrix);
					std::memcpy(destination, &instancedMatrix, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::InstancedMatrix9WithFloats2:
				{
					vector3 instancedMatrix = mesh.GetInstancedMatrix(index).column1;
					const unsigned long long size = sizeof(instancedMatrix);
					std::memcpy(destination, &instancedMatrix, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::InstancedMatrix9WithFloats3:
				{
					vector3 instancedMatrix = mesh.GetInstancedMatrix(index).column2;
					const unsigned long long size = sizeof(instancedMatrix);
					std::memcpy(destination, &instancedMatrix, size);
					offset += size;
					break;
				}
				default:;
				}
			}
		}

		glCheck(glUnmapBuffer(GL_ARRAY_BUFFER));

		SelectNothing();
	}
}
