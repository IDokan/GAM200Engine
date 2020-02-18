/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   DepthStandard.hpp
Author
		dbsqhd106@gmail.com
Creation Date: 23th/Jan/2020

	Header file for depth standards
	Since we know magic number is bad, I make a bunch of floating enum in here
******************************************************************************/

#pragma once

class Depth_Standard
{
	float value;
	Depth_Standard(float arg) : value(arg) {}
public:
	static const Depth_Standard HUD;
	static const Depth_Standard Player;
	static const Depth_Standard Background;
	static const Depth_Standard Particles;
	operator float() const { return value; }
};
const Depth_Standard Depth_Standard::HUD(-4000.f);
const Depth_Standard Depth_Standard::Particles(-500.f);
const Depth_Standard Depth_Standard::Player(-1.f);
const Depth_Standard Depth_Standard::Background(4000.f);