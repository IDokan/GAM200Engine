/*  1. Sinil.gang
 *  2. Camera Programming Assignment
 *  3. CS230
 *  4. Spring 2019
 */

#include "Transform.hpp"
//#include <Graphics/Camera.hpp>
#include <Graphics/Material.hpp>

    Math::matrix3 Transform::GetModelToWorld() const noexcept
    {
        Math::matrix3 currMatrix = Math::MATRIX3::build_translation(translation) * Math::MATRIX3::build_rotation(rotation) * Math::MATRIX3::build_scale(scale);
        
        if (parent == nullptr)
        {
            return currMatrix;
        }

        return parent->GetModelToWorld() * currMatrix;
    }

    // It should be changed
    Math::matrix3 Transform::GetWorldToModel() const noexcept
    {
        Math::matrix3 currMatrix = Math::MATRIX3::build_scale(Math::vector2{1.f / scale.x, 1.f / scale.y}) *
                             Math::MATRIX3::build_rotation(-rotation) * Math::MATRIX3::build_translation(-translation);

        if (parent == nullptr)
        {
            return currMatrix;
        }

        return parent->GetWorldToModel() * currMatrix;
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

Math::vector2 Transform::GetTranslation() const noexcept { return translation; }

    void Transform::SetTranslation(const Math::vector2& new_translation) noexcept { translation = new_translation; }

Math::vector2 Transform::GetScale() const noexcept { return scale; }

    void Transform::SetScale(const Math::vector2& new_scale) noexcept { scale = new_scale; }

    float Transform::GetRotation() const noexcept { return rotation; }

    void Transform::SetRotation(float new_rotation) noexcept { rotation = new_rotation; }

    const Transform* Transform::GetParent() const noexcept { return parent; }

    void Transform::SetParent(const Transform* transform_parent) noexcept { parent = transform_parent; }
