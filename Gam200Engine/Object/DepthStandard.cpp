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

const Depth_Standard Depth_Standard::HUD(-4000.f);
const Depth_Standard Depth_Standard::Particles(-500.f);
const Depth_Standard Depth_Standard::String(-0.999f);
const Depth_Standard Depth_Standard::Player(-11.5f);
const Depth_Standard Depth_Standard::Background(4000.f);