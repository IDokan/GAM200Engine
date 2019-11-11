/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
        dbsqhd106@gmail.com
Creation Date: 11th/Nov/2019

    Header file for the Application.cpp
******************************************************************************/
#include  "Player.h"

Player::Player(std::string _playerName, const vector2 playerPos, const vector2 playerScale, ObjectType _objectType,
    Graphics::Color4f _color, vector2 positionAdj, vector2 scaleAdj, float _depth)
    :Object(), playerName(_playerName), pos_x(playerPos.x), pos_y(playerPos.y), scale_x(playerScale.x), scale_y(playerScale.y), depth(_depth)
{
        Object::SetObjectName(std::move(_playerName));

        Object::SetTranslation(playerPos);

        SetScale(playerScale);

        SetDepth(_depth);

        Object::AddComponent(new Sprite(this));

        Object::AddComponent(new Physics(this));

        GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, _objectType, positionAdj, scaleAdj);

        GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ _color });
};

