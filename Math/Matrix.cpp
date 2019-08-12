/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix.cpp
Purpose: Math
Project: Gam200 Project
Author: Hyerin Jung
Created: 08/05/2019
------------------------------------------------------------------------*/

#include "Matrix.hpp"

    //=============================================Constructor============================================
    Matrix::Matrix() {
        for (int i = 0; i < 4 * 4; i++) {
            Elements[i] = 0.0f;
        }
    }
    Matrix::Matrix(float p_Diagonal) {
        for (int i = 0; i < 4 * 4; i++) {
            Elements[i] = 0.0f;
        }
        Elements[0 + 0 * 4] = p_Diagonal;
        Elements[1 + 1 * 4] = p_Diagonal;
        Elements[2 + 2 * 4] = p_Diagonal;
        Elements[3 + 3 * 4] = p_Diagonal;
    }
    //============================================Multiplication==========================================
    vector2 Matrix::Multiply(const vector2 &p_Vector) const {
        return vector2(
            Column[0].x * p_Vector.x + Column[1].x * p_Vector.y + Column[2].x + Column[3].x,
            Column[0].y * p_Vector.x + Column[1].y * p_Vector.y + Column[2].y + Column[3].y
        );
    }
    vector3 Matrix::Multiply(const vector3 &p_Vector) const {
        return vector3(
            Column[0].x * p_Vector.x + Column[1].x * p_Vector.y + Column[2].x * p_Vector.z + Column[3].x,
            Column[0].y * p_Vector.x + Column[1].y * p_Vector.y + Column[2].y * p_Vector.z + Column[3].y,
            Column[0].z * p_Vector.x + Column[1].z * p_Vector.y + Column[2].z * p_Vector.z + Column[3].z
        );
    }
    vector4 Matrix::Multiply(const vector4 &p_Vector) const {
        return vector4(
            Column[0].x * p_Vector.x + Column[1].x * p_Vector.y + Column[2].x * p_Vector.z + Column[3].x * p_Vector.w,
            Column[0].y * p_Vector.x + Column[1].y * p_Vector.y + Column[2].y * p_Vector.z + Column[3].y * p_Vector.w,
            Column[0].z * p_Vector.x + Column[1].z * p_Vector.y + Column[2].z * p_Vector.z + Column[3].z * p_Vector.w,
            Column[0].w * p_Vector.x + Column[1].w * p_Vector.y + Column[2].w * p_Vector.z + Column[3].w * p_Vector.w
        );
    }
    Matrix &Matrix::Multiply(const Matrix  &p_Matrix) {
        float MatrixData[16];
        for (int Row = 0; Row < 4; Row++) {
            for (int Column = 0; Column < 4; Column++) {
                float Sum = 0.0f;
                for (int Component = 0; Component < 4; Component++) {
                    Sum += Elements[Column + Component * 4] * p_Matrix.Elements[Component + Row * 4];
                }
                MatrixData[Column + Row * 4] = Sum;
            }
        }
        memcpy(Elements, MatrixData, 4 * 4 * sizeof(float));
        return *this;
    }
    //=========================================*= Operator Override=======================================
    Matrix &Matrix::operator*=(const Matrix &p_Matrix) {
        return Multiply(p_Matrix);
    }
    //==========================================* Operator Override=======================================
    vector2 operator*(const Matrix &p_LValue, const vector2 &p_RValue) {
        return p_LValue.Multiply(p_RValue);
    }
    vector3 operator*(const Matrix &p_LValue, const vector3 &p_RValue) {
        return p_LValue.Multiply(p_RValue);
    }
    vector4 operator*(const Matrix &p_LValue, const vector4 &p_RValue) {
        return p_LValue.Multiply(p_RValue);
    }
    Matrix operator*(Matrix p_LValue, const Matrix &p_RValue) {
        return p_LValue.Multiply(p_RValue);
    }
    //============================================Identity Matrix=========================================
    Matrix Matrix::Identiy() {
        return Matrix(1.0f);
    }
    //==============================================Orthographic==========================================
    Matrix Matrix::Orthographic(float p_Left, float p_Right, float p_Bottom, float p_Top, float p_Near, float p_Far) {
        Matrix Result(1.0f);

        Result.Elements[0 + 0 * 4] = 2.0f / (p_Right - p_Left);
        Result.Elements[1 + 1 * 4] = 2.0f / (p_Top - p_Bottom);
        Result.Elements[2 + 2 * 4] = 2.0f / (p_Near - p_Far);

        Result.Elements[0 + 3 * 4] = (p_Left + p_Right) / (p_Left - p_Right);
        Result.Elements[1 + 3 * 4] = (p_Bottom + p_Top) / (p_Bottom - p_Top);
        Result.Elements[2 + 3 * 4] = (p_Far + p_Near) / (p_Far - p_Near);
        return Result;
    }
    //==============================================Perspective===========================================
    Matrix Matrix::Perspective(float p_FieldOfView, float p_AspectRatio, float p_Near, float p_Far) {
        Matrix Result(1.0f);

        float ValueQ = 1.0f / tan(MATH::Radian(0.5f * p_FieldOfView));
        float ValueA = ValueQ / p_AspectRatio;
        float ValueB = (p_Near + p_Far) / (p_Near - p_Far);
        float ValueC = (2.0f * p_Near * p_Far) / (p_Near - p_Far);

        Result.Elements[0 + 0 * 4] = ValueA;
        Result.Elements[1 + 1 * 4] = ValueQ;
        Result.Elements[2 + 2 * 4] = ValueB;
        Result.Elements[3 + 2 * 4] = -1.0f;
        Result.Elements[2 + 3 * 4] = ValueC;
        return Result;
    }
    //===============================================Rotation=============================================
    Matrix Matrix::Rotate(float p_Angle, const vector3 &p_Axis) {
        Matrix Result(1.0f);

        float ValueX = p_Axis.x;
        float ValueY = p_Axis.y;
        float ValueZ = p_Axis.z;
        float ValueRadian = MATH::Radian(p_Angle);
        float ValueSine = sin(ValueRadian);
        float ValueCosine = cos(ValueRadian);
        float OneMinusCosine = 1.0f - ValueCosine;

        Result.Elements[0 + 0 * 4] = ValueX * OneMinusCosine + ValueCosine;
        Result.Elements[1 + 0 * 4] = ValueX * ValueY * OneMinusCosine + ValueZ * ValueSine;
        Result.Elements[2 + 0 * 4] = ValueX * ValueZ * OneMinusCosine - ValueY * ValueSine;

        Result.Elements[0 + 1 * 4] = ValueX * ValueY * OneMinusCosine - ValueZ * ValueSine;
        Result.Elements[1 + 1 * 4] = ValueY * OneMinusCosine + ValueCosine;
        Result.Elements[2 + 1 * 4] = ValueY * ValueZ * OneMinusCosine + ValueX * ValueSine;

        Result.Elements[0 + 2 * 4] = ValueX * ValueZ * OneMinusCosine + ValueY * ValueSine;
        Result.Elements[1 + 2 * 4] = ValueY * ValueZ * OneMinusCosine - ValueX * ValueSine;
        Result.Elements[2 + 2 * 4] = ValueZ * OneMinusCosine + ValueCosine;
        return Result;
    }
    //===============================================Translate============================================
    Matrix Matrix::Translate(const vector3 &p_Translation) {
        Matrix Result(1.0f);

        Result.Elements[0 + 3 * 4] = p_Translation.x;
        Result.Elements[1 + 3 * 4] = p_Translation.y;
        Result.Elements[2 + 3 * 4] = p_Translation.z;
        return Result;
    }
    //=================================================Scale==============================================
    Matrix Matrix::Scale(const vector3 &p_Scale) {
        Matrix Result(1.0f);

        Result.Elements[0 + 0 * 4] = p_Scale.x;
        Result.Elements[1 + 1 * 4] = p_Scale.y;
        Result.Elements[2 + 2 * 4] = p_Scale.z;
        return Result;
    }