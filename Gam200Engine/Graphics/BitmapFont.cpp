/*  1. sinil.gang
 *  2. text assignment
 *  3. CS230
 *  4. Spring 2019
 */
#include <Graphics/BitmapFont.hpp>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>


namespace Graphics
{
	BitmapFont::BitmapFont(const std::filesystem::path& filename)
	{
		characters.clear();
		pageTextures.clear();
		if (LoadFromFile(filename) == false)
		{
			//std::cerr << "Falied to load file!" << std::endl;
		}
		
	}

    bool BitmapFont::LoadFromFile(const std::filesystem::path& filename)
    {
        if (CanParseFile(filename) == false)
        {
            return false;
        }

        for (int count = 0; count < details.pagesCount; ++count)
        {
            Texture               texture;
            std::filesystem::path directory = filename.parent_path();
            directory.append(details.pageNames.at(count));
            pageTextures.emplace_back();
            if (pageTextures.at(count).LoadFromPNG(directory) == false)
            {
                return false;
            }
        }
        return true;
    }

    bool BitmapFont::LoadDefinition(const std::wstring& font_definition, std::vector<Texture> page_textures)
    {
        std::wistringstream stream(font_definition);
        if (!CanParseStream(stream))
            return false;
        pageTextures = std::move(page_textures);
        return pageTextures.size() == details.pagesCount;
    }

    const BitmapFont::information& BitmapFont::GetInformation() const noexcept { return details; }

    BitmapFont::character BitmapFont::GetCharacter(wchar_t character_id) const noexcept
    {
        if (HasCharacter(character_id))
        {
            return characters.at(character_id);
        }
        if (HasCharacter(wchar_t(-1)))
        {
            return characters.at(wchar_t(-1));
        }
        return character{};
    }

    unsigned short BitmapFont::GetLineHeight() const noexcept { return details.lineHeight; }

    const Texture& BitmapFont::GetTexture(int page_index) const noexcept
    {
        assert(pageTextures.empty() == false);
        assert(page_index >= 0 && page_index < static_cast<int>(pageTextures.size()));
        return pageTextures.at(page_index);
    }

    bool BitmapFont::HasCharacter(wchar_t character_id) const noexcept
    {
        const auto & it = characters.find(character_id);
        return it != characters.end();
    }

    bool BitmapFont::CanParseFile(const std::filesystem::path& filename)
    {
        std::wifstream stream(filename);
        if (stream.is_open())
        {
            return CanParseStream(stream);
        }
        return false;
    }

    bool BitmapFont::CanParseStream(std::wistream& stream)
    {
        std::wstring line;
        std::wstring read, key, value;
        std::size_t  i;

        while (!stream.eof())
        {
            std::wstringstream lineStream;
            std::getline(stream, line);
            lineStream << line;

            // Read the line's type
            lineStream >> read;
            if (read == L"info")
            {
                // this holds common data
                while (!lineStream.eof())
                {
                    lineStream >> read;

                    i     = read.find('=');
                    key   = read.substr(0, i);
                    value = read.substr(i + 1);

                    if (key == L"face")
                    {
                        std::size_t  count1   = line.find('\"');
                        std::size_t  count2   = line.find('\"', count1 + 1);
                        std::wstring fontName = line.substr(count1, count2 - count1 + 1);
                        details.fontName      = fontName;
                    }
                    else if (key == L"size")
                    {

                        std::wstringstream converter;
                        converter << value;
                        converter >> details.fontSize;
                    }
                }
            }
            if (read == L"char")
            {
                character ch;
                // this holds common data
                while (!lineStream.eof())
                {
                    lineStream >> read;

                    i     = read.find('=');
                    key   = read.substr(0, i);
                    value = read.substr(i + 1);

                    std::wstringstream converter;
                    converter << value;

                    if (key == L"id")
                    {
                        ch.id = wchar_t(std::stoi(value));
                    }
                    else if (key == L"x")
                    {
                        converter >> ch.x;
                    }
                    else if (key == L"y")
                    {
                        converter >> ch.y;
                    }
                    else if (key == L"width")
                    {
                        converter >> ch.width;
                    }
                    else if (key == L"height")
                    {
                        converter >> ch.height;
                    }
                    else if (key == L"xoffset")
                    {
                        converter >> ch.xOffset;
                    }
                    else if (key == L"yoffset")
                    {
                        converter >> ch.yOffset;
                    }
                    else if (key == L"xadvance")
                    {
                        converter >> ch.xAdvance;
                    }
                    else if (key == L"page")
                    {
                        unsigned short container;
                        converter >> container;
                        ch.page = static_cast<unsigned char>(container);
                    }
                }
                characters.insert_or_assign(ch.id, ch);
            }
            if (read == L"common")
            {
                // this holds common data
                while (!lineStream.eof())
                {
                    lineStream >> read;

                    i     = read.find('=');
                    key   = read.substr(0, i);
                    value = read.substr(i + 1);

                    // assign the correct value
                    // I try with another way
                    std::wstringstream converter;
                    converter << value;
                    if (key == L"lineHeight")
                    {
                        converter >> details.lineHeight;
                    }
                    else if (key == L"scaleW")
                    {
                        converter >> details.imageWidth;
                    }
                    else if (key == L"scaleH")
                    {
                        converter >> details.imageHeight;
                    }
                    else if (key == L"pages")
                    {
                        converter >> details.pagesCount;
                        details.pageNames.resize(details.pagesCount);
                    }
                }
            }
            if (read == L"page")
            {
                std::wstring id      = L"id";
                std::size_t  idCount = line.find(id);
                // (i, d, =) -> 3
                std::size_t  idStart = idCount + 3;
                std::size_t  idEnd   = line.find(' ', idStart);
                std::wstring idValue = line.substr(idStart, idEnd - idStart);

                std::wstring file      = L"file";
                std::size_t  fileCount = line.find(file);
                // (f, i, l, e, =, ") -> 6
                std::size_t  fileStart = fileCount + 6;
                std::size_t  fileEnd   = line.find('\"', fileStart);
                std::wstring fileValue = line.substr(fileStart, fileEnd - fileStart);

                unsigned short castedId = static_cast<unsigned short>(std::stoi(idValue));
                details.pageNames.at(castedId) = fileValue;
            }
        }
        return true;
    }
}
