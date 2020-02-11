/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   GL.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Source file for GL functions
******************************************************************************/
#include <Graphics/Color4f.hpp>
#include <Graphics/GL.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Vertices.hpp>
#include <Graphics/glCheck.hpp>
#include <GL/glew.h>
#include <iostream>
#include "ImGui/MyImGui.hpp"

namespace Graphics
{
	void SendUniforms(const material& material)
	{
		Shader::Select(*material.shader);

		for (const auto& element : material.color4fUniforms)
		{
			material.shader->SendUniformVariable(element.first, element.second);
		}
		for (const auto& element : material.matrix3Uniforms)
		{
			material.shader->SendUniformVariable(element.first, element.second);
		}
		for (const auto& element : material.intUniform)
		{
			material.shader->SendUniformVariable(element.first, element.second);
		}
		for (const auto& element : material.floatUniforms)
		{
			material.shader->SendUniformVariable(element.first, element.second);
		}
		for (const auto& element : material.vector2Uniforms)
		{
			material.shader->SendUniformVariable(element.first, element.second);
		}
		for (const auto& element : material.textureUniforms)
		{
			Texture::SelectTextureForSlot(*element.second.texture, element.second.textureSlot);
		}
		for (const auto& element : material.arrayVector2Uniforms)
		{
			material.shader->SendUniformVariable(element.first, element.second);
		}
	}
	
    void GL::setup() noexcept
    {
        set_clear_color(Color4f{0, 255});
        glCheck(glEnable(GL_DEPTH_TEST));
        glCheck(glEnable(GL_BLEND));
        glCheck(glBlendEquation(GL_FUNC_ADD));
        glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        enable_multiple_sampling(true);
    }

    void GL::begin_drawing() noexcept
    {
        glCheck(glClear(GL_COLOR_BUFFER_BIT));
        glCheck(glClear(GL_DEPTH_BUFFER_BIT));
    }

    void GL::draw(const Vertices& vertices, const material& material) noexcept
    {
        Shader::Select(*material.shader);
        Vertices::Select(vertices);

		SendUniforms(material);
    	
        glCheck(glDrawArrays(vertices.GetVerticesListPattern(), 0, vertices.GetVerticesCount()));
    }

	void GL::drawInstanced(const Vertices& vertices, const material& material) noexcept
	{
		Shader::Select(*material.shader);
		Vertices::Select(vertices);

		SendUniforms(material);

		constexpr GLsizei numOfDrawing = 10000;
		glCheck(glDrawArraysInstanced(vertices.GetVerticesListPattern(), 0, vertices.GetVerticesCount(), numOfDrawing));
	}

    void GL::end_drawing() noexcept { glCheck(glFinish()); }

    void GL::set_clear_color(Color4f color) noexcept
    {
        glCheck(glClearColor(color.red, color.green, color.blue, color.alpha));
    }

    void GL::set_display_area(int pixels_width, int pixels_height, int left_x, int bottom_y) noexcept
    {
        glCheck(glViewport(left_x, bottom_y, pixels_width, pixels_height));
    }

    void GL::set_line_width(float line_width) noexcept { glCheck(glLineWidth(line_width)); }

    void GL::enable_multiple_sampling(bool enable_it) noexcept
    {
        if (enable_it)
        {
            glCheck(glEnable(GL_MULTISAMPLE));
        }
        else
        {
            glCheck(glDisable(GL_MULTISAMPLE));
        }
    }

    void GL::print_context_information()
    {
        // print GL context parameters ...
        GLenum param_enums[] = {
            GL_VENDOR, // 0
            GL_RENDERER,
            GL_VERSION,
            GL_SHADING_LANGUAGE_VERSION, // 3

            GL_MAJOR_VERSION, // 4
            GL_MINOR_VERSION,
            GL_MAX_ELEMENTS_VERTICES,
            GL_MAX_ELEMENTS_INDICES,
            GL_MAX_GEOMETRY_OUTPUT_VERTICES,
            GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
            GL_MAX_CUBE_MAP_TEXTURE_SIZE,
            GL_MAX_DRAW_BUFFERS,
            GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
            GL_MAX_TEXTURE_IMAGE_UNITS,
            GL_MAX_TEXTURE_SIZE,
            GL_MAX_VARYING_FLOATS,
            GL_MAX_VERTEX_ATTRIBS,
            GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
            GL_MAX_VERTEX_UNIFORM_COMPONENTS, // 18

            GL_MAX_VIEWPORT_DIMS, // 19

            GL_STEREO // 20
        };

        char const* param_names[] = {
            "GL_VENDOR", // 0
            "GL_RENDERER",
            "GL_VERSION",
            "GL_SHADING_LANGUAGE_VERSION", // 3

            "GL_MAJOR_VERSION", // 4
            "GL_MINOR_VERSION",
            "GL_MAX_ELEMENTS_VERTICES",
            "GL_MAX_ELEMENTS_INDICES",
            "GL_MAX_GEOMETRY_OUTPUT_VERTICES",
            "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
            "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
            "GL_MAX_DRAW_BUFFERS",
            "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
            "GL_MAX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_TEXTURE_SIZE",
            "GL_MAX_VARYING_FLOATS",
            "GL_MAX_VERTEX_ATTRIBS",
            "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_VERTEX_UNIFORM_COMPONENTS", // 18

            "GL_MAX_VIEWPORT_DIMS", // 19

            "GL_STEREO" // 20
        };

        // C-strings for 1st four parameters
        std::cout << "GL version information and context parameters: " << std::endl;
        int i = 0;
        for (i = 0; i < 4; ++i)
        {
            GLubyte const* param_str = glGetString(param_enums[i]);
            glCheckError(__FILE__, __LINE__, "glGetString(param_enums[i])");
            std::cout << param_names[i] << ": " << param_str << std::endl;
        }

        // one integer for next set of fifteen parameters
        for (; i < 19; ++i)
        {
            GLint val;
            glCheck(glGetIntegerv(param_enums[i], &val));
            std::cout << param_names[i] << ": " << val << std::endl;
        }

        // two integers for next parameter
        GLint dim[2];
        glCheck(glGetIntegerv(param_enums[19], dim));
        std::cout << param_names[19] << ": " << dim[0] << " x " << dim[1] << std::endl;

        // bool for next parameter
        GLboolean flag;
        glCheck(glGetBooleanv(param_enums[20], &flag));
        std::cout << param_names[20] << ": " << static_cast<GLint>(flag) << std::endl;
    }
}
