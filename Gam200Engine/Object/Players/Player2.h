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

#pragma once
#include <Component/Sprite.hpp>
#include  <Object/Object.hpp>
#include <Component/Physics.hpp>
#include <utility>

class Player2 : public Object
{

public:
    Player2(std::string _playerName, const vector2 playerPos, vector2 playerScale
        , Physics::ObjectType _objectType, float _depth = 0, Graphics::Color4f _color = { 0.f,0.f,0.f,0.f },
        vector2 positionAdj = { 0.f, 0.f }, vector2 scaleAdj = { 0.f, 0.f });

    void Move() noexcept;

private:
    std::string playerName;
    float pos_x;
    float pos_y;
    float scale_x;
    float scale_y;
    float depth;
    
};