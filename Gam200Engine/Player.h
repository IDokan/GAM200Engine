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

class Player : public Object
{

public:
    Player(std::string _playerName, const vector2 playerPos, vector2 playerScale
        , ObjectType _objectType, Graphics::Color4f _color = { 0.f,0.f,0.f,0.f },
        vector2 positionAdj = { 0.f, 0.f }, vector2 scaleAdj = { 0.f, 0.f }, float _depth = 0);

private:
    std::string playerName;
    float pos_x;
    float pos_y;
    float scale_x;
    float scale_y;
    float depth;
    
};