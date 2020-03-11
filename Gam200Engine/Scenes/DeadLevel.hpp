/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: DeadLevel.hpp
Author: dbsqhd106@gmail.com

Creation Date: DEC/11th/2019

    Header file for the test object whether interact work or not
******************************************************************************/

#pragma once
#include <Scenes/Scene.hpp>

class Object;
class String;
class ObstacleObject;

class DeadLevel : public Scene
{
public:
    DeadLevel();
    virtual ~DeadLevel();

    void Update(float dt) override;
    
protected:
    
    void GameRestart() override;
    void Load() override;
    void Unload() override;

    void Input();
    void InitObject();
private:
    Object* background;
    Object* startPoint{};
    Object* goalPoint{};


    Object* player1{};
    Object* player2{};

    ObstacleObject* obj_1;
    ObstacleObject* obj_2;
    ObstacleObject* obj_3;

    String* string{};
};
