#include <Component/TriggerButton.hpp>
#include <Object/Particles/ParticleEmitter.hpp>

TriggerButton::TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* button1, Object* door_1, Object* door_2, ParticleEmitter* openEmitter, ParticleEmitter* closeEmitter) : Component(obj), player1(player1), player2(player2), button(button), button1(button1), door_1(door_1), door_2(door_2), movingObject(nullptr), isTimerButton(false), openEmitter(openEmitter), closeEmitter(closeEmitter)
{
}

TriggerButton::TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* button1, Object* door_1, Object* door_2, bool isTimerButton, ParticleEmitter* openEmitter, ParticleEmitter* closeEmitter) : Component(obj), player1(player1), player2(player2), button(button), button1(button1), door_1(door_1), door_2(door_2), movingObject(nullptr), isTimerButton(isTimerButton), openEmitter(openEmitter), closeEmitter(closeEmitter)
{
}

TriggerButton::TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* button1, Object* door_1, Object* door_2, Object* movingObject) : Component(obj), player1(player1), player2(player2), button(button), button1(button1), door_1(door_1), door_2(door_2), movingObject(movingObject), openEmitter(openEmitter), closeEmitter(closeEmitter)
{
}

TriggerButton::TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* door_1, ParticleEmitter* openEmitter) : Component(obj), player1(player1), player2(player2), button(button), button1(nullptr), door_1(door_1), door_2(nullptr), movingObject(nullptr), isTimerButton(false), openEmitter(openEmitter), closeEmitter(nullptr)
{
}

void TriggerButton::Init()
{
}

void TriggerButton::Update(float dt)
{

    //if (movingObject != nullptr)
    //{
    //    button->SetTranslation(vector2{ movingObject->GetTranslation().x, movingObject->GetTranslation().y -50.f});
    //}

    if (door_2 == nullptr)
    {
        OpenOneDoorWithOneButton();
    }
    else if (button1 == nullptr)
    {
        OpenAndCloseDoorsWithOneButton();
    }
    else if (isTimerButton == true)
    {
        OpenAndCloseDoorsWithTwoButtonOnTime(dt);
    }
    else
    {
        OpenAndCloseDoorsWithTwoButton();
    }
}

void TriggerButton::Clear()
{
}

void TriggerButton::OpenAndCloseDoorsWithOneButton()
{
    if ((player1->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true || player2->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true))
    {
        if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false && player1->GetComponentByTemplate<Physics>()->IsCollideWith(door_2) == false
            && player2->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false && player2->GetComponentByTemplate<Physics>()->IsCollideWith(door_2) == false) // to confirm one of the players are not on the door position if players on the door position, the door will not be opened.
        {
            Graphics::Color4f color = door_1->GetComponentByTemplate<Sprite>()->GetColor();
            Graphics::Color4f color2 = door_2->GetComponentByTemplate<Sprite>()->GetColor();
            if (button->GetDirtyFlag() == true) // only the first time when players collide with button, get in this if statement because without this if statement, doors will keep opening and closing 
            {
                if (door_1->GetComponentByTemplate<Physics>()->GetActiveGhostCollision() == true) // the reason why check the door is ghostCollision or not is that activating ghost collision means that that door is opened. so close the opened door and opend closed door.
                {
                    color.alpha = 1.f;
                    door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                    door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));
                    openEmitter->SetShouldReviveParticle(true);

                    color2.alpha = 0.2f;
                    door_2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                    door_2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color2));
                    closeEmitter->SetShouldReviveParticle(false);
                }
                else
                {

                    color.alpha = 0.2f;
                    door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                    door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));
                    openEmitter->SetShouldReviveParticle(false);

                    color2.alpha = 1.f;
                    door_2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                    door_2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color2));
                    closeEmitter->SetShouldReviveParticle(true);
                }
                button->SetDirtyFlag(false); // set flag as false to prevent the door keeps opening and closing
            }
        }
    }
    else
    {
        button->SetDirtyFlag(true); // set flag as true. this means that players does not trigger the button anymore.
    }

    if (button->GetDirtyFlag())
    {
        button->GetComponentByTemplate<Animation>()->SetState(0);
    }
    else
    {
        button->GetComponentByTemplate<Animation>()->SetState(1);
    }
}

void TriggerButton::OpenOneDoorWithOneButton()
{
    if ((player1->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true || player2->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true))
    {
        if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false && player2->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false) // to confirm one of the players are not on the door position if players on the door position, the door will not be opened.
        {
            if (button->GetDirtyFlag())
            {
                Graphics::Color4f color = door_1->GetComponentByTemplate<Sprite>()->GetColor();
                if (door_1->GetComponentByTemplate<Physics>()->GetActiveGhostCollision() == true) // rest parts are same as OpenAndCloseDoorsWithOneButton() function.
                {
                    color.alpha = 1.f;
                    door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                    door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));
                    openEmitter->SetShouldReviveParticle(true);
                }
                else
                {
                    color.alpha = 0.2f;
                    door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                    door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));
                    openEmitter->SetShouldReviveParticle(false);
                }
                button->SetDirtyFlag(false);
            }
        }
    }
    else
    {
        button->SetDirtyFlag(true);
    }

    if (button->GetDirtyFlag())
    {
        button->GetComponentByTemplate<Animation>()->SetState(0);
    }
    else
    {
        button->GetComponentByTemplate<Animation>()->SetState(1);
    }
}

