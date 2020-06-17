#include "StockShaders.hpp"
/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StockShaders.inl
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Source file for GLSL
******************************************************************************/
#pragma once

namespace Graphics
{
	inline Shader& SHADER::solid_color() noexcept
	{
		static Shader shader(R"(
#version 330

layout(location = 0) in vec2 position;

uniform mat3 to_ndc;
uniform float depth;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);
}
)",
R"(
#version 330

uniform vec4 color;
out vec4 output_color;

void main()
{
    output_color = color;
}
)");
		return shader;
	}

	inline const VertexLayoutDescription& SHADER::solid_color_vertex_layout() noexcept
	{
		static VertexLayoutDescription* layout = new VertexLayoutDescription({ VertexLayoutDescription::FieldType::Position2WithFloats });
		return *layout;
	}

	inline Shader& SHADER::interpolated_colors() noexcept
	{
		static Shader shader(
			R"(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;

uniform mat3 to_ndc;
uniform float depth;

smooth out vec4 interpolated_color;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);
    interpolated_color = color;
}
)",
R"(
#version 330

in vec4 interpolated_color;
out vec4 output_color;

void main()
{
    output_color = interpolated_color;
}
)");
		return shader;
	}

	inline const VertexLayoutDescription& SHADER::interpolated_colors_vertex_layout() noexcept
	{
		static VertexLayoutDescription* layout = new VertexLayoutDescription{ VertexLayoutDescription::FieldType::Position2WithFloats,
											  VertexLayoutDescription::FieldType::Color4WithUnsignedBytes };
		return *layout;
	}

	inline Shader& SHADER::textured() noexcept
	{
		static Shader shader(
			R"(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture_coordinate;

uniform mat3 to_ndc;
uniform float depth;

out vec2 interpolated_texture_coordinate;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);
    interpolated_texture_coordinate = texture_coordinate;
}
)",
R"(
#version 330

in vec2 interpolated_texture_coordinate;

uniform vec4 color;
uniform sampler2D texture_to_sample;

out vec4 output_color;

void main()
{
    vec4 texel = texture(texture_to_sample, interpolated_texture_coordinate);
    vec4 new_color = color * texel;
    if(new_color.a <= 0.0f)
        discard;
    output_color = new_color;
}
)");
		return shader;
	}

	inline const VertexLayoutDescription& SHADER::textured_vertex_layout() noexcept
	{
		static VertexLayoutDescription* layout = new VertexLayoutDescription{ VertexLayoutDescription::FieldType::Position2WithFloats,
											  VertexLayoutDescription::FieldType::TextureCoordinates2WithFloats };
		return *layout;
	}

	inline Shader& SHADER::animated() noexcept
	{
		static Shader shader(
			R"(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture_coordinate;

uniform mat3 to_ndc;
uniform float depth;
uniform int frame;
uniform int index;
uniform vec2 image_size;
uniform int state;
uniform int max_state;

out vec2 interpolated_texture_coordinate;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);
    interpolated_texture_coordinate = vec2((texture_coordinate.x + index) / frame, (texture_coordinate.y + state) / max_state);
}
)",
R"(
#version 330

in vec2 interpolated_texture_coordinate;

uniform vec4 color;
uniform sampler2D texture_to_sample;

out vec4 output_color;

void main()
{
    vec4 texel = texture(texture_to_sample, interpolated_texture_coordinate);
    vec4 new_color = color * texel;
    if(new_color.a <= 0.0f)
        discard;
    output_color = new_color;
}
)");
		return shader;
	}

	inline Shader& SHADER::background() noexcept
	{
		static Shader shader(
			R"(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture_coordinate;

uniform mat3 to_ndc;
uniform float depth;

out vec2 interpolated_texture_coordinate;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);
    interpolated_texture_coordinate = texture_coordinate;
}
)",
R"(
#version 330

in vec2 interpolated_texture_coordinate;

