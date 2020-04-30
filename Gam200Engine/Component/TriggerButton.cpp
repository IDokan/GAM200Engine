#include "TriggerButton.hpp"

TriggerButton::TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* button1, Object* door_1, Object* door_2) : Component(obj), player1(player1), player2(player2), button(button), button1(button1), door_1(door_1), door_2(door_2)
{
}

TriggerButton::TriggerButton(Object* obj, Player* player1, Player* player2, Object* button, Object* door_1) : Component(obj), player1(player1), player2(player2), button(button), button1(nullptr), door_1(door_1), door_2(nullptr)
{
}

void TriggerButton::Init()
{
}

void TriggerButton::Update(float dt)
{

    if (door_2 == nullptr)
    {
        OpenOneDoorWithOneButton();
    }
    else if (button1 == nullptr)
    {
        OpenTwoDoorWithOneButton();
    }
    else
    {
        OpenTwoDoorWithTwoButton();
    }
}

void TriggerButton::Clear()
{
}

void TriggerButton::OpenTwoDoorWithOneButton()
{
    if ((player1->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true || player2->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true))
    {
        if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false && player1->GetComponentByTemplate<Physics>()->IsCollideWith(door_2) == false && player2->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false && player2->GetComponentByTemplate<Physics>()->IsCollideWith(door_2) == false)
        {
            Graphics::Color4f color = door_1->GetComponentByTemplate<Sprite>()->GetColor();
            Graphics::Color4f color2 = door_2->GetComponentByTemplate<Sprite>()->GetColor();
            if (button->GetDirtyFlag() == true)
            {

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
                button->SetDirtyFlag(false);
            }
        }
        else
        {
            button->SetDirtyFlag(false);
        }
    }
    else
    {
        button->SetDirtyFlag(true);
    }
}

void TriggerButton::OpenOneDoorWithOneButton()
{
    if ((player1->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true || player2->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true))
    {
        if (player1->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false && player2->GetComponentByTemplate<Physics>()->IsCollideWith(door_1) == false)
        {
            if (button->GetDirtyFlag())
            {
                Graphics::Color4f color = door_1->GetComponentByTemplate<Sprite>()->GetColor();
                if (door_1->GetComponentByTemplate<Physics>()->GetActiveGhostCollision() == true)
                {
                    color.alpha = 1.f;
                    door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
                    door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));
                }
                else
                {
                    color.alpha = 0.2f;
                    door_1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
                    door_1->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(color));
                }
                button->SetDirtyFlag(false);
            }
        }
        else
        {
            button->SetDirtyFlag(false);
        }
    }
    else
    {
        button->SetDirtyFlag(true);
    }
}

void TriggerButton::OpenTwoDoorWithTwoButton()
{
    if ((player1->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true && player2->GetComponentByTemplate<Physics>()->IsCollideWith(button1) == true) ||
        (player1->GetComponentByTemplate<Physics>()->IsCollideWith(button1) == true && player2->GetComponentByTemplate<Physics>()->IsCollideWith(button) == true))
    {
        Graphics::Color4f color = door_1->GetComponentByTemplate<Sprite>()->GetColor();
        Graphics::Color4f color2 = door_2->GetComponentByTemplate<Sprite>()->GetColor();
        if (button->GetDirtyFlag() == true && button1->GetDirtyFlag() == true)
        {
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
            button->SetDirtyFlag(false);
            button1->SetDirtyFlag(false);
        }
    }
    else
    {
        button->SetDirtyFlag(true);
        button1->SetDirtyFlag(true);
    }
}
