/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TextPlatform.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 10.28.2019

	Source file for base text platform used for Text Class
******************************************************************************/
#include <Graphics/BitmapFont.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/StockShaders.hpp>
#include <Graphics/TextPlatform.hpp>

namespace Graphics
{
    TextPlatform::TextPlatform(std::wstring text_string, const BitmapFont& text_font) noexcept : string(text_string), font(&text_font)
    {
        InitializeWithEmptyVertices();
    }

    std::vector<std::pair<const Vertices*, const Texture*>> TextPlatform::GetVerticesWithMatchingTextures() const noexcept
    {
        BuildNewMeshesIfNeeded();
        std::vector<std::pair<const Vertices*, const Texture*>> result;
        for (int i = 0; i < static_cast<int>(vertices.size()); ++i)
        {
            if (vertices.at(i).GetVerticesCount() != 0)
            {
                result.push_back(std::pair<const Vertices*, const Texture*>{&vertices.at(i), &font->GetTexture(i)});
            }
        }
        return result;
    }

    std::wstring TextPlatform::GetString() const noexcept { return string; }

    void TextPlatform::SetString(const std::wstring& text_string) noexcept
    {
        if (string != text_string)
        {
            needNewMeshes = true;
            string        = text_string;
        }
    }

    const BitmapFont* TextPlatform::GetFont() const noexcept { return font; }

    void TextPlatform::SetFont(const BitmapFont& text_font) noexcept
    {
        font = &text_font;
        InitializeWithEmptyVertices();
        needNewMeshes = true;
    }

    void TextPlatform::InitializeWithEmptyVertices() const noexcept
    {
        vertices.clear();

        for (int i = 0; i < font->GetInformation().pagesCount; ++i)
        {
            Vertices tmp;
            Mesh     empty;
            empty.Clear();
            tmp.InitializeWithMeshAndLayout(empty, SHADER::textured_vertex_layout());
            vertices.insert_or_assign(i, std::move(tmp));
        }
    }

    void TextPlatform::BuildNewMeshesIfNeeded() const noexcept
    {
        if (needNewMeshes == false)
        {
            return;
        }

        const BitmapFont::information& information = font->GetInformation();

        for (unsigned short i = 0; i < information.pagesCount; ++i)
        {
            Mesh     mesh;
            Vertices vertice;
            vector2  cursor{0.f};
            for (const auto& element : string)
            {
                const BitmapFont::character& character = font->GetCharacter(element);
                mesh.SetPointListType(PointListPattern::Triangles);

                if (element == L' ')
                {
                    if (font->HasCharacter(wchar_t(' ')))
                    {
                        cursor.x += character.xAdvance;
                    }
                    else
                    {
                        cursor.x += information.fontSize;
                    }
                }
                else if (element == L'\t')
                {
                    if (font->HasCharacter(wchar_t(' ')))
                    {
                        cursor.x = 4.f * character.xAdvance;
                    }
                    else
                    {
                        cursor.x = 4.f * information.fontSize;
                    }
                }
                else if (element == L'\n')
                {
                    cursor.x = 0;
                    cursor.y -= information.lineHeight;
                }
                else if (character.page == i)
                {

                    const float left   = character.xOffset + cursor.x;
                    const float bottom = (character.yOffset + character.height) * -1 + font->GetLineHeight() + cursor.y;
                    const float right  = left + character.width;
                    const float top    = bottom + character.height;

                    const float left_u   = static_cast<float>(character.x) / information.imageWidth;
                    const float right_u  = static_cast<float>(character.x + character.width) / information.imageWidth;
                    const float top_v    = static_cast<float>(character.y) / information.imageHeight;
                    const float bottom_v = static_cast<float>(character.y + character.height) / information.imageHeight;

                    mesh.AddPoint(vector2{left, top});
                    mesh.AddTextureCoordinate(vector2{left_u, top_v});
                    mesh.AddPoint(vector2{right, top});
                    mesh.AddTextureCoordinate(vector2{right_u, top_v});
                    mesh.AddPoint(vector2{left, bottom});
                    mesh.AddTextureCoordinate(vector2{left_u, bottom_v});

                    mesh.AddPoint(vector2{right, top});
                    mesh.AddTextureCoordinate(vector2{right_u, top_v});
                    mesh.AddPoint(vector2{left, bottom});
                    mesh.AddTextureCoordinate(vector2{left_u, bottom_v});
                    mesh.AddPoint(vector2{right, bottom});
                    mesh.AddTextureCoordinate(vector2{right_u, bottom_v});

                    cursor.x += character.xAdvance;
                }
                else
                {
                    cursor.x += character.xAdvance;
                }
            } // Loop End
            vertice.InitializeWithMeshAndLayout(mesh, SHADER::textured_vertex_layout());
            vertices.insert_or_assign(i, std::move(vertice));
        }
        needNewMeshes = false;
    }
}
