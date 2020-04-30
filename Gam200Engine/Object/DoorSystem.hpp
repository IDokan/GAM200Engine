#pragma once

#include "Object/Object.hpp"
#include "Object/Players/Player.h"

class ParticleEmitter;

class DoorSystem : public Object
{
public:

    DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale);
    DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 doorPos, vector2 doorScale, bool isOpen);
    void SetButtonAndDoorColor(Graphics::Color4f buttonColor, Graphics::Color4f openDoorColor, Graphics::Color4f closeDoorColor);
    void SetButtonAndDoorColor(Graphics::Color4f buttonColor, Graphics::Color4f doorColor);
    void SetButtonAndDoorName(std::string buttonName, std::string openDoorName, std::string closeDoorName);
    void SetButtonAndDoorName(std::string buttonName, std::string doorName);

private:
    vector2 FindPositionOfParticle(vector2 velocity, vector2 doorPosition, vector2 doorScale);
private:

    Object* button;
    Object* button1;
    Object* openDoor;
    Object* closeDoor;
    ParticleEmitter* particleEmitter;
};