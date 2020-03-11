/*  sinil.gang
 *  CS230 && GAM200
 */
#include <cassert>
#include <cstdint>
#include <Graphics/Mesh.hpp>
#include <Graphics/VertexLayoutDescription.hpp>
#include <Graphics/glCheck.hpp>
#include <GL/glew.h>
#include <Graphics/Vertices.hpp>

namespace Graphics
{
	Graphics::VertexLayoutDescription::VertexLayoutDescription(std::initializer_list<FieldType> fields) noexcept
	{
		for (const VertexLayoutDescription::FieldType& element : fields)
		{
			AddField(element);
		}
	}

	void Graphics::VertexLayoutDescription::AddField(FieldType field_type) noexcept
	{
		fields.push_back(field_type);

		field_description temp;

		switch (field_type) {
		case FieldType::Position2WithFloats:
			temp.elementType = GL_FLOAT;
			temp.elementCount = 2;
			temp.sizeInBytes = sizeof(float) * temp.elementCount;
			break;

		case FieldType::TextureCoordinates2WithFloats:
			temp.elementType = GL_FLOAT;
			temp.elementCount = 2;
			temp.sizeInBytes = sizeof(float) * temp.elementCount;
			break;

		case FieldType::Color4WithUnsignedBytes:
			temp.elementType = GL_UNSIGNED_BYTE;
			temp.elementCount = 4;
			temp.sizeInBytes = sizeof(unsigned char) * temp.elementCount;
			temp.shouldNormalize = true;
			break;

		case FieldType::InstancedMatrix9WithFloats1:
			temp.elementType = GL_FLOAT;
			temp.elementCount = 3;
			temp.sizeInBytes = sizeof(float) * temp.elementCount;
			temp.shouldInstanced = true;
			break;

		case FieldType::InstancedMatrix9WithFloats2:
			temp.elementType = GL_FLOAT;
			temp.elementCount = 3;
			temp.sizeInBytes = sizeof(float) * temp.elementCount;
			temp.shouldInstanced = true;
			break;

		case FieldType::InstancedMatrix9WithFloats3:
			temp.elementType = GL_FLOAT;
			temp.elementCount = 3;
			temp.sizeInBytes = sizeof(float) * temp.elementCount;
			temp.shouldInstanced = true;
			break;

		default:
			break;
		}

		if (temp.shouldInstanced == false)
		{
			vertexSize += temp.sizeInBytes;

			vertexDescription.push_back(temp);
		}
		else
		{
			instanceVertexSize += temp.sizeInBytes;

			instanceVertexDescription.push_back(temp);
		}
	}

	void Graphics::VertexLayoutDescription::SendVertexDescriptionToOpenGL(unsigned int dataBufferHandle, unsigned int instanceDataBufferHandle) const noexcept
	{
		GLintptr offset = 0;
		GLuint count = 0;
		GLuint sizeOfVertexDescription = static_cast<GLuint>(vertexDescription.size());

		glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle);

		// send vertex data
		for (; count < sizeOfVertexDescription; ++count)
		{
			glCheck(glEnableVertexAttribArray(count));

			const field_description temp = vertexDescription.at(count);


			glCheck(glVertexAttribPointer(count, temp.elementCount, temp.elementType, temp.shouldNormalize, vertexSize,
				(void*)offset));

			offset += vertexDescription.at(count).sizeInBytes;
		}

		if (instanceDataBufferHandle == Vertices::NOT_GENERATED)
		{
			return;
		}

		glBindBuffer(GL_ARRAY_BUFFER, instanceDataBufferHandle);

		 
		offset = 0;
		GLuint sizeOfVertexANDInstanceVertexDescription = sizeOfVertexDescription + static_cast<GLuint>(instanceVertexDescription.size());
		// send instance data
		for (; count < sizeOfVertexANDInstanceVertexDescription; ++count)
		{
			glCheck(glEnableVertexAttribArray(count));

			const field_description temp = instanceVertexDescription.at(count - sizeOfVertexDescription);


			glCheck(glVertexAttribPointer(count, temp.elementCount, temp.elementType, temp.shouldNormalize, instanceVertexSize,
				(void*)offset));

			glCheck(glVertexAttribDivisor(count, 1));

			offset += instanceVertexDescription.at(count - sizeOfVertexDescription).sizeInBytes;
		}
	}
}
