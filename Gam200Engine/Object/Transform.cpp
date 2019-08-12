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

#include "Transform.hpp"
#include <Graphics/Camera.hpp>
#include <Graphics/Material.hpp>

     matrix3 Transform::GetModelToWorld() const noexcept
    {
         matrix3 currMatrix =  MATRIX3::build_translation(translation) *  MATRIX3::build_rotation(rotation) *  MATRIX3::build_scale(scale);
        
        if (parent == nullptr)
        {
            return currMatrix;
        }

        return parent->GetModelToWorld() * currMatrix;
    }
	 
     matrix3 Transform::GetWorldToModel() const noexcept
    {
         matrix3 currMatrix =  MATRIX3::build_scale( vector2{1.f / scale.x, 1.f / scale.y}) *
                              MATRIX3::build_rotation(-rotation) *  MATRIX3::build_translation(-translation);

        if (parent == nullptr)
        {
            return currMatrix;
        }

        return currMatrix * parent->GetWorldToModel();
    }

    float Transform::CalculateWorldDepth() const noexcept
    {
        if (parent == nullptr)
        {
            return GetDepth();
        }
        return GetDepth() + parent->CalculateWorldDepth();
    }

    float Transform::GetDepth() const noexcept { return depth; }

    void Transform::SetDepth(float new_depth) noexcept { depth = new_depth; }

 vector2 Transform::GetTranslation() const noexcept { return translation; }

    void Transform::SetTranslation(const  vector2& new_translation) noexcept { translation = new_translation; }

 vector2 Transform::GetScale() const noexcept { return scale; }

    void Transform::SetScale(const  vector2& new_scale) noexcept { scale = new_scale; }

    float Transform::GetRotation() const noexcept { return rotation; }

    void Transform::SetRotation(float new_rotation) noexcept { rotation = new_rotation; }

    const Transform* Transform::GetParent() const noexcept { return parent; }

    void Transform::SetParent(const Transform* transform_parent) noexcept { parent = transform_parent; }