void TriggerButton::OpenAndCloseDoorsWithTwoButton()
{
    bool isPlayer1OnButton = player1->GetComponentByTemplate<Physics>()->IsCollideWith(button);
    bool isPlayer2OnButton1 = player2->GetComponentByTemplate<Physics>()->IsCollideWith(button1);
    bool isPlayer1OnButton1 = player1->GetComponentByTemplate<Physics>()->IsCollideWith(button1);
    bool isPlayer2OnButton = player2->GetComponentByTemplate<Physics>()->IsCollideWith(button);
    if ((isPlayer1OnButton == true && isPlayer2OnButton1 == true) ||
        (isPlayer1OnButton1 == true && isPlayer2OnButton == true)) // the doors are opened only when players press two button at the same time.
    {
        Graphics::Color4f color = door_1->GetComponentByTemplate<Sprite>()->GetColor();
        Graphics::Color4f color2 = door_2->GetComponentByTemplate<Sprite>()->GetColor();
        if (button->GetDirtyFlag() == true && button1->GetDirtyFlag() == true)
        {
            if (door_1->GetComponentByTemplate<Physics>()->GetActiveGhostCollision() == true)  // rest parts are same as OpenAndCloseDoorsWithOneButton() function.
            {
                color.alpha = 1.f;
                door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));

                color2.alpha = 0.2f;
                door_2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                door_2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color2));
            }
            else
            {
                color.alpha = 0.2f;
                door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));

                color2.alpha = 1.f;
                door_2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                door_2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color2));
            }
            button->SetDirtyFlag(false);
            button1->SetDirtyFlag(false);
        }
    }
    else
    {
        button->SetDirtyFlag(true);
        button1->SetDirtyFlag(true);
    }

    if (isPlayer1OnButton || isPlayer2OnButton)
    {
        button->GetComponentByTemplate<Animation>()->SetState(1);
    }
    else
    {
        button->GetComponentByTemplate<Animation>()->SetState(0);
    }

    if (isPlayer1OnButton1 || isPlayer2OnButton1)
    {
        button1->GetComponentByTemplate<Animation>()->SetState(1);
    }
    else
    {
        button1->GetComponentByTemplate<Animation>()->SetState(0);
    }
}

void TriggerButton::OpenAndCloseDoorsWithTwoButtonOnTime(float dt)
{    if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true) // when player trigger button, timer is started
    {
        if (button->GetDirtyFlag() == true)
        {
            button->SetDirtyFlag(false);
            button->SetIsTimerOn(true);
        }
    }
    
    else if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(button1) == true) // when player trigger button, timer is started
    {
        if (button1->GetDirtyFlag() == true)
        {
            button1->SetDirtyFlag(false);
            button1->SetIsTimerOn(true);
        }
    }

    if (player2->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true) // when player trigger button, timer is started
    {
        if (button->GetDirtyFlag() == true)
        {
            button->SetDirtyFlag(false);
            button->SetIsTimerOn(true);
        }
    }
    else if (player2->GetComponentByTemplate<Physics>()->IsCollideWith(button1) == true) // when player trigger button, timer is started
    {
        if (button1->GetDirtyFlag() == true)
        {
            button1->SetDirtyFlag(false);
            button1->SetIsTimerOn(true);
        }
    }

    if (button->GetIsTImerOn() == true || button->GetDirtyFlag() == false)  // keep timer 
    {
        button->SetTimer(dt);
    }

    if (button1->GetIsTImerOn() == true || button1->GetDirtyFlag() == false)
    {
        button1->SetTimer(dt);
    }

    if (button->GetIsTImerOn() == true)
    {
        button->GetComponentByTemplate<Animation>()->SetState(1);
    }
    else if (button->GetIsTImerOn() == false)
    {
        button->GetComponentByTemplate<Animation>()->SetState(0);
    }

    if (button1->GetIsTImerOn() == true)
    {
        button1->GetComponentByTemplate<Animation>()->SetState(1);
    }
    else if (button1->GetIsTImerOn() == false)
    {
        button1->GetComponentByTemplate<Animation>()->SetState(0);
    }

    if (button->GetIsTImerOn() == true && button1->GetIsTImerOn() == true)
    {
        Graphics::Color4f color = door_1->GetComponentByTemplate<Sprite>()->GetColor();
        Graphics::Color4f color2 = door_2->GetComponentByTemplate<Sprite>()->GetColor();
        if (door_1->GetComponentByTemplate<Physics>()->GetActiveGhostCollision() == true)
        {
            color.alpha = 1.f;
            door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
            door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));

            color2.alpha = 0.2f;
            door_2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
            door_2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color2));
        }
        else
        {
            color.alpha = 0.2f;
            door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
            door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));

            color2.alpha = 1.f;
            door_2->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
            door_2->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color2));
        }
        button->SetIsTimerOn(false);
        button1->SetIsTimerOn(false);

        button->ResetTimer(); // to be determine delete this line or not.
        button1->ResetTimer();  // to be determine delete this line or not.
    }

    if (button->GetTimer() >= 3.f)
    {
        button->SetDirtyFlag(true);
        button->SetIsTimerOn(false);
        button->ResetTimer();
    }
    if (button1->GetTimer() >= 3.f)
    {
        button1->SetDirtyFlag(true);
        button1->SetIsTimerOn(false);
        button1->ResetTimer();
    }
}
