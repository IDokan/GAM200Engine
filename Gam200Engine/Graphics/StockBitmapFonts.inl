/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StockBitmapFonts.inl
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 10.28.2019

	Header file for Stock files for bitmap fonts
******************************************************************************/
#pragma once

namespace Graphics
{
	namespace BITMAPFONTS
	{
		inline BitmapFont& malgungothic() noexcept
		{
			static BitmapFont bitmap{ "../assets/fonts/Malgungothic/malgungothic.fnt" };
			return bitmap;
		}
		inline BitmapFont& showcardgothic() noexcept
		{
			static BitmapFont bitmap{ "../assets/fonts/ShowCardGothic/showcardgothic.fnt" };
			return bitmap;
		}
	}
}