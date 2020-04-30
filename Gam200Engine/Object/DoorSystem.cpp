#include "Object/DoorSystem.hpp"
#include "Component/TriggerButton.hpp"
#include <Object/ObjectManager.hpp>
#include <Object/Particles/ParticleEmitter.hpp>
#include <Object/DepthStandard.hpp>

DoorSystem::DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale)
{
    button = new Object();
    button->SetObjectType(Object::ObjectType::BUTTON);
    button->SetTranslation(buttonPos);
    button->SetScale(buttonScale);
    button->AddComponent(new Sprite(button));
    button->AddComponent(new Physics(button));
    button->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button, Physics::ObjectType::RECTANGLE);
    button->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button->SetDepth(-1.f);

    openDoor = new Object();
    openDoor->SetObjectType(Object::ObjectType::DOOR);
    openDoor->SetTranslation(openDoorPos);
    openDoor->SetScale(openDoorScale);
    openDoor->AddComponent(new Sprite(openDoor));
    openDoor->AddComponent(new Physics(openDoor));
    openDoor->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    openDoor->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(openDoor, Physics::ObjectType::RECTANGLE);
    openDoor->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/BLOCK_W.png");
    openDoor->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(openDoor->GetScale() / 75.f);
    openDoor->SetDepth(-1.f);

    closeDoor = new Object();
    closeDoor->SetObjectType(Object::ObjectType::DOOR);
    closeDoor->SetTranslation(closeDoorPos);
    closeDoor->SetScale(closeDoorScale);
    closeDoor->AddComponent(new Sprite(closeDoor));
    closeDoor->AddComponent(new Physics(closeDoor));
    closeDoor->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
    closeDoor->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(closeDoor, Physics::ObjectType::RECTANGLE);
    closeDoor->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/BLOCK_W.png");
    closeDoor->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(closeDoor->GetScale() / 75.f);
    closeDoor->SetDepth(-1.f);
    
    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(button);
    objManager->FindLayer(LayerNames::Stage)->AddObject(openDoor);
    objManager->FindLayer(LayerNames::Stage)->AddObject(closeDoor);

    particleEmitter = new ParticleEmitter(10.f, 5.f, 500, [&]()
        {
            Particle::ParticleObject p;
            p.color = Graphics::Color4f(1.f);
            p.transform.SetScale(vector2{ 10.f });
            float x = ((rand() % 100) / 100.f) - 0.5f;
            float y = ((rand() % 100) / 100.f) - 0.5f;

            p.transform.SetTranslation(FindPositionOfParticle(vector2{x, y }, button->GetTranslation(), button->GetScale()));

            p.velocity = vector2{x, y};
            p.life = 5.f;
            return p;
        }
        ,
            [&](Particle::ParticleObject& p, float dt) 
        {
            p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * 50.f * dt));
        }
        );
    particleEmitter->SetParticleImage("../assets/textures/circle.png");
    particleEmitter->SetDepth(Depth_Standard::HUDFrontVFX);
    particleEmitter->SetShouldReviveLikeTrigger(true);

    Object::AddComponent(new TriggerButton(this, player1, player2, button, nullptr, openDoor, closeDoor, particleEmitter));
    objManager->FindLayer(LayerNames::Stage)->AddObject(particleEmitter);
}

DoorSystem::DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 doorPos, vector2 doorScale, bool isOpen)
{
    button = new Object();
    button->SetObjectType(Object::ObjectType::BUTTON);
    button->SetTranslation(buttonPos);
    button->SetScale(buttonScale);
    button->AddComponent(new Sprite(button));
    button->AddComponent(new Physics(button));
    button->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button, Physics::ObjectType::RECTANGLE);
    button->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button->SetDepth(-1.f);

    openDoor = new Object();
    openDoor->SetObjectType(Object::ObjectType::DOOR);
    openDoor->SetTranslation(doorPos);
    openDoor->SetScale(doorScale);
    openDoor->AddComponent(new Sprite(openDoor));
    openDoor->AddComponent(new Physics(openDoor));
    openDoor->GetComponentByTemplate<Physics>()->ActiveGhostCollision(isOpen);
    openDoor->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(openDoor, Physics::ObjectType::RECTANGLE);
    openDoor->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    openDoor->SetDepth(-1.f);

    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(button);
    objManager->FindLayer(LayerNames::Stage)->AddObject(openDoor);

    Object::AddComponent(new TriggerButton(this, player1, player2, button, openDoor));
}

void DoorSystem::SetButtonAndDoorColor(Graphics::Color4f buttonColor, Graphics::Color4f openDoorColor, Graphics::Color4f closeDoorColor)
{
    button->GetComponentByTemplate<Sprite>()->SetColor(buttonColor);
    openDoor->GetComponentByTemplate<Sprite>()->SetColor(openDoorColor);
    closeDoor->GetComponentByTemplate<Sprite>()->SetColor(closeDoorColor);
}

void DoorSystem::SetButtonAndDoorColor(Graphics::Color4f buttonColor, Graphics::Color4f doorColor)
{
    button->GetComponentByTemplate<Sprite>()->SetColor(buttonColor);
    openDoor->GetComponentByTemplate<Sprite>()->SetColor(doorColor);
}

void DoorSystem::SetButtonAndDoorName(std::string buttonName, std::string openDoorName, std::string closeDoorName)
{
    button->SetObjectName(buttonName);
    openDoor->SetObjectName(openDoorName);
    closeDoor->SetObjectName(closeDoorName);
    //particleEmitter->SetObjectName("ParticleEmitter");
}

void DoorSystem::SetButtonAndDoorName(std::string buttonName, std::string doorName)
{
    button->SetObjectName(buttonName);
    openDoor->SetObjectName(doorName);
    //particleEmitter->SetObjectName(std::string("ParticleEmitter"));
}

vector2 DoorSystem::FindPositionOfParticle(vector2 velocity, vector2 doorPosition, vector2 doorScale)
{
    vector2 velocityIn1stSquare{ abs(velocity.x), abs(velocity.y) };

    // Calculate offset under assume velocity vector is on 1st square
    vector2 resultOffset{ -1.f };
    vector2 compareVector{ doorScale / 2.f };

    float compareAngle = angle_between(compareVector, vector2{ 1.f, 0.f });
    float angleBetweenX = angle_between(velocityIn1stSquare, vector2{ 1.f, 0.f });
    if (angleBetweenX < compareAngle)
    {
        resultOffset.y = atan(angleBetweenX) * doorScale.x;
    }
    else
    {
        resultOffset.x = atan(angle_between(velocityIn1stSquare, vector2{ 0.f, 1.f })) * doorScale.y;
    }

    // Init result vector
    // Initial value of resultOffset is -1, 
    // it means if the value which less than 0 does not have valid value
    // Thus, initialize it into half of scale value.
    if (resultOffset.x < 0.f)
    {
        resultOffset.x = doorScale.x / 2.f;
    }
    else
    {
        resultOffset.y = doorScale.y / 2.f;
    }

    // now, resultOffset should have valid x, y values.
    vector2 resultPosition = doorPosition;
    resultPosition.x += (velocity.x >= 0.f) ? resultOffset.x : -resultOffset.x;
    resultPosition.y += (velocity.y >= 0.f) ? resultOffset.y : -resultOffset.y;

    return resultPosition;
}
