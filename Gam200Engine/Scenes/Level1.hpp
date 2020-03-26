/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Level1.hpp
Author
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 03.25.2020


******************************************************************************/
#pragma once

#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>

class Object;
class String;
class Player;

class Level1 : public Scene
{
public:
    Level1();
    virtual ~Level1();

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

    Player* player1{};
    Player* player2{};

    String* string{};
};