uniform vec4 color;
uniform sampler2D texture_to_sample;

out vec4 output_color;

void main()
{
    vec4 texel = texture(texture_to_sample, interpolated_texture_coordinate);
    vec4 new_color = color * texel;
    if(new_color.a <= 0.0f)
        discard;
    output_color = new_color;
}
)");
		return shader;
	}

	inline Shader& SHADER::StringShader() noexcept
	{
		static Shader shader(
			R"(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture_coordinate;

uniform float stringHeight;
uniform vec2 stringVectorPosition[60];
uniform int stringVertexCapacity;
uniform mat3 to_ndc;
uniform float depth;

out vec2 interpolated_texture_coordinate;

// Flag that indicates it has to be discarded or not.
flat out int isDiscarded;

vec2 GetPerpendicularVectorWithSize(vec2 targetVector, vec2 currentVector, float size)
{
		// Get a vector
		vec2 vector = targetVector - currentVector;
		// rotate by counter clockwise
		vec2 perpendicularVector = vec2(-vector.y, vector.x);
		vec2 normalVector = normalize(perpendicularVector);
		return (normalVector * vec2(stringHeight));
}

vec2 GetPerpendicularVectorWithSize(vec2 targetVector1, vec2 targetVector2, vec2 currentVector, float size)
{
		// Get a vector
		vec2 vector1 = targetVector1 - currentVector;
		vec2 vector2 = currentVector - targetVector2;
		// rotate by counter clockwise
		vec2 perpendicularVector1 = vec2(-vector1.y, vector1.x);
		vec2 perpendicularVector2 = vec2(-vector2.y, vector2.x);

		vec2 normalVector = normalize(perpendicularVector1 + perpendicularVector2);
		return (normalVector * vec2(stringHeight));
}



void main()
{
	int stringIndex = int(position.x);
	if(stringIndex >= stringVertexCapacity)
	{
		isDiscarded = 1;
		return;
	}
    else
    {
        isDiscarded = 0;
    }
	
	// position flag indicates this position is a upper point or lower point
	// if 0 upper point, if 1 lower point
	int positionFlag = int(position.y);
	vec3 vertexPosition = vec3(stringVectorPosition[stringIndex], 1.f);

	// Determine thickness of string with stringHeight and calculation with other points
	vec2 normalVector = vec2(0, 0);

		// If first vertex of string,
		if(stringIndex == 0)
		{
			normalVector = GetPerpendicularVectorWithSize(stringVectorPosition[stringIndex+1], stringVectorPosition[stringIndex], stringHeight);
		}
		// If last vertex of string,
		else if(stringIndex == stringVertexCapacity-1)
		{
			normalVector = GetPerpendicularVectorWithSize(stringVectorPosition[stringIndex], stringVectorPosition[stringIndex-1], stringHeight);
		}
		// normal vertex
		else{
				normalVector = GetPerpendicularVectorWithSize(stringVectorPosition[stringIndex+1], stringVectorPosition[stringIndex-1], stringVectorPosition[stringIndex], stringHeight);
		}

	// If current position is lower position,
	if(positionFlag == 1)
	{
		// Flip normal vector (up -> down)
		normalVector = -normalVector;
	}
	
		// Update vertexPosition with calculated normalVector
		vertexPosition.x += normalVector.x;
		vertexPosition.y += normalVector.y;
		
vertexPosition = to_ndc * vertexPosition;

    gl_Position = vec4(vertexPosition.xy, depth, 1.0);
    interpolated_texture_coordinate = texture_coordinate;
}
)",
R"(
#version 330

flat in int isDiscarded;
in vec2 interpolated_texture_coordinate;

uniform vec4 color;
uniform sampler2D texture_to_sample;

out vec4 output_color;

void main()
{
	// Discard and return unused vertices
	if(isDiscarded == 1)
	{
		discard;
		return;
	}

    vec4 texel = texture(texture_to_sample, interpolated_texture_coordinate);
    vec4 new_color = color * texel;
    if(new_color.a <= 0.0f)
        discard;
    output_color = new_color;
}
)");
		return shader;
	}

	inline const VertexLayoutDescription& SHADER::StringVertexLayout() noexcept
	{
		static VertexLayoutDescription* layout = new VertexLayoutDescription{ VertexLayoutDescription::FieldType::Position2WithFloats,
											  VertexLayoutDescription::FieldType::TextureCoordinates2WithFloats };
		return *layout;
	}

	inline Shader& SHADER::Instancing() noexcept
	{
		static Shader shader{ R"(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture_coordinate;
layout(location = 2) in mat3 to_ndc;

uniform float depth;

out vec2 interpolated_texture_coordinate;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);
    interpolated_texture_coordinate = texture_coordinate;
}
)",
R"(
#version 330

