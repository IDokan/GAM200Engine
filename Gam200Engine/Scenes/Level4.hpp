/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  Level4.hpp
Author
    - Jiwon.Jung       jjwon6218@gmail.com
    - Jaemin Woo

Creation Date: 06.30.2020

    Header file for 4th level
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>
#include <Object/DepthStandard.hpp>

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
    Object* background;
};
