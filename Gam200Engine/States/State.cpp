/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   State.cpp
Author
		rtd99062@gmail.com
Creation Date: 12.10.2019

	Source file for the abstract class for all of state
******************************************************************************/
#include <States/State.hpp>

#include <Object/ObjectManager.hpp>
#include <Graphics/GL.hpp>
// Include Components
#include <Component/Sprite.hpp>
#include <Component/StringSprite.hpp>
#include <Component/TextComponent.hpp>


void State::Draw() const noexcept
{
	Graphics::GL::begin_drawing();

	for (const auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
	{
		element->SortingDepth();
		for (const auto& obj : element->GetObjContainer())
		{
			if (const auto & stringSprite = obj.get()->GetComponentByTemplate<StringSprite>())
			{
				// Incomplete one
				const auto matrix = cameraManager.GetWorldToNDCTransform();
				stringSprite->UpdateUniforms(matrix,
					obj.get()->GetTransform().CalculateWorldDepth());
				Graphics::GL::draw(*stringSprite->GetVertices(), *stringSprite->GetMaterial());
			}
			else if (const auto & sprite = obj.get()->GetComponentByTemplate<Sprite>())
			{
				const auto matrix = cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld();
				sprite->UpdateUniforms(matrix,
					obj.get()->GetTransform().CalculateWorldDepth());
				Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());
			}
			if (const auto & text = obj.get()->GetComponentByTemplate<TextComponent>())
			{
				const auto matrix = cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld();
				text->Draw(matrix,
					obj.get()->GetTransform().CalculateWorldDepth());
			}
		}
	}
	Graphics::GL::end_drawing();
}