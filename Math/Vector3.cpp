
/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector3.cpp
Purpose: Math
Project: Gam200 Project
Author: Hyerin Jung
Created: 08/05/2019
------------------------------------------------------------------------*/

#include"Vector3.hpp"
#include <cassert>
#include <limits>

namespace Math
{
    vector3::vector3() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
    vector3::vector3(float repeated_float) noexcept : x(repeated_float), y(repeated_float), z(repeated_float) {}
    vector3::vector3(float fx, float fy, float fz) noexcept : x(fx), y(fy), z(fz) {}


    void operator+=(vector3& v, const vector3& adding_vector) noexcept
    {
        v.x += adding_vector.x;
        v.y += adding_vector.y;
        v.z += adding_vector.z;
    }

    void operator-=(vector3& v, const vector3& subtracting_vector) noexcept
    {
        v.x -= subtracting_vector.x;
        v.y -= subtracting_vector.y;
        v.z -= subtracting_vector.z;
    }

    void operator*=(vector3& v, float scale) noexcept
    {
        v = v * scale;
    }

    void operator/=(vector3& v, float divisor) noexcept
    {
        assert(divisor != 0.f);
        v = v / divisor;
    }


    vector3 operator-(const vector3& v) noexcept
    {
        vector3 minusVector3(-v.x, -v.y, -v.z);
        return minusVector3;
    }

    vector3 operator+(const vector3& v1, const vector3& v2) noexcept
    {
        vector3 addVector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
        return addVector3;
    }

    vector3 operator-(const vector3& v1, const vector3& v2) noexcept
    {
        vector3 subtracVector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
        return subtracVector3;
    }

    vector3 operator*(const vector3& v, float scale) noexcept
    {
        vector3 multiplyVectorScale(v.x * scale, v.y * scale, v.z * scale);
        return multiplyVectorScale;
    }
    vector3 operator*(float scale, const vector3& v) noexcept
    {

        vector3 multiplyScaleVector(scale * v.x, scale * v.y, scale * v.z);
        return multiplyScaleVector;
    }

    vector3 operator/(const vector3& v, float divisor) noexcept
    {
        assert(divisor != 0.f);
        vector3 divideVector3(v.x / divisor, v.y / divisor, v.z / divisor);
        return divideVector3;
    }

    [[nodiscard]] bool operator==(const vector3& v1, const vector3& v2) noexcept
    {
        if ((std::numeric_limits<float>::epsilon() >= std::abs(v1.x - v2.x)) &&
            (std::numeric_limits<float>::epsilon() >= std::abs(v1.y - v2.y)) &&
            (std::numeric_limits<float>::epsilon() >= std::abs(v1.z - v2.z)))
        {
            return true;
        }
        else
            return false;
    }
    [[nodiscard]] bool operator!=(const vector3& v1, const vector3& v2) noexcept
    {
        if ((std::numeric_limits<float>::epsilon() <= std::abs(v1.x - v2.x)) ||
            (std::numeric_limits<float>::epsilon() <= std::abs(v1.y - v2.y)) ||
            (std::numeric_limits<float>::epsilon() <= std::abs(v1.z - v2.z)))
        {
            return true;
        }
        else
            return false;
    }

    [[nodiscard]] float dot(vector3 a, vector3 b) noexcept
    {
        float dotProduct3(a.x * b.x + a.y * b.y + a.z * b.z);
        return dotProduct3;
    }

    vector3 cross(vector3 a, vector3 b) noexcept
    {
        vector3 crossVector(a.y*b.z - a.z*b.y, -a.x*b.z + a.z*b.x, a.x*b.y - a.y*b.x);
        return crossVector;
    }

    [[nodiscard]] float magnitude_squared(vector3 a) noexcept
    {
        float squared_magnitude = a.x * a.x + a.y * a.y + a.z * a.z;
        return squared_magnitude;
    }

    [[nodiscard]] float magnitude(vector3 a) noexcept
    {
        float magnitude = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        return magnitude;
    }

    vector3 normalize(vector3 a) noexcept
    {
        float   magnitude = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        vector3 normalize = a / magnitude;
        return normalize;
    }

    [[nodiscard]] float distance_between_squared(vector3 a, vector3 b) noexcept
    {
        float squaredDistance = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
        return squaredDistance;
    }

    [[nodiscard]] float distance_between(vector3 a, vector3 b) noexcept
    {
        float squaredDistance = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
        float distance = std::sqrt(squaredDistance);
        return distance;
    }

    [[nodiscard]] float angle_between(vector3 a, vector3 b) noexcept
    {
        float angleBetween = acos(dot(a, b) / (magnitude(a) * magnitude(b)));
        return angleBetween;
    }

    std::ostream &operator<<(std::ostream &p_Stream, const vector3 &p_Vector) {
        p_Stream << "[Vector3] (" << p_Vector.x << ", " << p_Vector.y << ", " << p_Vector.z << ")";
        return p_Stream;
    }


}