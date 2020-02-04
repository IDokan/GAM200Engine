/*  sinil.gang
 *  CS230 && GAM200
 */
#include <Graphics/Mesh.hpp>
#include <Graphics/VertexLayoutDescription.hpp>
#include <Graphics/glCheck.hpp>
#include <GL/glew.h>
#include <cassert>
#include <cstdint>

namespace Graphics
{
	Graphics::VertexLayoutDescription::VertexLayoutDescription(std::initializer_list<FieldType> fields) noexcept
	{
		for (const FieldType& element : fields)
		{
			AddField(element);
		}
	}

	void Graphics::VertexLayoutDescription::AddField(FieldType field_type) noexcept
	{
		fields.push_back(field_type);

		field_description temp;

		switch (field_type) {
		case Position2WithFloats:
			temp.elementType = GL_FLOAT;
			temp.elementCount = 2;
			temp.sizeInBytes = sizeof(float) * temp.elementCount;
			break;

		case TextureCoordinates2WithFloats:
			temp.elementType = GL_FLOAT;
			temp.elementCount = 2;
			temp.sizeInBytes = sizeof(float) * temp.elementCount;
			break;

		case Color4WithUnsignedBytes:
			temp.elementType = GL_UNSIGNED_BYTE;
			temp.elementCount = 4;
			temp.sizeInBytes = sizeof(unsigned char) * temp.elementCount;
			temp.shouldNormalize = true;
			break;

		case InstancedMatrix9WithFloats:
			temp.elementType = GL_FLOAT;
			temp.elementCount = 9;
			temp.sizeInBytes = sizeof(float) * temp.elementCount;
			temp.shouldInstanced = true;
			break;

		default:
			break;
		}

		vertexSize += temp.sizeInBytes;

		vertexDescription.push_back(temp);
	}

	void Graphics::VertexLayoutDescription::SendVertexDescriptionToOpenGL() const noexcept
	{
		GLintptr offset = 0;

		for (int count = 0; count < static_cast<int>(fields.size()); ++count)
		{
			glCheck(glEnableVertexAttribArray(count));

			const field_description temp = vertexDescription.at(count);


			glCheck(glVertexAttribPointer(count, temp.elementCount, temp.elementType, temp.shouldNormalize, vertexSize,
				(void*)offset));

			if (temp.shouldInstanced)
			{
				glCheck(glVertexAttribDivisor(count, 1));
			}

			offset += vertexDescription.at(count).sizeInBytes;
		}
	}
}
