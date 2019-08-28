/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Texture.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Source file for GL functions
******************************************************************************/
#include <Graphics/Image.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/glCheck.hpp>
#include <GL/glew.h>
#include <cassert>
#include <filesystem>
#include <unordered_map>

namespace
{
	static std::unordered_map<std::string, Graphics::Texture*> imageStorage;
}

namespace Graphics
{
    bool Texture::LoadFromPNG(const std::filesystem::path& file_path) noexcept
    {
		bool returnValue;
		Image image;
		if (imageStorage.find(file_path.string()) == imageStorage.end())
		{
			if (image.LoadFromPNG(file_path) == false)
			{
				return false;
			}

			returnValue = LoadFromImage(image);

			imageStorage.insert_or_assign(file_path.string(), this);
		}
		else
		{
			Texture* loadedTexture = imageStorage.at(file_path.string());
			textureHandle = loadedTexture->textureHandle;
			width = loadedTexture->width;
			height = loadedTexture->height;
			returnValue = true;
		}

        return returnValue;
    }

    bool Texture::LoadFromImage(const Image& image) noexcept
    {
        return LoadFromMemory(image.GetWidth(), image.GetHeight(), image.GetPixelsPointer());
    }

    bool Texture::LoadFromMemory(int image_width, int image_height, const Color4ub* colors) noexcept
    {
        assert(colors != nullptr);
        assert(image_width > 0 && image_height > 0);

            if (textureHandle != 0)
        {
            DeleteTexture();
        }

        width  = image_width;
        height = image_height;

        glCheck(glGenTextures(1, &textureHandle));
        if (textureHandle == 0)
        {
            return true;
        }

        glCheck(glBindTexture(GL_TEXTURE_2D, textureHandle));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        glCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, colors));
        
        return !glGetError();
    }

    void Texture::SelectTextureForSlot(const Texture& texture, unsigned slot) noexcept
    {
        if (texture.GetTextureHandle() == 0)
        {
            return;
        }
        assert(slot < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
        glCheck(glActiveTexture(GL_TEXTURE0 + slot));
        glCheck(glBindTexture(GL_TEXTURE_2D, texture.GetTextureHandle()));
    }

    void Texture::DeleteTexture() noexcept
    {
        if (textureHandle == 0)
        {
            return;
        }
        glCheck(glDeleteTextures(1, &textureHandle));
        textureHandle = 0;
    }

    Texture::~Texture() noexcept { DeleteTexture(); }

    Texture::Texture(Texture&& other) noexcept
        : textureHandle{other.textureHandle}, width{other.width}, height{other.height}
    {
        other.textureHandle = 0;
        other.width         = 0;
        other.height        = 0;
    }

    Texture& Texture::operator=(Texture&& other) noexcept
    {
        if (this == &other)
            return *this;
        DeleteTexture();
        textureHandle       = other.textureHandle;
        width               = other.width;
        height              = other.height;
        other.textureHandle = 0;
        other.width         = 0;
        other.height        = 0;
        return *this;
    }
}
