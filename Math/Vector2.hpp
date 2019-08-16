/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector2.hpp
Purpose: Math
Project: Gam200 Project
Author: Hyerin Jung
Created: 08/05/2019
------------------------------------------------------------------------*/

#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
#include <ostream>


    struct[[nodiscard]] vector2
    {
        union {
            struct
            {
                float x, y;
            };
            struct
            {
                float u, v;
            };
            struct
            {
                float width, height;
            };
            float elements[2];
        };

        //==========================Constructor===============================
        vector2() noexcept;
        explicit vector2(float repeated_float) noexcept;
        vector2(float fx, float fy) noexcept;
    };

    //=========================Check vector is 2D===================
    static_assert(sizeof(vector2) == sizeof(float) * 2, "vector2 should only be two floats");

    //=========================Operator Override============================
    void operator+=(vector2& v, const vector2& adding_vector) noexcept;
    void operator-=(vector2& v, const vector2& subtracting_vector) noexcept;
    void operator*=(vector2& v, float scale) noexcept;
    void operator/=(vector2& v, float divisor) noexcept;

    vector2 operator-(const vector2& v) noexcept;

    vector2 operator+(const vector2& v1, const vector2& v2) noexcept;
    vector2 operator-(const vector2& v1, const vector2& v2) noexcept;
    vector2 operator*(const vector2& v, float scale) noexcept;
    vector2 operator*(float scale, const vector2& v) noexcept;
    vector2 operator/(const vector2& v, float divisor) noexcept;

    [[nodiscard]] bool operator==(const vector2& v1, const vector2& v2) noexcept;
    [[nodiscard]] bool operator!=(const vector2& v1, const vector2& v2) noexcept;

    //==========================Dot Product ==============================
    [[nodiscard]] float dot(vector2 a, vector2 b) noexcept;


    //============================Perpendicular===========================
    vector2             perpendicular_to(vector2 a) noexcept;


    //===========================Scale=================================
    [[nodiscard]] float magnitude_squared(vector2 a) noexcept;
    [[nodiscard]] float magnitude(vector2 a) noexcept;
    vector2             normalize(vector2 a) noexcept;

    //===========================Distance===============================
    [[nodiscard]] float distance_between_squared(vector2 a, vector2 b) noexcept;
    [[nodiscard]] float distance_between(vector2 a, vector2 b) noexcept;

    //===========================Angle=================================
    [[nodiscard]] float angle_between(vector2 a, vector2 b) noexcept;
    vector2             rotate_by(float angle_in_radians, vector2 v) noexcept;

    //====================<< Operator Override=============================
    std::ostream &operator<<(std::ostream &p_Stream, const vector2 &p_Vector);



#pragma warning(pop)