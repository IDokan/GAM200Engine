/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Color4f.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.06.2019

	Header file for Color with 4 float
******************************************************************************/
#pragma once
namespace Graphics
{
	class[[nodiscard]] Color4f
	{
	public:
		float red = 0;
		float green = 0;
		float blue = 0;
		float alpha = 1.f;

	public:
		Color4f() noexcept = default;
		Color4f(float grey, float alpha = 1.f) noexcept;
		Color4f(float red, float green, float blue, float alpha = 1.f) noexcept;
	};

	static_assert(sizeof(Color4f) == 16, "Color4f should be 4 floats");

	class Color4ub;

	Color4f to_color4f(const Color4ub& eight_bit_color);

}