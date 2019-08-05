
/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Angle.hpp
Purpose: Math
Project: Gam200 Project
Author: Hyerin Jung
Created: 08/05/2019
------------------------------------------------------------------------*/

#pragma once
#define _USE_MATH_DEFINES
#include<cmath>

namespace Math
{
    constexpr float PI = M_PI;
    constexpr float TWO_PI = PI * 2.0f;
    constexpr float HALF_PI = PI / 2.0f;
    constexpr float QUARTER_PI = PI / 4.0f;

    constexpr float radian(float angle_in_degrees) { return angle_in_degrees * PI / 180.0f; }
    constexpr float degrees(float angle_in_radian) { return angle_in_radian * 180.0f / PI; }

}