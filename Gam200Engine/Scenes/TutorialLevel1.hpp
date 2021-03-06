/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TutorialLevel1.hpp
Author
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 03.15.2020


******************************************************************************/
#pragma once

#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>

class Object;
class String;
class Player;

class TutorialLevel1 : public Scene
{
public:
    TutorialLevel1();
    virtual ~TutorialLevel1();

    void Update(float dt) override;

protected:
    void GameRestart() override;
    void Load() override;
    void Unload() override;

    void Collision();
    void InitObject();

private:
    Object* background;
    Object* startPoint{};
    Object* goalPoint{};
};