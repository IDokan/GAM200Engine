/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.hpp
Author
    - Sinil.Kang rtd99062@gmail.com

Creation Date: 12.10.2019

    Header file for level that player learned how to move player
******************************************************************************/
#pragma once
#include <States/State.hpp>

class Object;
class String;


class TutorialLevel : public State
{
public:
    TutorialLevel();
    virtual ~TutorialLevel();

    void Update(float dt) override;

protected:
    void GameRestart() override;
    void Load() override;
    void Unload() override;

    void Input();
    void Collision();
    void InitObject();

private:
    Object* background;
    Object* startPoint{};
    Object* goalPoint{};
    Object* player1{};
    Object* player2{};


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


    Object* moveBox1{};

    Object* lock{};

    String* string{};
};