/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Shader.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Source file for Shader
******************************************************************************/
#include "Shader.hpp"
#include <Graphics/glCheck.hpp>
#include <Graphics/Color4f.hpp>
#include <GL/glew.h>
#include <iostream>
#include <matrix3.hpp>
#include <Vector2.hpp>
#include <Object/Strings/String.hpp>

Graphics::Shader::Shader(const std::string& vertex_shader_source_code, const std::string& fragment_shader_source_code)
{
	if (!LoadFromSource(vertex_shader_source_code, fragment_shader_source_code))
	{
		std::cout << "Shader compilation failed!\n";
		std::cerr << "Shader compilation failed!\n";
	}
}

bool Graphics::Shader::LoadFromSource(const std::string& vertex_shader_source_code,
	const std::string& fragment_shader_source_code)
{
	if (handleToShader != NULL)
	{
		Delete();
	}

	GLuint vertexShader;
	glCheck(vertexShader = glCreateShader(GL_VERTEX_SHADER));

	const GLchar* vertexShaderSource = vertex_shader_source_code.c_str();

	glCheck(glShaderSource(vertexShader, 1, &vertexShaderSource, NULL));
	glCheck(glCompileShader(vertexShader));

	GLint isCompiled = 0;
	glCheck(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled));

	if (isCompiled == GL_FALSE)
	{
		GLsizei logLength = 0;
		glCheck(glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength));

		GLchar* errorLog = new GLchar[logLength + 1];
		glCheck(glGetShaderInfoLog(vertexShader, logLength, &logLength, errorLog));

		std::cout << errorLog << '\n';
		std::cerr << errorLog << '\n';

		delete[] errorLog;
		glCheck(glDeleteShader(vertexShader));

		return false;
	}

	GLuint fragmentShader;
	glCheck(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

	const GLchar* fragmentShaderSource = fragment_shader_source_code.c_str();
	glCheck(glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL));

	glCheck(glCompileShader(fragmentShader));

	glCheck(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled));

	if (isCompiled == GL_FALSE)
	{
		GLsizei logLength = 0;
		glCheck(glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength));

		GLchar* errorLog = new GLchar[logLength + 1];
		glCheck(glGetShaderInfoLog(fragmentShader, logLength, &logLength, errorLog));

		std::cout << errorLog << '\n';
		std::cerr << errorLog << '\n';

		delete[] errorLog;
		glCheck(glDeleteShader(vertexShader));
		glCheck(glDeleteShader(fragmentShader));

		return false;
	}

	GLuint program;
	glCheck(program = glCreateProgram());

	glCheck(glAttachShader(program, vertexShader));
	glCheck(glAttachShader(program, fragmentShader));

	glCheck(glLinkProgram(program));

	GLint isLinked = 0;
	glCheck(glGetProgramiv(program, GL_LINK_STATUS, &isLinked));
	if (isLinked == GL_FALSE)
	{
		GLsizei logLength = 0;
		glCheck(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength));

		GLchar* errorLog = new GLchar[logLength + 1];
		glCheck(glGetProgramInfoLog(program, logLength, &logLength, errorLog));

		std::cout << errorLog << '\n';
		std::cerr << errorLog << '\n';

		delete[] errorLog;
		glCheck(glDeleteProgram(program));
		Delete();

		glCheck(glDeleteShader(vertexShader));
		glCheck(glDeleteShader(fragmentShader));

		return false;
	}

	glCheck(glUseProgram(program));

	glCheck(glDeleteShader(vertexShader));
	glCheck(glDeleteShader(fragmentShader));

	handleToShader = program;

	return true;
}

void Graphics::Shader::SendUniformVariable(const std::string& variable_name, const  matrix3& affine_matrix) noexcept
{
	glCheck(glUniformMatrix3fv(GetUniformLocation(variable_name), 1, GL_FALSE, &affine_matrix.elements[0][0]));
}

void Graphics::Shader::SendUniformVariable(const std::string& variable_name, float number) noexcept
{
	glCheck(glUniform1f(GetUniformLocation(variable_name), number));
}

void Graphics::Shader::SendUniformVariable(const std::string& variable_name, int number) noexcept
{
	glCheck(glUniform1i(GetUniformLocation(variable_name), number));
}

void Graphics::Shader::SendUniformVariable(const std::string& variable_name, vector2 number) noexcept
{
	glCheck(glUniform2f(GetUniformLocation(variable_name), number.x, number.y));
}

void Graphics::Shader::SendUniformVariable(const std::string& variable_name, Color4f color) noexcept
{
	glCheck(glUniform4f(GetUniformLocation(variable_name), color.red, color.green, color.blue, color.alpha));
}

void Graphics::Shader::SendUniformVariable(const std::string& variable_name, vector2* number) noexcept
{
	glCheck(glUniform2fv(GetUniformLocation(variable_name), String::maxVertexSize, &number->elements[0]));
}

void Graphics::Shader::Delete() noexcept
{
	// Error prone
	if (handleToShader == 0)
	{
		return;
	}
	glCheck(glDeleteProgram(handleToShader));
	handleToShader = 0;
	uniformNameToLocation.clear();
}

void Graphics::Shader::Select(const Shader& shader) noexcept
{
	auto program = shader.GetShaderHandler();
	if (program)
	{
		glCheck(glUseProgram(program));
	}
}

void Graphics::Shader::SelectNothing() noexcept
{
	glCheck(glUseProgram(NULL));
}

int Graphics::Shader::GetUniformLocation(const std::string& name) noexcept
{
	std::map<std::string, int>::iterator tmp = uniformNameToLocation.find(name);

	if (tmp != uniformNameToLocation.end())
	{
		return tmp->second;
	}
	else
	{
		GLuint newLocation;
		glCheck(newLocation = glGetUniformLocation(handleToShader, name.c_str()));
		uniformNameToLocation.insert(std::pair<std::string, int>(name, newLocation));
		return newLocation;
	}
}
