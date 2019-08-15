/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Shader.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.06.2019

	Header file for Raw Shader code
******************************************************************************/
#pragma once
#include <map>
#include <string>

struct matrix3;

namespace Graphics
{
	class Color4f;
	struct vector3;

	class[[nodiscard]] Shader
	{
	public:
		Shader() noexcept = default;
		Shader(const std::string& vertex_shader_source_code, const std::string& fragment_shader_source_code);
		~Shader() noexcept = default;

		bool LoadFromSource(const std::string& vertex_shader_source_code,
							const std::string& fragment_shader_source_code);

		void SendUniformVariable(const std::string& variable_name, const  matrix3& affine_matrix) noexcept;
		void SendUniformVariable(const std::string& variable_name, float number) noexcept;
		void SendUniformVariable(const std::string& variable_name, int number) noexcept;
		void SendUniformVariable(const std::string& variable_name, Color4f color) noexcept;

		constexpr unsigned GetShaderHandler() const noexcept { return handleToShader; }

		void Delete() noexcept;

	public:
		static void Select(const Shader& shader) noexcept;
		static void SelectNothing() noexcept;

	public:
		Shader(const Shader& other) = delete;
		Shader(Shader&& other) noexcept = delete;
		Shader& operator=(const Shader& other) = delete;
		Shader& operator=(Shader&& other) noexcept = delete;

	private:
		int GetUniformLocation(const std::string& name) noexcept;

	private:
		unsigned                   handleToShader = 0;
		std::map<std::string, int> uniformNameToLocation{};
	};

}
