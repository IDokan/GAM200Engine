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

class Player : public Object
{
    Player(std::string _playerName, vector2 playerPos, vector2 playerScale
        )
    {
     //   Object::SetObjectName(_playerName);
        //SetObjectName(_playerName);
       // this->AddComponent(new Sprite())
    };/*

    
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