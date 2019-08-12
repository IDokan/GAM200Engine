
/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector4.hpp
Purpose: Math
Project: Gam200 Project
Author: Hyerin Jung
Created: 08/05/2019
------------------------------------------------------------------------*/

#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
#include <ostream>

    struct[[nodiscard]] vector4
    {
        union {
            struct
            {
                float x, y, z, w;
            };
            struct
            {
                float r, g, b, a;
            };

            float elements[4];
        };
    //==========================Constructor===============================
        vector4() noexcept;
        explicit vector4(float repeated_float) noexcept;
        vector4(float fx, float fy, float fz, float fw) noexcept;
    };

    //=========================Check vector is 4D============================
    static_assert(sizeof(vector4) == sizeof(float) * 4, "vector4 should only be three floats");

    //=========================Operator Override============================
    void operator+=(vector4& v, const vector4& adding_vector) noexcept;
    void operator-=(vector4& v, const vector4& subtracting_vector) noexcept;
    void operator*=(vector4& v, float scale) noexcept;
    void operator/=(vector4& v, float divisor) noexcept;

    vector4 operator-(const vector4& v) noexcept;

    vector4 operator+(const vector4& v1, const vector4& v2) noexcept;
    vector4 operator-(const vector4& v1, const vector4& v2) noexcept;
    vector4 operator*(const vector4& v, float scale) noexcept;
    vector4 operator*(float scale, const vector4& v) noexcept;
    vector4 operator/(const vector4& v, float divisor) noexcept;

    [[nodiscard]] bool operator==(const vector4& v1, const vector4& v2) noexcept;
    [[nodiscard]] bool operator!=(const vector4& v1, const vector4& v2) noexcept;

    //==========================Dot Product ==============================
    [[nodiscard]] float dot(vector4 a, vector4 b) noexcept;

    //===========================Scale=================================
    [[nodiscard]] float magnitude_squared(vector4 a) noexcept;
    [[nodiscard]] float magnitude(vector4 a) noexcept;
    vector4             normalize(vector4 a) noexcept;

    //===========================Distance===============================
    [[nodiscard]] float distance_between_squared(vector4 a, vector4 b) noexcept;
    [[nodiscard]] float distance_between(vector4 a, vector4 b) noexcept;

    //===========================Angle=================================
    [[nodiscard]] float angle_between(vector4 a, vector4 b) noexcept;

    //====================<< Operator Override=============================
    std::ostream &operator<<(std::ostream &p_Stream, const vector4 &p_Vector);

#pragma warning(pop)
