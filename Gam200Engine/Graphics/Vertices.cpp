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
		instanceDataBufferHandle = other.instanceDataBufferHandle;
		verticesCount = other.verticesCount;
		instanceDataCount = other.instanceDataCount;
		verticesListPattern = other.verticesListPattern;
		bufferVertexCapacity = other.bufferVertexCapacity;
		layout = other.layout;
		other.verticesHandle = 0;
		other.dataBufferHandle = 0;
		other.instanceDataBufferHandle = 0;
		other.verticesCount = 0;
		other.instanceDataCount = 0;
		other.verticesListPattern = 0;
		other.bufferVertexCapacity = 0;
	}

	void Vertices::operator=(Vertices&& other) noexcept
	{
		if (this == &other)
			return;
		DeleteVerticesOnGPU();
		verticesHandle = other.verticesHandle;
		dataBufferHandle = other.dataBufferHandle;
		instanceDataBufferHandle = other.instanceDataBufferHandle;
		verticesCount = other.verticesCount;
		instanceDataCount = other.instanceDataCount;
		verticesListPattern = other.verticesListPattern;
		bufferVertexCapacity = other.bufferVertexCapacity;
		layout = other.layout;
		other.verticesHandle = 0;
		other.dataBufferHandle = 0;
		other.instanceDataBufferHandle = 0;
		other.verticesCount = 0;
		other.instanceDataCount = 0;
		other.bufferVertexCapacity = 0;
	}

	void Vertices::InitializeWithMeshAndLayout(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept
	{
		DeleteVerticesOnGPU();

		layout = vertex_layout;

		verticesListPattern = FindVerticesListPattern(mesh);
		instanceDataCount = static_cast<unsigned int>(mesh.GetInstancedMatrixCount());
		verticesCount = static_cast<unsigned int>(mesh.GetPointCount());
		bufferVertexCapacity = verticesCount;

		glCheck(glGenVertexArrays(1, &verticesHandle));

		glCheck(glGenBuffers(1, &dataBufferHandle));

		Select(*this);

		glCheck(glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle));
		static constexpr GLvoid* NO_COPY = nullptr;
		glCheck(glBufferData(GL_ARRAY_BUFFER, (static_cast<unsigned long long>(verticesCount) * layout.GetVertexSize()), NO_COPY, GL_STATIC_DRAW));
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

		if (mesh.IsInstanceMatrixInvalid() == false)
		{
			glCheck(glGenBuffers(1, &instanceDataBufferHandle));
			glCheck(glBindBuffer(GL_ARRAY_BUFFER, instanceDataBufferHandle));
			glCheck(glBufferData(GL_ARRAY_BUFFER, (static_cast<unsigned long long>(instanceDataCount) * layout.GetInstanceVertexSize()), NO_COPY, GL_STATIC_DRAW));
			glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		layout.SendVertexDescriptionToOpenGL(dataBufferHandle, instanceDataBufferHandle);

		WriteMeshDataToVertexBuffer(mesh);

		SelectNothing();
	}

	void Vertices::UpdateVerticesFromMesh(const Mesh& mesh)
	{
		if ((mesh.GetPointCount()) <= bufferVertexCapacity)
		{
			verticesCount = (mesh.GetPointCount());

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
			glCheck(glDeleteVertexArrays(1, &dataBufferHandle));
			glCheck(glDeleteVertexArrays(1, &instanceDataBufferHandle));
			verticesHandle = 0;
			dataBufferHandle = 0;
			instanceDataBufferHandle = 0;
		}
	}

	void Vertices::WriteMeshDataToVertexBuffer(const Mesh& mesh) const noexcept
	{
		if (mesh.GetPointCount() == 0)
		{
			return;
		}

		Select(*this);

		// Write vertex data
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle));
		void* pointer;
		glCheck(pointer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

		GLuint offset = 0;
		const size_t pointCount = mesh.GetPointCount();
		for (std::size_t index = 0; index < pointCount; ++index)
		{
			for (const auto& element : layout.GetFieldTypes())
			{
				char* destination = reinterpret_cast<char*>(pointer) + offset;
				switch (element)
				{
				case VertexLayoutDescription::FieldType::Position2WithFloats:
				{
					vector2 position = mesh.GetPoint(index);
					const unsigned long long size = sizeof(position);
					std::memcpy(destination, &position, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::FieldType::TextureCoordinates2WithFloats:
				{
					vector2 textureCoordinate = mesh.GetTextureCoordinate(index);
					const unsigned long long size = sizeof(textureCoordinate);
					std::memcpy(destination, &textureCoordinate, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::FieldType::Color4WithUnsignedBytes:
				{
					Color4ub color = mesh.GetColor(index);
					const unsigned long long size = sizeof(color);
					std::memcpy(destination, &color, size);
					offset += size;
					break;
				}
				default:;
				}
			}
		}

		glCheck(glUnmapBuffer(GL_ARRAY_BUFFER));
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

		if (instanceDataBufferHandle == NOT_GENERATED || mesh.IsInstanceMatrixInvalid())
		{
			SelectNothing();
			return;
		}

		// Write Instance Data
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, instanceDataBufferHandle));
		void* instancePointer;
		glCheck(instancePointer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

		offset = 0;
		const size_t instancedMatrixCount = mesh.GetInstancedMatrixCount();
		for (size_t index = 0; index < instancedMatrixCount; index++)
		{
			for (const auto& element : layout.GetFieldTypes())
			{
				char* destination = reinterpret_cast<char*>(instancePointer) + offset;
				switch (element)
				{
				case VertexLayoutDescription::FieldType::InstancedMatrix9WithFloats1:
				{
					vector3 instancedMatrix = mesh.GetInstancedMatrix(index).column0;
					const unsigned long long size = sizeof(instancedMatrix);
					std::memcpy(destination, &instancedMatrix, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::FieldType::InstancedMatrix9WithFloats2:
				{
					vector3 instancedMatrix = mesh.GetInstancedMatrix(index).column1;
					const unsigned long long size = sizeof(instancedMatrix);
					std::memcpy(destination, &instancedMatrix, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::FieldType::InstancedMatrix9WithFloats3:
				{
					vector3 instancedMatrix = mesh.GetInstancedMatrix(index).column2;
					const unsigned long long size = sizeof(instancedMatrix);
					std::memcpy(destination, &instancedMatrix, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::FieldType::InstancedTextureCoordinateScaler2WithFloats:
				{
					vector2 instancedTextureCoordinate = mesh.GetInstancedTextureCoordinate(index);
					const unsigned long long size = sizeof(instancedTextureCoordinate);
					std::memcpy(destination, &instancedTextureCoordinate, size);
					offset += size;
					break;
				}
				case VertexLayoutDescription::FieldType::InstancedColor4WithUnsignedBytes:
				{
					Color4ub instancedColor = mesh.GetInstancedColors(index);
					const unsigned long long size = sizeof(instancedColor);
					std::memcpy(destination, &instancedColor, size);
					offset += size;
					break;
				}
				default:
					break;
				}
			}
		}
		glCheck(glUnmapBuffer(GL_ARRAY_BUFFER));
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

		SelectNothing();
	}
}