in vec2 interpolated_texture_coordinate;

uniform vec4 color;
uniform sampler2D texture_to_sample;

out vec4 output_color;

void main()
{
    vec4 texel = texture(texture_to_sample, interpolated_texture_coordinate);
    vec4 new_color = color * texel;
    if(new_color.a <= 0.0f)
        discard;
    output_color = new_color;
}
)" };
		return shader;
	}

	inline const VertexLayoutDescription& SHADER::instancing_vertex_layout() noexcept
	{
		static VertexLayoutDescription* layout = new VertexLayoutDescription{
			VertexLayoutDescription::FieldType::Position2WithFloats,
		VertexLayoutDescription::FieldType::TextureCoordinates2WithFloats,
		VertexLayoutDescription::FieldType::InstancedMatrix9WithFloats1,
		VertexLayoutDescription::FieldType::InstancedMatrix9WithFloats2,
		VertexLayoutDescription::FieldType::InstancedMatrix9WithFloats3,
		};
		return *layout;
	}
	inline Shader& SHADER::AdvancedInstancing() noexcept
	{
		static Shader shader{ R"(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture_coordinate;
layout(location = 2) in vec2 texture_coordinate_scaler;
layout(location = 3) in vec4 color;
layout(location = 4) in mat3 to_ndc;

uniform float depth;

out vec2 interpolated_texture_coordinate;
out vec4 interpolated_color;

void main()
{
    vec3 position = to_ndc * vec3(position, 1.0f);
    gl_Position = vec4(position.xy, depth, 1.0);

	// Scale Texture coordinate
	vec2 TC;
	TC.x = texture_coordinate.x * texture_coordinate_scaler.x;
	TC.y = texture_coordinate.y * texture_coordinate_scaler.y;

    interpolated_texture_coordinate = TC;
	interpolated_color = color;
}
)",
R"(
#version 330

in vec2 interpolated_texture_coordinate;
in vec4 interpolated_color;

uniform sampler2D texture_to_sample;

out vec4 output_color;

void main()
{
    vec4 texel = texture(texture_to_sample, interpolated_texture_coordinate);
    vec4 new_color = interpolated_color * texel;
    if(new_color.a <= 0.0f)
        discard;
    output_color = new_color;
}
)" };
		return shader;
	}
	inline const VertexLayoutDescription& SHADER::Advanced_instancing_vertex_layout() noexcept
	{
		static VertexLayoutDescription* layout = new VertexLayoutDescription
		{
			VertexLayoutDescription::FieldType::Position2WithFloats,
			VertexLayoutDescription::FieldType::TextureCoordinates2WithFloats,
			VertexLayoutDescription::FieldType::InstancedTextureCoordinateScaler2WithFloats,
			VertexLayoutDescription::FieldType::InstancedColor4WithUnsignedBytes,
			VertexLayoutDescription::FieldType::InstancedMatrix9WithFloats1,
			VertexLayoutDescription::FieldType::InstancedMatrix9WithFloats2,
			VertexLayoutDescription::FieldType::InstancedMatrix9WithFloats3,
		};
		return *layout;
	}
}
