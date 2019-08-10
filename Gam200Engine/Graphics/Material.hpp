/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Material.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Header file for Material declaration
******************************************************************************/
#pragma once
#include <Graphics/Color4f.hpp>
#include <Matrix.hpp>
#include <map>
#include <string>
#include "matrix3.hpp"

namespace Graphics
{
    class Shader;
    class Texture;
    struct [[nodiscard]] texture_uniform
    {
        const Texture* texture     = nullptr;
        int            textureSlot = 0;
    };

    struct [[nodiscard]] material
    {
        Shader*                                shader = nullptr;
        std::map<std::string, Math::matrix3>         matrix3Uniforms{};
        std::map<std::string, Color4f>         color4fUniforms{};
        std::map<std::string, float>           floatUniforms{};
        std::map<std::string, texture_uniform> textureUniforms{};
    };
}
