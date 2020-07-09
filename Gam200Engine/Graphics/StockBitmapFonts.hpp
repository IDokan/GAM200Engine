/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StockBitmapFonts.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 10.28.2019

	Header file for Stock files for bitmap fonts
******************************************************************************/
#pragma once

#include <Graphics/BitmapFont.hpp>

namespace Graphics
{
	namespace BITMAPFONTS
	{
		enum class FONTTYPE
		{
			MALGUNGOTHIC,
			SHOWCARDGOTHIC,
			NUMOFFONTTYPE,
		};

		BitmapFont& malgungothic() noexcept;
		BitmapFont& showcardgothic() noexcept;
	}
}

#include "StockBitmapFonts.inl"