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


    Object* block1{};
    Object* block2{};
    Object* block3{};
    Object* block4{};
    Object* block5{};
    Object* block6{};
    Object* block7{};
    Object* block8{};
    Object* block9{};
    Object* block10{};
    Object* block11{};
    Object* block12{};
    Object* block13{};
    Object* block14{};
    Object* block15{};
    Object* block16{};
    Object* block17{};
    Object* block18{};
    Object* block19{};
    Object* block20{};
    Object* block21{};
    Object* block22{};
    Object* block23{};
    Object* block24{};
    Object* block25{};
    Object* block26{};

    Object* moveBox1{};

    Object* lock1{};
    Object* lock2{};
    Object* key1{};
    Object* key2{};

    String* string{};
};