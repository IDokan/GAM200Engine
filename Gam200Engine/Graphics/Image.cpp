/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Image.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Source file for GL functions
******************************************************************************/
#include <Graphics/Image.hpp>
#include <cassert>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#pragma warning(push)
#pragma warning(disable : 4505) // unreferenced local function has been removed
#pragma warning(disable : 4100) // unreferenced formal parameter
#include <stb_image.h>
#pragma warning(pop)

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include <stb_image_write.h>

namespace Graphics
{
    void Image::ResizeToPixelWidthHeight(int pixel_width, int pixel_height) noexcept
    {
        if (pixel_width == 0 && pixel_height == 0)
        {
            width = 0;
            height = 0;
            return;
        }
        assert(pixel_width > 0 && pixel_height > 0 && "Safe check for input in ResizeToPixelWidthHeight");

        width  = pixel_width;
        height = pixel_height;

        pixels.resize(width * height);
    }

    bool Image::LoadFromPNG(const std::filesystem::path& file_path) noexcept
    {
        int                  channels = ChannelsPerColor;

        unsigned char* result =
            stbi_load(file_path.generic_string().c_str(), &width, &height, &channels, ChannelsPerColor);

		if (result == nullptr)
        {
                    return false;
        }

        for (int i = 0; i < width * height * ChannelsPerColor; i += ChannelsPerColor)
        {
            Color4ub tmp        = {result[i], result[i + 1], result[i + 2], result[i + 3]};
            pixels.push_back(tmp);
        }

		stbi_image_free(result);

        return result;
    }

    void Image::SaveToPNG(const std::filesystem::path& file_path) const noexcept
    {
        if (pixels.empty())
        {
			return;
        }
		// [-1 points] Your stride bytes is wrong.
        stbi_write_png(file_path.generic_string().c_str(), width, height, ChannelsPerColor,
                       GetPixelsPointer(), width * ChannelsPerColor);
    }

    int Image::GetWidth() const noexcept { return width; }

    int Image::GetHeight() const noexcept { return height; }

    void Image::SetPixel(int column, int row, Color4ub color) noexcept
    {
        assert(column >= 0 && row >= 0);
        assert(column < width && row < height);
        pixels[column + row * width] = color;
    }

    Color4ub* Image::GetPixelsPointer() noexcept
    {
        assert(pixels.empty() == false);
        return &pixels.front();
    }

    const Color4ub* Image::GetPixelsPointer() const noexcept
    {
        assert(pixels.empty() == false);
        return &pixels.front();
    }

    int Image::GetPixelsBufferBytesSize() const noexcept { return static_cast<int>(pixels.size() * sizeof(Color4ub)); }

    void Image::FlipVertically() noexcept
    {
        if (pixels.empty())
        {
            return;
        }

        int      swap1 = 0;
        int      swap2 = 0;
        Color4ub temp{};
        int      heightWithOffset = height - 1;
        for (int row = 0; row < height / 2; ++row)
        {
            for (int column = 0; column < width; ++column)
            {
                swap1 = (heightWithOffset - row) * width + column;
                swap2 = row * width + column;

                temp               = pixels[swap2];
                pixels[swap2] = pixels[swap1];
                pixels[swap1] = temp;
            }
        }
    }
}
