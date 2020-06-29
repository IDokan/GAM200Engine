/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   DepthStandard.cpp
Author
		rtd99062@gmail.com
Creation Date: 8th/March/2020

	Source file for depth standards
	Since we know magic number is bad, I make a bunch of floating enum in here
******************************************************************************/
#include <Object/DepthStandard.hpp>

const Depth_Standard Depth_Standard::HUDFrontVFX(-4600.f);
const Depth_Standard Depth_Standard::HUDText(-4500.f);
const Depth_Standard Depth_Standard::HUDImage(-4450.f);
const Depth_Standard Depth_Standard::HUDBackImage(-4425.f);
const Depth_Standard Depth_Standard::HUDBackground(-4400.f);
const Depth_Standard Depth_Standard::HUD(-4000.f);
const Depth_Standard Depth_Standard::Button(-3000.f);
const Depth_Standard Depth_Standard::Particles(-500.f);
const Depth_Standard Depth_Standard::Player(-11.5f);
const Depth_Standard Depth_Standard::MouseAI(-10.f);
const Depth_Standard Depth_Standard::Obstacle(-10.f);
const Depth_Standard Depth_Standard::Jail(-10.f);
const Depth_Standard Depth_Standard::String(-9.f);
const Depth_Standard Depth_Standard::SavedCheese(-8.f);
const Depth_Standard Depth_Standard::Points(-5.f);
const Depth_Standard Depth_Standard::DustVFX(-0.01f);
const Depth_Standard Depth_Standard::NearBackground(3500.f);
const Depth_Standard Depth_Standard::Background(3500.f);
const Depth_Standard Depth_Standard::WoodSign(3800.f);
const Depth_Standard Depth_Standard::FurtherBackground(4000.f);