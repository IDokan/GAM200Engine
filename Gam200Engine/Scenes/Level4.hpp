/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  Level4.hpp
Author
    - Jiwon.Jung       jjwon6218@gmail.com
    - Jaemin Woo    wjm9932@gmail.com

Creation Date: 06.30.2020

    Header file for 4th level
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>
#include <Object/DepthStandard.hpp>
#include <Object/DoorSystem.hpp>

class Object;
class String;
class Player;

class Level4 : public Scene
{
public:
    Level4();
    virtual ~Level4();

    void Update(float dt) override;

protected:
    void GameRestart() override;
    void Load() override;
    void Unload() override;

    void Collision();
    void InitObject();

private:
    DoorSystem* button1;
    DoorSystem* button2;
    DoorSystem* button3;
    DoorSystem* button4;
    Object* cheese;
    Object* jail1;
    Object* jail2;
    Object* jail3;
    Object* jail4;
    Object* background;
};
