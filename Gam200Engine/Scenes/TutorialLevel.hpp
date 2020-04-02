/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.hpp
Author
    - Hyerin.Jung       junghl0621@gmail.com

Creation Date: 02.11.2020

    Header file for level that player learned how to move player
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Players/Player.h>
#include <Object/Strings/String.hpp>
#include <Object/InteractiveObject/CrushableObject.hpp>

class Object;
class String;
class Player;

class TutorialLevel : public Scene
{
public:
    TutorialLevel();
    virtual ~TutorialLevel();

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

    Object* key1{};
    Object* key2{};

    Object* lock1{};
    Object* lock2{};



    Object* button2;
    Object* wall5;
    Object* wall6;

    Object* wall7;
    Object* wall8;
    Object* wall9;

    Object* button3;
    Object* button4;

    Object* cheese;

    CrushableObject* jail;

    bool canGoNextLevel;

    Graphics::Color4f color;
    String* string{};
};