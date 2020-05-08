#pragma once
#include <Component/Component.hpp>
#include<Object/Object.hpp>
#include <Object/Players/Player.h>

class TriggerButton : public Component
{
public:
    TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* button1, Object* door_1, Object* door_2);
    TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* button1, Object* door_1, Object* door_2, bool isTimerButton);
    TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* button1, Object* door_1, Object* door_2, Object* movingObject);
    TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* door_1);
    ~TriggerButton() = default;
    virtual void Init();
    virtual void Update(float dt);
    virtual void Clear();

    void OpenAndCloseDoorsWithOneButton();
    void OpenOneDoorWithOneButton();
    void OpenAndCloseDoorsWithTwoButton();
    void OpenAndCloseDoorsWithTwoButtonOnTime(float dt);
private:
    Object* movingObject;
    Object* button;
    Object* button1;
    Object* door_1;
    Object* door_2;
    
    Player* player1;
    Player* player2;

    bool isTimerButton;
};