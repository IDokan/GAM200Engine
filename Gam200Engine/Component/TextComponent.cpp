/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Text.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 10.28.2019

	Header file for Text Component Implementation
******************************************************************************/
#include "Component/Text.hpp"
#include <Graphics/StockBitmapFonts.hpp>
#include <Graphics/StockShaders.hpp>
#include <Graphics/GL.hpp>

TextComponent::TextComponent(Object* obj) noexcept
	:Component(obj), textPlatform(std::make_shared<Graphics::TextPlatform>(L"default string", Graphics::BITMAPFONTS::malgungothic())), textMaterial(std::make_shared<Graphics::material>())
{
}

void TextComponent::Init()
{
	textMaterial->shader = &Graphics::SHADER::textured();
	textMaterial->color4fUniforms[Graphics::SHADER::Uniform_Color] = Graphics::Color4f{ 1.f };
	textMaterial->floatUniforms[Graphics::SHADER::Uniform_Depth] = -0.9f;
}

void TextComponent::Update(float dt)
{
}

void TextComponent::Clear()
{
}

void TextComponent::Draw(const matrix3& toNDC, float depth) noexcept
{
	for (const auto& verticesTexturePair : textPlatform->GetVerticesWithMatchingTextures())
	{
		const Graphics::Vertices& textVertices = *verticesTexturePair.first;
		const Graphics::Texture* textTexture = verticesTexturePair.second;
		textMaterial->textureUniforms.insert_or_assign(Graphics::SHADER::Uniform_Texture, Graphics::texture_uniform{ textTexture });
		textMaterial->matrix3Uniforms[Graphics::SHADER::Uniform_ToNDC] = toNDC;
		textMaterial->floatUniforms[Graphics::SHADER::Uniform_Depth] = depth;
		Graphics::GL::draw(textVertices, *textMaterial.get());
	}
}

void TextComponent::SetFonts(Graphics::BITMAPFONTS::FONTTYPE fontType)
{
	switch (fontType)
	{
	case Graphics::BITMAPFONTS::FONTTYPE::MALGUNGOTHIC:
		textPlatform->SetFont(Graphics::BITMAPFONTS::malgungothic());
		break;
	case Graphics::BITMAPFONTS::FONTTYPE::NUMOFFONTTYPE:
	default:
		break;
	}
}

void TextComponent::SetString(std::wstring str) noexcept
{
	textPlatform->SetString(str);
}

std::vector<std::pair<const Graphics::Vertices*, const Graphics::Texture*>> TextComponent::GetVerticesWithMatchingTextures() const noexcept
{
	return textPlatform->GetVerticesWithMatchingTextures();
}
