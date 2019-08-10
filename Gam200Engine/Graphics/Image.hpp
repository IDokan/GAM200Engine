/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Image.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Header file for Image
******************************************************************************/
#pragma once
#include <Graphics/Color4ub.hpp>
#include <filesystem>
#include <vector>

namespace Graphics
{
    class [[nodiscard]] Image
    {
    public:
        void ResizeToPixelWidthHeight(int pixel_width, int pixel_height) noexcept;
        bool LoadFromPNG(const std::filesystem::path& file_path) noexcept;
        void SaveToPNG(const std::filesystem::path& file_path) const noexcept;

        int GetWidth() const noexcept;
        int GetHeight() const noexcept;

        void            SetPixel(int column, int row, Color4ub color) noexcept;
        Color4ub*       GetPixelsPointer() noexcept;
        const Color4ub* GetPixelsPointer() const noexcept;
        int             GetPixelsBufferBytesSize() const noexcept;
        void            FlipVertically() noexcept;

    private:
        int                   width  = 0;
        int                   height = 0;
        std::vector<Color4ub> pixels{};

        static const int ChannelsPerColor = 4;
    };
}
