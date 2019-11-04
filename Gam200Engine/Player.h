/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
        dbsqhd106@gmail.com
Creation Date: 

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
    Player(std::string _playerName, vector2 playerPos, vector2 playerScale
    , float _depth)
    :playerName(_playerName),pos_x(playerPos.x),pos_y(playerPos.y),scale_x(playerScale.x),scale_y(playerScale.y)
    ,depth(_depth)
    {
        Object::SetObjectName(std::move(_playerName));
        Object::SetTranslation(playerPos);
                SetScale(playerScale);
                SetDepth(_depth);
                Object::AddComponent(new Sprite(this));
                Object::AddComponent(new Physics(this));
              //  AddComponent(new Sprite(this));
     //   Object::SetObjectName(_playerName);
        //SetObjectName(_playerName);
       // this->AddComponent(new Sprite())
    };
private:
    std::string playerName;
    float pos_x;
    float pos_y;
    float scale_x;
    float scale_y;
    float depth;
  //  void AddComponent(Component* comp) override;
    
    /*

    
    
    void AddComponent(Component* comp) override;

    void SetDepth(float depth) override;
    void SetTranslation(vector2 pos) override;
    void SetRotation(float angle) override;
    void SetScale(vector2 scale) override;
    void SetScale(float scale) override;
    void SetObjectName(std::string name) override;*/
    
//private:
//    Object* newPlayer;
//    std::string playerName;
//    
};