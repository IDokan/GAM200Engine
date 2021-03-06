/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Player.hpp
Author
        dbsqhd106@gmail.com
Creation Date: 23th/Jan/2020

    Header file for the Player.cpp
******************************************************************************/

#pragma once
#include  <Object/Object.hpp>
#include <Component/Sprite/Animation.hpp>
#include <Component/Physics.hpp>

class Player : public Object
{
public:
	enum class Identifier
	{
		Player1,
		Player2,
		UNDEFINED,
	};
public:
	explicit Player(Identifier player, const Transform& playerTransformData = Transform());
    Player(std::string _playerName, const vector2 playerPos, vector2 playerScale
        , Physics::ObjectType _objectType, float _depth = -50.f, Graphics::Color4f _color = { 1.f },
        vector2 positionAdj = { 0.f, 0.f }, vector2 scaleAdj = { 0.f, 0.f });

	[[nodiscard]] Identifier GetID() const noexcept;
    void SetIsBlock(bool flag);
    bool GetIsBlock();

    void SetCurrentAnimationState(int state);
    int GetLastAnimationState();

private:
	void LoadPlayer1Layout();
	void LoadPlayer2Layout();
	
private:
	Identifier id;
    bool isBlock;
    int lastAnimationState;
};