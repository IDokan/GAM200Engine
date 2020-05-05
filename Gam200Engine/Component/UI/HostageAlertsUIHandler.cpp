/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   HostageAlertsUIHandler.cpp
Author
		sinil.gang -rtd99062@gmail.com
Creation Date: 05.05.2020

	Header file for a component that manage HostageAlerts UI
******************************************************************************/
#include <Component/UI/HostageAlertsUIHandler.hpp>

#include <Object/HUD/HostageAlertsUI.hpp>

#include <Component/MessageCapable.hpp>
#include <Systems/MessageSystem/Message.hpp>


#include <Angle.hpp>

HostageAlertsUIHandler::HostageAlertsUIHandler(HostageAlertsUI* owner)
	: Component(owner), ui(owner), shouldShowing(false), timer(0.f)
{


    ui->AddComponent(new MessageCapable(ui, MessageObjects::HostageAlertsUI,
        [&](const Message& msg)
        {
            switch (msg.Msg)
            {
            case MessageTypes::HostageNotRescuedYet:
                shouldShowing = true;
                return true;
                break;
            default:
                return false;
                break;
            }
        }
    ));
}

HostageAlertsUIHandler::~HostageAlertsUIHandler()
{
}

void HostageAlertsUIHandler::Init()
{
}

void HostageAlertsUIHandler::Update(float dt)
{
    if (shouldShowing)
    {
        // toggle shouldShowing
        shouldShowing = false;

        // Update timer with dt
        UpdateTimer(dt);
        // Lerp here and SetTranslation
        ui->SetTranslation(EaseOutElastic(timer));
    }
    else
    {
        // Update timer with dt
        UpdateTimer(-dt);
        // Lerp here and SetTranslation
        ui->SetTranslation(EaseInQuad(timer));
    }
}

void HostageAlertsUIHandler::Clear()
{
}

vector2 HostageAlertsUIHandler::EaseOutElastic(float t)
{
    if (t > 1.f)
    {
        t = t - static_cast<int>(t);
    }

    float t2 = (t - 1.f) * (t - 1.f);
    float result = 1.f - t2 * t2 * cos(t * MATH::PI * 4.5f);

    return (1.f - result) * hidePosition + result * showPosition;
}

vector2 HostageAlertsUIHandler::EaseInQuad(float t)
{
    if (t > 1.f)
    {
        t = t - static_cast<int>(t);
    }
    float result = t * t;
    return (1.f - result) * hidePosition + result * showPosition;
}

void HostageAlertsUIHandler::UpdateTimer(float dt)
{
    timer += dt;

    if (timer > 1.f)
    {
        timer = 1.f;
    }
    else if(timer < 0.f)
    {
        timer = 0.f;
    }
}
