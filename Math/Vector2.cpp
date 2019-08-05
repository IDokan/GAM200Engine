/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector2.cpp
Purpose: Math
Project: Gam200 Project
Author: Hyerin Jung
Created: 08/05/2019
------------------------------------------------------------------------*/

#include"Vector2.hpp"
#include <cassert>
#include <limits>


namespace Math
{
    //==========================Constructor===============================
    vector2::vector2() noexcept : x(0.0f), y(0.0f) {}
    vector2::vector2(float repeated_float) noexcept : x(repeated_float), y(repeated_float) {}
    vector2::vector2(float fx, float fy) noexcept : x(fx), y(fy) {}


    //=========================Operator Override============================
    void operator+=(vector2& v, const vector2& adding_vector) noexcept
    {
        v.x += adding_vector.x;
        v.y += adding_vector.y;
    }

    void operator-=(vector2& v, const vector2& subtracting_vector) noexcept
    {
        v.x -= subtracting_vector.x;
        v.y -= subtracting_vector.y;
    }

    void operator*=(vector2& v, float scale) noexcept
    {
        v = v * scale;
    }

    void operator/=(vector2& v, float divisor) noexcept
    {
        v= v/divisor;
    }


    vector2 operator-(const vector2& v) noexcept
    {
        vector2 minusVector2(-v.x, -v.y);
        return minusVector2;
    }


    vector2 operator+(const vector2& v1, const vector2& v2) noexcept
    {
        return { v1.x + v2.x, v1.y + v2.y };

    }

    vector2 operator-(const vector2& v1, const vector2& v2) noexcept
    {
        return{ v1.x - v2.x, v1.y - v2.y };
    }

    vector2 operator*(const vector2& v, float scale) noexcept
    {
        return {v.x * scale, v.y * scale};
    }

    vector2 operator*(float scale, const vector2& v) noexcept
    {
        return{ scale * v.x, scale * v.y};
    }

    vector2 operator/(const vector2& v, float divisor) noexcept
    {
        assert(divisor != 0.f);
        return{ v.x / divisor, v.y / divisor };
    }

    [[nodiscard]] bool operator==(const vector2& v1, const vector2& v2) noexcept
    {
        if ((std::numeric_limits<float>::epsilon() >= std::abs(v1.x - v2.x)) &&
            (std::numeric_limits<float>::epsilon() >= std::abs(v1.y - v2.y)))
        {
            return true;
        }
        else
            return false;
    }


    [[nodiscard]] bool operator!=(const vector2& v1, const vector2& v2) noexcept
    {
        if ((std::numeric_limits<float>::epsilon() <= std::abs(v1.x - v2.x)) ||
            (std::numeric_limits<float>::epsilon() <= std::abs(v1.y - v2.y)))
        {
            return true;
        }
        else
            return false;
    }

    //==========================Dot Product ==============================
    [[nodiscard]] float dot(vector2 a, vector2 b) noexcept
    {
        float dotProduct2 = a.x * b.x + a.y * b.y;
        return dotProduct2;
    }

    vector2 perpendicular_to(vector2 a) noexcept
    {
        vector2 perpendicularVector(-a.y, a.x);
        return perpendicularVector;
    }

    [[nodiscard]] float magnitude_squared(vector2 a) noexcept
    {
        float squared_magnitude = a.x * a.x + a.y * a.y;
        return squared_magnitude;
    }

    [[nodiscard]] float magnitude(vector2 a) noexcept
    {
        float magnitude = std::sqrt(a.x * a.x + a.y * a.y);
        return magnitude;
    }

    vector2 normalize(vector2 a) noexcept
    {
        float   magnitude = std::sqrt(a.x * a.x + a.y * a.y);
        vector2 normalize = a / magnitude;
        return normalize;
    }


    [[nodiscard]] float distance_between_squared(vector2 a, vector2 b) noexcept
    {
        float distanceSquared = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
        return distanceSquared;
    }


    [[nodiscard]] float distance_between(vector2 a, vector2 b) noexcept
    {
        float distanceSquared = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
        float distance = sqrt(distanceSquared);
        return distance;
    }


    [[nodiscard]] float angle_between(vector2 a, vector2 b) noexcept
    {
        float angleBetween = acos(dot(a, b) / (magnitude(a) * magnitude(b)));
        return angleBetween;
    }


    vector2 rotate_by(float angle_in_radians, vector2 v) noexcept
    {
        vector2 rotateVector;

        rotateVector.x = cos(angle_in_radians) * v.x - sin(angle_in_radians) * v.y;
        rotateVector.y = sin(angle_in_radians) * v.x + cos(angle_in_radians) * v.y;

        return rotateVector;
    }


    //=======================Operator Overidde =========================
    std::ostream &operator<<(std::ostream &p_Stream, const vector2 &p_Vector) {
        p_Stream << "[Vector2] (" << p_Vector.x << ", " << p_Vector.y << ")";
        return p_Stream;
    }


}
