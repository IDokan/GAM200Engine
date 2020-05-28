/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Level3.hpp
Author
    -  jaemin.woo wjm9932@gmail.com
Creation Date: 03.13.2020

    Header file for scene which works as Level3
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>
#include <Object/DoorSystem.hpp>

class Object;
class Player;
class String;

class Level3 : public Scene
{
public:


    Level3();
    virtual ~Level3();

    void Update(float dt) override;

protected:
    void GameRestart() override;
    void Load() override;
    void Unload() override;

    void Collision();
    void InitObject();

private:
    Object* background;
    Object* movingObject1;
    Object* jail;
    Object* cheese;
    DoorSystem* button1;
    DoorSystem* button2;
    DoorSystem* button3;
    DoorSystem* button4;
};
