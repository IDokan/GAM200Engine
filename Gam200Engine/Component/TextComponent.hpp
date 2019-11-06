/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Text.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 10.28.2019

	Header file for Text Component Implementation
******************************************************************************/
#pragma once
#include "Graphics/TextPlatform.hpp"
#include "Component/Component.hpp"
#include "Graphics/BitmapFont.hpp"
#include "Graphics/Material.hpp"

namespace Graphics
{
	namespace BITMAPFONTS
	{
		enum class FONTTYPE;
	}
}

class TextComponent : public Component
{
public:
	TextComponent(Object* obj) noexcept;
	~TextComponent() noexcept = default;
	
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Clear() override;

	void Draw(const matrix3& toNDC, float depth) noexcept;
	
	void SetFonts(Graphics::BITMAPFONTS::FONTTYPE fontType);
	void SetString(std::wstring str) noexcept;

	std::vector<std::pair<const Graphics::Vertices*, const Graphics::Texture*>> GetVerticesWithMatchingTextures() const noexcept;
private:
	std::shared_ptr<Graphics::TextPlatform> textPlatform;
	std::shared_ptr<Graphics::material> textMaterial;
};