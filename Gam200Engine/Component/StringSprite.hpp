/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringSprite.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 11.04.2019

	Header file for Sprite Prototypes for string graphics
******************************************************************************/
#pragma once

#include <Component/Sprite.hpp>

class Object;

class StringSprite : Sprite
{
public:
	StringSprite(Object* obj) noexcept;
	virtual ~StringSprite() noexcept = default;
	
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Clear() override;
	
private:
	
};
