#pragma once
#include <Component/Component.hpp>
#include<Object/Object.hpp>
#include <Object/Players/Player.h>

class ParticleEmitter;

class TriggerButton : public Component
{
public:
    TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* button1, Object* door_1, Object* door_2, ParticleEmitter* particleEmitter = nullptr);
    TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* door_1, ParticleEmitter* particleEmitter = nullptr);
    ~TriggerButton() = default;
    virtual void Init();
    virtual void Update(float dt);
    virtual void Clear();

    void OpenTwoDoorWithOneButton();
    void OpenOneDoorWithOneButton();
private:
    Object* button;
    Object* button1;
    Object* door_1;
    Object* door_2;
    ParticleEmitter* particleEmitter;
    
    Player* player1;
    Player* player2;
};