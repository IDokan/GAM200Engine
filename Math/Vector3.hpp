
/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector3.hpp
Purpose: Math
Project: Gam200 Project
Author: Hyerin Jung
Created: 08/05/2019
------------------------------------------------------------------------*/
#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
#include <ostream>

namespace Math
{
    struct[[nodiscard]] vector3
    {
        union {
            struct
            {
                float x, y, z;
            };
            struct
            {
                float r, g, b;
            };
            struct
            {
                float width, height, depth;
            };
            float elements[3];
        };
    //========================Constructor=================================
        vector3() noexcept;
        explicit vector3(float repeated_float) noexcept;
        vector3(float fx, float fy, float fz) noexcept;
    };

    //=========================Check vector is 3D============================
    static_assert(sizeof(vector3) == sizeof(float) * 3, "vector3 should only be three floats");


    //=========================Operator Override============================
    void operator+=(vector3& v, const vector3& adding_vector) noexcept;
    void operator-=(vector3& v, const vector3& subtracting_vector) noexcept;
    void operator*=(vector3& v, float scale) noexcept;
    void operator/=(vector3& v, float divisor) noexcept;

    vector3 operator-(const vector3& v) noexcept;

    vector3 operator+(const vector3& v1, const vector3& v2) noexcept;
    vector3 operator-(const vector3& v1, const vector3& v2) noexcept;
    vector3 operator*(const vector3& v, float scale) noexcept;
    vector3 operator*(float scale, const vector3& v) noexcept;
    vector3 operator/(const vector3& v, float divisor) noexcept;

    [[nodiscard]] bool operator==(const vector3& v1, const vector3& v2) noexcept;
    [[nodiscard]] bool operator!=(const vector3& v1, const vector3& v2) noexcept;

    //==========================Dot Product ==============================
    [[nodiscard]] float dot(vector3 a, vector3 b) noexcept;
    vector3             cross(vector3 a, vector3 b) noexcept;

    //===========================Scale==================================
    [[nodiscard]] float magnitude_squared(vector3 a) noexcept;
    [[nodiscard]] float magnitude(vector3 a) noexcept;
    vector3             normalize(vector3 a) noexcept;

    //===========================Distance===============================
    [[nodiscard]] float distance_between_squared(vector3 a, vector3 b) noexcept;
    [[nodiscard]] float distance_between(vector3 a, vector3 b) noexcept;

    //===========================Angle=================================
    [[nodiscard]] float angle_between(vector3 a, vector3 b) noexcept;

    //====================<< Operator Override=============================
    std::ostream &operator<<(std::ostream &p_Stream, const vector3 &p_Vector);
}
#pragma warning(pop)