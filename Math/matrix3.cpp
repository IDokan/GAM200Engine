/*******************************************************************************
1. sinil.gang
2. Math Programming Assignment
3. CS230
4. Spring 2019

*******************************************************************************/


#include "matrix3.hpp"
#include "Vector2.hpp"
#include <cassert> // for assert()
#include <limits>

#include <cmath> // for std::cos(), std::sin()
#include "Angle.hpp"    // for PI, HALF_PI

    matrix3::matrix3() noexcept : column0(0), column1(0), column2(0) {}

    matrix3::matrix3(vector3 first_column, vector3 second_column, vector3 third_column) noexcept
        : column0(first_column), column1(second_column), column2(third_column)
    {
    }

    matrix3::matrix3(float column0_row0, float column0_row1, float column0_row2, float column1_row0, float column1_row1,
                     float column1_row2, float column2_row0, float column2_row1, float column2_row2) noexcept
    :   column0(column0_row0, column0_row1, column0_row2), 
        column1(column1_row0, column1_row1, column1_row2),
        column2(column2_row0, column2_row1, column2_row2)
    {
    }

    float matrix3::operator()(int column, int row) const noexcept
    {
        // Check validation of column & row
        assert(column >= 0 && column < 3 && "Column calls invalidation");
        assert(row >= 0 && row < 3 && "Row calls invalidation");
        return elements[column][row];
    }

    float& matrix3::operator()(int column, int row) noexcept
    {
        // Check validation of column & row
        assert(column >= 0 && column < 3 && "Column calls invalidation");
        assert(row >= 0 && row < 3 && "Row calls invalidation");
        return elements[column][row];
    }

    matrix3 operator*(const matrix3& m1, const matrix3& m2) noexcept
    {
        return matrix3(
            m1(0, 0) * m2(0, 0) + m1(1, 0) * m2(0, 1) + m1(2, 0) * m2(0, 2),
            m1(0, 1) * m2(0, 0) + m1(1, 1) * m2(0, 1) + m1(2, 1) * m2(0, 2),
            m1(0, 2) * m2(0, 0) + m1(1, 2) * m2(0, 1) + m1(2, 2) * m2(0, 2),
            m1(0, 0) * m2(1, 0) + m1(1, 0) * m2(1, 1) + m1(2, 0) * m2(1, 2),
            m1(0, 1) * m2(1, 0) + m1(1, 1) * m2(1, 1) + m1(2, 1) * m2(1, 2),
            m1(0, 2) * m2(1, 0) + m1(1, 2) * m2(1, 1) + m1(2, 2) * m2(1, 2),
            m1(0, 0) * m2(2, 0) + m1(1, 0) * m2(2, 1) + m1(2, 0) * m2(2, 2),
            m1(0, 1) * m2(2, 0) + m1(1, 1) * m2(2, 1) + m1(2, 1) * m2(2, 2),
            m1(0, 2) * m2(2, 0) + m1(1, 2) * m2(2, 1) + m1(2, 2) * m2(2, 2));
    }

    void operator*=(matrix3& m1, const matrix3& m2) noexcept { m1 = m1 * m2; }

    vector3 operator*(const matrix3& m, vector3 v) noexcept
    {
        return vector3(
            m(0, 0) * v.x + m(1, 0) * v.y + m(2, 0) * v.z, 
            m(0, 1) * v.x + m(1, 1) * v.y + m(2, 1) * v.z,
            m(0, 2) * v.x + m(1, 2) * v.y + m(2, 2) * v.z);
    }

    matrix3 MATRIX3::transpose(const matrix3& m) noexcept
    {
        return matrix3(
            m(0, 0), m(1, 0), m(2, 0), 
            m(0, 1), m(1, 1), m(2, 1), 
            m(0, 2), m(1, 2), m(2, 2));
    }

    matrix3 MATRIX3::build_rotation(float angle_in_radians) noexcept
    {
        // Return specific matrix at specific parameter without calculation.
        if (angle_in_radians <= std::numeric_limits<float>::epsilon())
        {
            return build_identity();
        }
        else if (angle_in_radians <= MATH::HALF_PI + std::numeric_limits<float>::epsilon() && 
                    angle_in_radians >= MATH::HALF_PI - std::numeric_limits<float>::epsilon())
        {
            return matrix3(
				0, 1, 0, 
				-1, 0, 0, 
				0, 0, 1);
        }
        else if (angle_in_radians <= MATH::PI + std::numeric_limits<float>::epsilon() &&
                    angle_in_radians >= MATH::PI - std::numeric_limits<float>::epsilon())
        {
            return matrix3(
				-1, 0, 0, 
				0, -1, 0, 
				0, 0, 1);
        }
        else if (angle_in_radians <= MATH::PI + MATH::HALF_PI + std::numeric_limits<float>::epsilon() &&
                    angle_in_radians >= MATH::PI + MATH::HALF_PI - std::numeric_limits<float>::epsilon())
        {
            return matrix3(
				0, -1, 0, 
				1, 0, 0, 
				0, 0, 1);
        }

        const float cos = std::cos(angle_in_radians);
        const float sin = std::sin(angle_in_radians);

        // If not, calculate followed parameter.
        return matrix3 (
            cos, sin, 0,
            -sin, cos, 0, 
            0, 0, 1);
    }

    matrix3 MATRIX3::build_identity() noexcept
    {
        return matrix3(
            1, 0, 0, 
            0, 1, 0, 
            0, 0, 1);
    }

    matrix3 MATRIX3::build_scale(float scale_x, float scale_y) noexcept
    {
        return matrix3(
            scale_x, 0, 0, 
            0, scale_y, 0, 
            0, 0, 1);
    }

    matrix3 MATRIX3::build_scale(float scale) noexcept { return MATRIX3::build_scale(scale, scale); }

    matrix3 MATRIX3::build_scale(const vector2& scale) noexcept { return MATRIX3::build_scale(scale.x, scale.y); }

    matrix3 MATRIX3::build_translation(float translate_x, float translate_y) noexcept
    {
        return matrix3(
            1, 0, 0, 
            0, 1, 0, 
            translate_x, translate_y, 1);
    }

    matrix3 MATRIX3::build_translation(const vector2& translation) noexcept
    {
        return MATRIX3::build_translation(translation.x, translation.y);
    }