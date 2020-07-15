/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   VertexLayoutDescription.hpp
Author
    - Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

    Header file for VertexLayoutDescription functions
******************************************************************************/
#pragma once
#include <vector>

namespace Graphics
{
    class [[nodiscard]] VertexLayoutDescription
    {
    public:
        enum class FieldType
        {
            Position2WithFloats,
            TextureCoordinates2WithFloats,
            Color4WithUnsignedBytes,
			InstancedMatrix9WithFloats1,
			InstancedMatrix9WithFloats2,
			InstancedMatrix9WithFloats3,
            InstancedTextureCoordinateScaler2WithFloats,
            InstancedColor4WithUnsignedBytes,
        };

        constexpr VertexLayoutDescription() noexcept = default;
        VertexLayoutDescription(std::initializer_list<FieldType> fields) noexcept;


        void                                    AddField(FieldType field_type) noexcept;
        void                                    SendVertexDescriptionToOpenGL(unsigned int dataBufferHandle, unsigned int instanceDataBufferHandle) const noexcept;
		[[nodiscard]] constexpr unsigned                      GetVertexSize() const noexcept { return vertexSize; }
		[[nodiscard]] constexpr unsigned                      GetInstanceVertexSize() const noexcept { return instanceVertexSize; }
        [[nodiscard]] constexpr const std::vector<FieldType>& GetFieldTypes() const noexcept { return fields; }

    private:
        struct field_description
        {
            unsigned elementType     = 0;
            unsigned elementCount    = 0;
            unsigned sizeInBytes     = 0;
            bool     shouldNormalize = false;
			bool		shouldInstanced = false;
        };
        unsigned                       vertexSize = 0;
		unsigned						instanceVertexSize = 0;
		std::vector<field_description> vertexDescription{};
		std::vector<field_description> instanceVertexDescription{};
        std::vector<FieldType>         fields{};
    };
}
