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
#include <Object/DoorSystem.hpp>
#include <Object/DepthStandard.hpp>

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


    Object* movingObject_1;
    Object* movingObject_2;



    Object* cheese;
    CrushableObject* jail;
    DoorSystem* button1;
    DoorSystem* button2;
    DoorSystem* button3;
    DoorSystem* button4;
    DoorSystem* button5;
    DoorSystem* button6;
};