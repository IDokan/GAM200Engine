/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   DepthStandard.hpp
Author
		rtd99062@gmail.com
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
	static const Depth_Standard TransitionHUD;
	static const Depth_Standard HUDFrontVFX;
	static const Depth_Standard HUD;
	static const Depth_Standard WoodSign;
	static const Depth_Standard String;
	static const Depth_Standard Player;
	static const Depth_Standard MouseAI;
	static const Depth_Standard Points;
	static const Depth_Standard Obstacle;
	static const Depth_Standard Jail;
	static const Depth_Standard CheckPoint;
	static const Depth_Standard SavedCheese;
	static const Depth_Standard Button;
	static const Depth_Standard NearBackground;
	static const Depth_Standard Background;
	static const Depth_Standard DustVFX;
	static const Depth_Standard ColdVFX;
	static const Depth_Standard FurtherBackground;
	static const Depth_Standard Particles;
	static const Depth_Standard HUDBackground;
	static const Depth_Standard HUDBackImage;
	static const Depth_Standard HUDImage;
	static const Depth_Standard HUDText;
	operator float() const { return value; }
};