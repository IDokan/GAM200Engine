/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MainMenu.hpp
Author
    -Hyerin Jung (junghl0621@gmail.com)

Creation Date: 12.02.2019

    Source file for Mainmenu State Component
******************************************************************************/

#pragma once
#include<States/State.hpp>
#include<Graphics/CameraManager.hpp>
#include<Object/ObjectManager.hpp>

class MainMenu final :public State
{
public:
    MainMenu() = default;
    virtual ~MainMenu() {};

    virtual void Load() override;
    virtual void Update(float dt) override;
    virtual void Unload() override;

    void Draw() const noexcept override;

private:
    Graphics::CameraManager cameraManager;
    Object* background;
    Object* select_menu;
    Object* exit;
};