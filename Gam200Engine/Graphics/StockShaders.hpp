/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StockShaders.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Header file for GLSL
******************************************************************************/
#pragma once

#include <Graphics/Shader.hpp>
#include <Graphics/VertexLayoutDescription.hpp>

namespace Graphics
{
    namespace SHADER
    {
        /**
         * \brief uniform input:
         * to_ndc : mat3  - To transform the mesh's local positions into Normalized Device Coordinates.
         * depth  : float - Used to define the meshes depth. Assumed to be in the range of [-1,1)
         * color  : vec4  - The color used to paint the mesh with
         * Assumes a Vertex structure of:
         * struct Vertex{
         *  vector2 position;
         * };
         * \return Globally accessible Shader for drawing Vertices with a solid uniform color.
         */
        Shader&                        solid_color() noexcept;
        const VertexLayoutDescription& solid_color_vertex_layout() noexcept;
        /**
         * \brief uniform input:
         * to_ndc : mat3  - To transform the mesh's local positions into Normalized Device Coordinates.
         * depth  : float - Used to define the meshes depth. Assumed to be in the range of [-1,1)
         * Assumes a Vertex structure of:
         * struct Vertex{
         *  vector2 position;
         *  Color4  color;
         * };
         * \return Globally accessible Shader for drawing Vertices with individual colors.
         */
        Shader&                        interpolated_colors() noexcept;
        const VertexLayoutDescription& interpolated_colors_vertex_layout() noexcept;
        /**
         * \brief uniform input:
         * to_ndc            : mat3      - To transform the mesh's local positions into Normalized Device Coordinates.
         * depth             : float     - Used to define the meshes depth. Assumed to be in the range of [-1,1)
         * color             : vec4      - The color used to multiply the texture with to create simple color variations
         * texture_to_sample : sampler2D - The texture to be applied to the mesh
         * Assumes a Vertex structure of:
         * struct Vertex{
         *  vector2 position;
         *  vector2 texture_coordinate;
         * };
         * \return Globally accessible Shader for drawing meshes with a texture.
         */
        Shader&                        textured() noexcept;
        const VertexLayoutDescription& textured_vertex_layout() noexcept;
		/**
		 * \brief uniform input:
		 * to_ndc            : mat3      - To transform the mesh's local positions into Normalized Device Coordinates.
		 * depth             : float     - Used to define the meshes depth. Assumed to be in the range of [-1,1)
		 * color             : vec4      - The color used to multiply the texture with to create simple color variations
		 * texture_to_sample : sampler2D - The texture to be applied to the mesh
		 * Assumes a Vertex structure of:
		 * struct Vertex{
		 *  vector2 position;
		 *  vector2 texture_coordinate;
		 * };
		 * \return Globally accessible Shader for drawing meshes with an animation.
		 */
		Shader& animated() noexcept;

		/**
		 * \brief uniform input:
		 * to_ndc            : mat3      - To transform the mesh's local positions into Normalized Device Coordinates.
		 * depth             : float     - Used to define the meshes depth. Assumed to be in the range of [-1,1)
		 * color             : vec4      - The color used to multiply the texture with to create simple color variations
		 * texture_to_sample : sampler2D - The texture to be applied to the mesh
		 * Assumes a Vertex structure of:
		 * struct Vertex{
		 *  vector2 position;
		 *  vector2 texture_coordinate;
		 * };
		 * \return Globally accessible Shader for drawing meshes with an infinite tiles.
		 */
		Shader& background() noexcept;

		/**
		 * \brief uniform input:
		 * stringHeight : float - height of string
		 * stringVectorPosition : vec2[50] - array that stored position of each Vertex
		 * stringVertexCapacity : int - To indicate how many vertex is used in string to discard unused mesh's points
		 * to_ndc            : mat3      - To transform the mesh's local positions into Normalized Device Coordinates.
		 * depth             : float     - Used to define the meshes depth. Assumed to be in the range of [-1,1)
		 * color             : vec4      - The color used to multiply the texture with to create simple color variations
		 * texture_to_sample : sampler2D - The texture to be applied to the mesh
		 * Assumes a Vertex structure of:
		 * struct Vertex{
		 *  vector2 position;
		 *  vector2 texture_coordinate;
		 * };
		 * \return Globally accessible Shader for drawing meshes with an infinite tiles.
		 */
		Shader& StringShader() noexcept;
		const VertexLayoutDescription& StringVertexLayout() noexcept;

        constexpr const char* Uniform_ToNDC   = "to_ndc";
        constexpr const char* Uniform_Depth   = "depth";
        constexpr const char* Uniform_Color   = "color";
        constexpr const char* Uniform_Texture = "texture_to_sample";
		constexpr const char* Uniform_Frame = "frame";
		constexpr const char* Uniform_Index = "index";
		constexpr const char* Uniform_ImageSize = "image_size";
		constexpr const char* Uniform_String_Vertex_Capacity = "stringVertexCapacity";
		constexpr const char* Uniform_String_Vertex_Position = "stringVectorPosition";
		constexpr const char* Uniform_String_Height = "stringHeight";
    };
}

#include "StockShaders.inl"
