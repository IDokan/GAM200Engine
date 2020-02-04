/*
 * sinil.gang
 * Graphics Library
 * CS230 && GAM200
 */
#pragma once
#include <vector>

namespace Graphics
{
    class [[nodiscard]] VertexLayoutDescription
    {
    public:
        enum FieldType
        {
            Position2WithFloats,
            TextureCoordinates2WithFloats,
            Color4WithUnsignedBytes,
        	InstancedMatrix9WithFloats,
        };

        constexpr VertexLayoutDescription() noexcept = default;
        VertexLayoutDescription(std::initializer_list<FieldType> fields) noexcept;


        void                                    AddField(FieldType field_type) noexcept;
        void                                    SendVertexDescriptionToOpenGL() const noexcept;
        [[nodiscard]] constexpr unsigned                      GetVertexSize() const noexcept { return vertexSize; }
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
        std::vector<field_description> vertexDescription{};
        std::vector<FieldType>         fields{};
    };
}
