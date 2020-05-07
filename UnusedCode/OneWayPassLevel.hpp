/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   OneWayPassLevel.hpp
Author
    - Sinil.Kang rtd99062@gmail.com
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 12.10.2019

    Header file for level that string make player move easily
******************************************************************************/
#pragma once
#include <Scenes/Scene.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Component/Physics.hpp>
#include <Object\ObjectManager.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Systems/FileIO.hpp>
#include <Object/Players/Player1.h>
#include <Object/Players/Player2.h>
#include <Sounds/SoundManager.hpp>

// input function
#include <Graphics/GL.hpp>
#include <Systems/Input.hpp>

class Player1;
class Player2;
class Object;
class String;

class OneWayPassLevel : public Scene
{
public:
    OneWayPassLevel();
    virtual ~OneWayPassLevel();

	void Update(float dt) override;

protected:
    void GameRestart() override;
	void Load() override;
	void Unload() override;
	
    void Input();
    void Collision();
    void InitObject();
    void SetPlayersPosition(vector2 playerPos1, vector2 playerPos2);
private:
    Object* background;
    Object* startPoint{};
    Object* goalPoint{};

    Object* first_Objects_1{};
    Object* first_Objects_2{};
    Object* first_Objects_3{};
};