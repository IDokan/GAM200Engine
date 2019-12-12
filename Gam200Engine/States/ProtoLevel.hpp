/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ProtoLevel.cpp
Author
        Hyerin Jung
        junghl0621@gmail.com
Creation Date: 11.11.2019

    Header file for the ProtoLevel.cpp
******************************************************************************/
#pragma once
#include<States/State.hpp>
#include<Graphics/CameraManager.hpp>

class Object;

class ProtoLevel final :public State
{
public:
    ProtoLevel() = default;
    virtual ~ProtoLevel(){};

    virtual void GameRestart() override;
    virtual void Load() override;
    virtual void Update(float dt) override;
    virtual void Unload() override;

    void Draw() const noexcept override;

private:
    Graphics::CameraManager cameraManager;
    Object* background;
    Object* startPoint;
    Object* goalPoint;
};