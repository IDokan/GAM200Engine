/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   DoorSystem.hpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 06.05.2020

    Source file for Door Object
******************************************************************************/

#pragma once

#include "Object/Object.hpp"
#include "Object/Players/Player.h"

class ParticleEmitter;

class DoorSystem : public Object
{
public:

    DoorSystem(Player* player1, Player* player2, vector2 button_1_Pos, vector2 button_1_Scale, vector2 button_2_Pos, vector2 button_2_Scale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale);
    DoorSystem(Player* player1, Player* player2, vector2 button_1_Pos, vector2 button_1_Scale, vector2 button_2_Pos, vector2 button_2_Scale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale, bool timerButton);
    DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale);
    DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale, Object* movingObject);
    DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 doorPos, vector2 doorScale, bool isOpen);
    void SetButtonAndDoorColor(Graphics::Color4f button_1_Color, Graphics::Color4f button_2_Color, Graphics::Color4f openDoorColor, Graphics::Color4f closeDoorColor);
    void SetButtonAndDoorColor(Graphics::Color4f buttonColor, Graphics::Color4f openDoorColor, Graphics::Color4f closeDoorColor);
    void SetButtonAndDoorColor(Graphics::Color4f buttonColor, Graphics::Color4f doorColor);
    void SetButtonAndDoorName(std::string button_1_Name, std::string button_2_Name, std::string openDoorName, std::string closeDoorName);
    void SetButtonAndDoorName(std::string buttonName, std::string openDoorName, std::string closeDoorName);
    void SetButtonAndDoorName(std::string buttonName, std::string doorName);


    void ReinitializeDoors();
private:
    vector2 FindPositionOfParticle(vector2 velocity, vector2 doorPosition, vector2 doorScale);
private:

    Object* button = nullptr;
    Object* button1 = nullptr;
    Object* openDoor = nullptr;
    Object* closeDoor = nullptr;
    ParticleEmitter* openEmitter = nullptr;
    ParticleEmitter* closeEmitter = nullptr;
};