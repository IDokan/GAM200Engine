/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix.hpp
Purpose: Math
Project: Gam200 Project
Author: Hyerin Jung
Created: 08/05/2019
------------------------------------------------------------------------*/
#pragma once
#include "MathLibrary.hpp"

    struct Matrix {
        //===========================================Union For Memory=========================================
        union {
            float Elements[4 * 4];
            vector4 Column[4];
        };
        //=============================================Constructor============================================
        Matrix();
        Matrix(float p_Diagonal);
        //========================================Get Column of Matrix========================================
        vector4 GetColumn(int p_Index) {
            p_Index * 4;
            return vector4(Elements[p_Index], Elements[p_Index + 1], Elements[p_Index + 2], Elements[p_Index + 3]);
        }
        //============================================Multiplication==========================================
        vector2 Multiply(const vector2 &p_Vector) const;
        vector3 Multiply(const vector3 &p_Vector) const;
        vector4 Multiply(const vector4 &p_Vector) const;
        Matrix &Multiply(const Matrix  &p_Matrix);
        //=========================================*= Operator Override=======================================
        Matrix &operator*=(const Matrix &p_Matrix);
        //==========================================* Operator Override=======================================
        friend vector2 operator*(const Matrix &p_LValue, const vector2 &p_RValue);
        friend vector3 operator*(const Matrix &p_LValue, const vector3 &p_RValue);
        friend vector4 operator*(const Matrix &p_LValue, const vector4 &p_RValue);
        friend Matrix  operator*(Matrix p_LValue, const Matrix &p_RValue);
        //============================================Identity Matrix=========================================
        static Matrix Identiy();
        //==============================================Orthographic==========================================
        static Matrix Orthographic(float p_Left, float p_Right, float p_Bottom, float p_Top, float p_Near, float p_Far);
        //==============================================Perspective===========================================
        static Matrix Perspective(float p_FieldOfView, float p_AspectRatio, float p_Near, float p_Far);
        //===============================================Rotation=============================================
        static Matrix Rotate(float p_Angle, const vector3 &p_Axis);
        //===============================================Translate============================================
        static Matrix Translate(const vector3 &p_Translation);
        //=================================================Scale==============================================
        static Matrix Scale(const vector3 &p_Scale);
    };
