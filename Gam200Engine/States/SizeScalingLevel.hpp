/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SizeScalingLevel.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 12.10.2019

	Header file for level that teach size scaling
******************************************************************************/
#pragma once
#include <States/State.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Component/Physics.hpp>
#include <Object\ObjectManager.hpp>
#include <Component/Sprite.hpp>
#include <Systems/FileIO.hpp>
#include <Object/Player1.h>
#include <Object/Player2.h>

// input function
#include <Graphics/GL.hpp>
#include <Systems/Input.hpp>


class SizeScalingLevel : public State
{
public:
	SizeScalingLevel();
	virtual ~SizeScalingLevel();

	void Update(float dt) override;
protected:
	void Load() override;
	void Unload() override;

    void Input();
    void Collision();
    void InitObject();

private:
    Object* background;
    Object* startPoint{};
    Object* goalPoint{};

    Object* scaleObject1;
    Object* scaleObject2;

    Player1* player1{};
    Player2* player2{};
    String* string{};

};