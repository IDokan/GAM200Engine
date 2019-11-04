/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TextPlatform.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 10.28.2019

	Source file for base text platform used for Text Class
******************************************************************************/
#pragma once

#include <Graphics/Vertices.hpp>
#include <string>
#include <unordered_map>
#include "Graphics/CameraView.hpp"
#include "Object/Transform.hpp"
#include "Graphics/BitmapFont.hpp"

class CameraView;
class Transform;

namespace Graphics
{
	class BitmapFont;
	class Texture;

    class [[nodiscard]] TextPlatform
    {
    public:
		TextPlatform() noexcept = default;
		TextPlatform(std::wstring text_string, const BitmapFont& text_font) noexcept;

        std::vector<std::pair<const Vertices*, const Texture*>> GetVerticesWithMatchingTextures() const noexcept;
        std::wstring                                            GetString() const noexcept;
        void                                                    SetString(const std::wstring& text_string) noexcept;
        const BitmapFont*                                       GetFont() const noexcept;
        void                                                    SetFont(const BitmapFont& text_font) noexcept;

    private:
        void InitializeWithEmptyVertices() const noexcept;
        void BuildNewMeshesIfNeeded() const noexcept;

    private:
        std::wstring                              string{};
        const BitmapFont*                         font = nullptr;
        mutable std::unordered_map<int, Vertices> vertices{};
        mutable bool                              needNewMeshes = true;
    };
}
