/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Level2.hpp
Author
    - Jiwon Jung jjwon6218@gmail.com

Creation Date: 07.11.2020
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>
#include <Object/DepthStandard.hpp>

class Object;
class String;
class Player;

class Level2 : public Scene
{
public:
    Level2();
    virtual ~Level2();

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
