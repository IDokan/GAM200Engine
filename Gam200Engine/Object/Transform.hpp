/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Transform.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.12.2019

	Source file for Object's Transform
******************************************************************************/
#pragma once
#include <matrix3.hpp>
#include <vector2.hpp>

    class [[nodiscard]] Transform
    {
    public:
        Transform() noexcept = default;
         matrix3 GetModelToWorld() const noexcept;
         matrix3 GetWorldToModel() const noexcept;

        float CalculateWorldDepth() const noexcept;
        float GetDepth() const noexcept;
        void  SetDepth(float new_depth) noexcept;

         vector2 GetTranslation() const noexcept;
        void    SetTranslation(const  vector2& new_translation) noexcept;

         vector2 GetScale() const noexcept;
        void    SetScale(const  vector2& new_scale) noexcept;

        float GetRotation() const noexcept;
        void  SetRotation(float new_rotation) noexcept;

        const Transform* GetParent() const noexcept;
        void             SetParent(const Transform* transform_parent) noexcept;

    private:
         vector2          translation{};
         vector2          scale{1.0f, 1.0f};
        float            rotation = 0.0f;
        float            depth    = 0.0f;
        const Transform* parent   = nullptr;
    };