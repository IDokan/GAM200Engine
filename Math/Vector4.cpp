
/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector4.cpp
Purpose: Math
Project: Gam200 Project
Author: Hyerin Jung
Created: 08/05/2019
------------------------------------------------------------------------*/

#include"Vector4.hpp"
#include <cassert>
#include <limits>

namespace Math
{
    //==========================Constructor===============================
    vector4::vector4() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
    vector4::vector4(float repeated_float) noexcept : x(repeated_float), y(repeated_float), z(repeated_float), w(repeated_float) {}
    vector4::vector4(float fx, float fy, float fz, float fw) noexcept : x(fx), y(fy), z(fz), w(fw) {}

    //=========================Operator Override============================
    void operator+=(vector4& v, const vector4& adding_vector) noexcept
    {
        v.x += adding_vector.x;
        v.y += adding_vector.y;
        v.z += adding_vector.z;
        v.w += adding_vector.w;
    }

    void operator-=(vector4& v, const vector4& subtracting_vector) noexcept
    {
        v.x -= subtracting_vector.x;
        v.y -= subtracting_vector.y;
        v.z -= subtracting_vector.z;
        v.w += subtracting_vector.w;
    }

    void operator*=(vector4& v, float scale) noexcept
    {
        v = v * scale;
    }

    void operator/=(vector4& v, float divisor) noexcept
    {
        assert(divisor != 0.f);
        v = v / divisor;
    }


    vector4 operator-(const vector4& v) noexcept
    {
        vector4 minusvector4(-v.x, -v.y, -v.z,-v.w);
        return minusvector4;
    }

    vector4 operator+(const vector4& v1, const vector4& v2) noexcept
    {
        vector4 addvector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z,v1.w+v2.w);
        return addvector4;
    }

    vector4 operator-(const vector4& v1, const vector4& v2) noexcept
    {
        vector4 subtracvector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z,v1.w-v2.w);
        return subtracvector4;
    }

    vector4 operator*(const vector4& v, float scale) noexcept
    {
        vector4 multiplyVectorScale(v.x * scale, v.y * scale, v.z * scale,v.w*scale);
        return multiplyVectorScale;
    }
    vector4 operator*(float scale, const vector4& v) noexcept
    {

        vector4 multiplyScaleVector(scale * v.x, scale * v.y, scale * v.z, scale*v.w);
        return multiplyScaleVector;
    }

    vector4 operator/(const vector4& v, float divisor) noexcept
    {
        assert(divisor != 0.f);
        vector4 dividevector4(v.x / divisor, v.y / divisor, v.z / divisor, v.w/divisor);
        return dividevector4;
    }

    [[nodiscard]] bool operator==(const vector4& v1, const vector4& v2) noexcept
    {
        if ((std::numeric_limits<float>::epsilon() >= std::abs(v1.x - v2.x)) &&
            (std::numeric_limits<float>::epsilon() >= std::abs(v1.y - v2.y)) &&
            (std::numeric_limits<float>::epsilon() >= std::abs(v1.z - v2.z)) &&
            (std::numeric_limits<float>::epsilon() >= std::abs(v1.w-v2.w)))
        {
            return true;
        }
        else
            return false;
    }
    [[nodiscard]] bool operator!=(const vector4& v1, const vector4& v2) noexcept
    {
        if ((std::numeric_limits<float>::epsilon() <= std::abs(v1.x - v2.x)) ||
            (std::numeric_limits<float>::epsilon() <= std::abs(v1.y - v2.y)) ||
            (std::numeric_limits<float>::epsilon() <= std::abs(v1.z - v2.z)) ||
            (std::numeric_limits<float>::epsilon() >= std::abs(v1.w - v2.w)))
        {
            return true;
        }
        else
            return false;
    }


    //==========================Dot Product ==============================
    [[nodiscard]] float dot(vector4 a, vector4 b) noexcept
    {
        float dotProduct4(a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
        return dotProduct4;
    }

    //===========================Scale=================================
    [[nodiscard]] float magnitude_squared(vector4 a) noexcept
    {
        float squared_magnitude = a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
        return squared_magnitude;
    }

    [[nodiscard]] float magnitude(vector4 a) noexcept
    {
        float magnitude = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z+a.w * a.w);
        return magnitude;
    }

    vector4 normalize(vector4 a) noexcept
    {
        float   magnitude = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
        return a/magnitude;
    }

    //===========================Distance===============================
    [[nodiscard]] float distance_between_squared(vector4 a, vector4 b) noexcept
    {
        float squaredDistance = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z) + (a.w-b.w)*(a.w - b.w);
        return squaredDistance;
    }

    [[nodiscard]] float distance_between(vector4 a, vector4 b) noexcept
    {
        float squaredDistance = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z) + (a.w - b.w)*(a.w - b.w);
        float distance = std::sqrt(squaredDistance);
        return distance;
    }

    //===========================Angle=================================
    [[nodiscard]] float angle_between(vector4 a, vector4 b) noexcept
    {
        float angleBetween = acos(dot(a, b) / (magnitude(a) * magnitude(b)));
        return angleBetween;
    }

    //====================<< Operator Override=============================
    std::ostream &operator<<(std::ostream &p_Stream, const vector4 &p_Vector) {
        p_Stream << "[vector4] (" << p_Vector.x << ", " << p_Vector.y << ", " << p_Vector.z <<", "<<p_Vector.w<< ")";
        return p_Stream;
    }


}