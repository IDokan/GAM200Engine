/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:  AlphaTutorialLevel1.hpp
Author
    - Jiwon.Jung       jjwon6218@gmail.com
    - Doyoung Lee

Creation Date: 05.10.2020

    Header file for level that player learned how to move player
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>
#include <Object/DepthStandard.hpp>

class Object;
class String;
class Player;

class AlphaTutorialLevel1 : public Scene
{
public:
    AlphaTutorialLevel1();
    virtual ~AlphaTutorialLevel1();

    void Update(float dt) override;

protected:
    void GameRestart() override;
    void Load() override;
    void Unload() override;

    void Collision();
    void InitObject();

private:
    Object* background;

    Object* movingObject;
    Object* movingObject1;
    Object* movingObject2;

    Object* cheese;
};