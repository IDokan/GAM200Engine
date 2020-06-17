#include "Object/DoorSystem.hpp"
#include "Component/TriggerButton.hpp"
#include <Object/ObjectManager.hpp>
#include <Object/Particles/ParticleEmitter.hpp>
#include <Object/DepthStandard.hpp>

/*OPEN TWO DOOR WITH ONE BUTTON*/
DoorSystem::DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale) : button1(nullptr)
{
    button = new Object();
    button->SetObjectType(Object::ObjectType::BUTTON);
    button->SetTranslation(buttonPos);
    button->SetScale(buttonScale);
    Animation* buttonAnimation = new Animation(button);
    button->AddComponent(buttonAnimation);
    buttonAnimation->SetImage("../assets/textures/pressurePlate.png");
    buttonAnimation->SetNumOfState(2);
    buttonAnimation->SetSpeed(0.f);
    buttonAnimation->SetState(0);
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

    openEmitter = new ParticleEmitter(7.5f, 5.f, 35, [&]()
        {
            Particle::ParticleObject p;
            p.color = Graphics::Color4f(0.65f);
            p.transform.SetScale(vector2{ 10.f });
            float x = ((rand() % 100) / 100.f) - 0.5f;
            float y = ((rand() % 100) / 100.f) - 0.5f;

            p.transform.SetTranslation(FindPositionOfParticle(vector2{ x, y }, openDoor->GetTranslation(), openDoor->GetScale()));

            p.velocity = vector2{ x, y };
            p.life = 5.f;
            return p;
        }
        ,
            [&](Particle::ParticleObject& p, float dt)
        {
            p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * 50.f * dt));
            p.color.alpha -= dt * 0.3f;
        }
        );
    openEmitter->SetParticleImage("../assets/textures/circle.png");
    openEmitter->SetDepth(Depth_Standard::DustVFX);
    openEmitter->SetShouldReviveParticle(false);

    closeEmitter = new ParticleEmitter(7.5f, 5.f, 35, [&]()
        {
            Particle::ParticleObject p;
            p.color = Graphics::Color4f(0.65f);
            p.transform.SetScale(vector2{ 10.f });
            float x = ((rand() % 100) / 100.f) - 0.5f;
            float y = ((rand() % 100) / 100.f) - 0.5f;

            p.transform.SetTranslation(FindPositionOfParticle(vector2{ x, y }, closeDoor->GetTranslation(), closeDoor->GetScale()));

            p.velocity = vector2{ x, y };
            p.life = 5.f;
            return p;
        }
        ,
            [&](Particle::ParticleObject& p, float dt)
        {
            p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * 50.f * dt));
            p.color.alpha -= dt * 0.3f;
        }
        );
    closeEmitter->SetParticleImage("../assets/textures/circle.png");
    closeEmitter->SetDepth(Depth_Standard::DustVFX);
    closeEmitter->SetShouldReviveParticle(true);

    Object::AddComponent(new TriggerButton(this, player1, player2, button, nullptr, openDoor, closeDoor, openEmitter, closeEmitter));
    objManager->FindLayer(LayerNames::Stage)->AddObject(openEmitter);
    objManager->FindLayer(LayerNames::Stage)->AddObject(closeEmitter);
}

// To be improved
DoorSystem::DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale, Object* movingObject)
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
    openDoor->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    openDoor->SetDepth(-1.f);

    closeDoor = new Object();
    closeDoor->SetObjectType(Object::ObjectType::DOOR);
    closeDoor->SetTranslation(closeDoorPos);
    closeDoor->SetScale(closeDoorScale);
    closeDoor->AddComponent(new Sprite(closeDoor));
    closeDoor->AddComponent(new Physics(closeDoor));
    closeDoor->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
    closeDoor->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(closeDoor, Physics::ObjectType::RECTANGLE);
    closeDoor->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rect.png");
    closeDoor->SetDepth(-1.f);

    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(button);
    objManager->FindLayer(LayerNames::Stage)->AddObject(openDoor);
    objManager->FindLayer(LayerNames::Stage)->AddObject(closeDoor);

    Object::AddComponent(new TriggerButton(this, player1, player2, button, nullptr, openDoor, closeDoor, movingObject));
}

/*OPEN TWO DOOR WITH TWO BUTTON NOT A TIMER*/
DoorSystem::DoorSystem(Player* player1, Player* player2, vector2 button_1_Pos, vector2 button_1_Scale, vector2 button_2_Pos, vector2 button_2_Scale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale)
{
    button = new Object();
    button->SetObjectType(Object::ObjectType::BUTTON);
    button->SetTranslation(button_1_Pos);
    button->SetScale(button_1_Scale);
    Animation* buttonAnimation = new Animation(button);
    button->AddComponent(buttonAnimation);
    buttonAnimation->SetImage("../assets/textures/pressurePlate.png");
    buttonAnimation->SetNumOfState(2);
    buttonAnimation->SetSpeed(0.f);
    buttonAnimation->SetState(0);
    button->AddComponent(new Physics(button));
    button->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button, Physics::ObjectType::RECTANGLE);
    button->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button->SetDepth(-1.f);

    button1 = new Object();
    button1->SetObjectType(Object::ObjectType::BUTTON);
    button1->SetTranslation(button_2_Pos);
    button1->SetScale(button_2_Scale);
    Animation* button1Animation = new Animation(button1);
    button1->AddComponent(button1Animation);
    button1Animation->SetImage("../assets/textures/pressurePlate.png");
    button1Animation->SetNumOfState(2);
    button1Animation->SetSpeed(0.f);
    button1Animation->SetState(0);
    button1->AddComponent(new Physics(button1));
    button1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button1, Physics::ObjectType::RECTANGLE);
    button1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button1->SetDepth(-1.f);

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
    objManager->FindLayer(LayerNames::Stage)->AddObject(button1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(openDoor);
    objManager->FindLayer(LayerNames::Stage)->AddObject(closeDoor);

    openEmitter = new ParticleEmitter(7.5f, 5.f, 35, [&]()
        {
            Particle::ParticleObject p;
            p.color = Graphics::Color4f(0.65f);
            p.transform.SetScale(vector2{ 10.f });
            float x = ((rand() % 100) / 100.f) - 0.5f;
            float y = ((rand() % 100) / 100.f) - 0.5f;

            p.transform.SetTranslation(FindPositionOfParticle(vector2{ x, y }, openDoor->GetTranslation(), openDoor->GetScale()));

            p.velocity = vector2{ x, y };
            p.life = 5.f;
            return p;
        }
        ,
            [&](Particle::ParticleObject& p, float dt)
        {
            p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * 50.f * dt));
            p.color.alpha -= dt * 0.3f;
        }
        );
    openEmitter->SetParticleImage("../assets/textures/circle.png");
    openEmitter->SetDepth(Depth_Standard::DustVFX);
    openEmitter->SetShouldReviveParticle(false);

    closeEmitter = new ParticleEmitter(7.5f, 5.f, 35, [&]()
        {
            Particle::ParticleObject p;
            p.color = Graphics::Color4f(0.65f);
            p.transform.SetScale(vector2{ 10.f });
            float x = ((rand() % 100) / 100.f) - 0.5f;
            float y = ((rand() % 100) / 100.f) - 0.5f;

            p.transform.SetTranslation(FindPositionOfParticle(vector2{ x, y }, closeDoor->GetTranslation(), closeDoor->GetScale()));

            p.velocity = vector2{ x, y };
            p.life = 5.f;
            return p;
        }
        ,
            [&](Particle::ParticleObject& p, float dt)
        {
            p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * 50.f * dt));
            p.color.alpha -= dt * 0.3f;
        }
        );
    closeEmitter->SetParticleImage("../assets/textures/circle.png");
    closeEmitter->SetDepth(Depth_Standard::DustVFX);
    closeEmitter->SetShouldReviveParticle(true);

    Object::AddComponent(new TriggerButton(this, player1, player2, button, button1, openDoor, closeDoor, openEmitter, closeEmitter));

    objManager->FindLayer(LayerNames::Stage)->AddObject(openEmitter);
    objManager->FindLayer(LayerNames::Stage)->AddObject(closeEmitter);
}

/*OPEN TWO DOOR WITH TWO TIMER BUTTON*/
DoorSystem::DoorSystem(Player* player1, Player* player2, vector2 button_1_Pos, vector2 button_1_Scale, vector2 button_2_Pos, vector2 button_2_Scale, vector2 openDoorPos, vector2 openDoorScale, vector2 closeDoorPos, vector2 closeDoorScale, bool timerButton)
{
    button = new Object();
    button->SetObjectType(Object::ObjectType::BUTTON);
    button->SetTranslation(button_1_Pos);
    button->SetScale(button_1_Scale);
    Animation* buttonAnimation = new Animation(button);
    button->AddComponent(buttonAnimation);
    buttonAnimation->SetImage("../assets/textures/lever.png");
    buttonAnimation->SetNumOfState(4);
    buttonAnimation->SetSpeed(0.f);
    buttonAnimation->SetState(0);
    button->AddComponent(new Physics(button));
    button->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button, Physics::ObjectType::RECTANGLE);
    button->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button->SetDepth(-1.f);

    button1 = new Object();
    button1->SetObjectType(Object::ObjectType::BUTTON);
    button1->SetTranslation(button_2_Pos);
    button1->SetScale(button_2_Scale);
    Animation* button1Animation = new Animation(button1);
    button1->AddComponent(button1Animation);
    button1Animation->SetImage("../assets/textures/lever.png");
    button1Animation->SetNumOfState(4);
    button1Animation->SetSpeed(0.f);
    button1Animation->SetState(0);
    button1->AddComponent(new Physics(button1));
    button1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(button1, Physics::ObjectType::RECTANGLE);
    button1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
    button1->SetDepth(-1.f);

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
    objManager->FindLayer(LayerNames::Stage)->AddObject(button1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(openDoor);
    objManager->FindLayer(LayerNames::Stage)->AddObject(closeDoor);

    openEmitter = new ParticleEmitter(7.5f, 5.f, 35, [&]()
        {
            Particle::ParticleObject p;
            p.color = Graphics::Color4f(0.65f);
            p.transform.SetScale(vector2{ 10.f });
            float x = ((rand() % 100) / 100.f) - 0.5f;
            float y = ((rand() % 100) / 100.f) - 0.5f;

            p.transform.SetTranslation(FindPositionOfParticle(vector2{ x, y }, openDoor->GetTranslation(), openDoor->GetScale()));

            p.velocity = vector2{ x, y };
            p.life = 5.f;
            return p;
        }
        ,
            [&](Particle::ParticleObject& p, float dt)
        {
            p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * 50.f * dt));
            p.color.alpha -= dt * 0.3f;
        }
        );
    openEmitter->SetParticleImage("../assets/textures/circle.png");
    openEmitter->SetDepth(Depth_Standard::DustVFX);
    openEmitter->SetShouldReviveParticle(false);

    closeEmitter = new ParticleEmitter(7.5f, 5.f, 35, [&]()
        {
            Particle::ParticleObject p;
            p.color = Graphics::Color4f(0.65f);
            p.transform.SetScale(vector2{ 10.f });
            float x = ((rand() % 100) / 100.f) - 0.5f;
            float y = ((rand() % 100) / 100.f) - 0.5f;

            p.transform.SetTranslation(FindPositionOfParticle(vector2{ x, y }, closeDoor->GetTranslation(), closeDoor->GetScale()));

            p.velocity = vector2{ x, y };
            p.life = 5.f;
            return p;
        }
        ,
            [&](Particle::ParticleObject& p, float dt)
        {
            p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * 50.f * dt));
            p.color.alpha -= dt * 0.3f;
        }
        );
    closeEmitter->SetParticleImage("../assets/textures/circle.png");
    closeEmitter->SetDepth(Depth_Standard::DustVFX);
    closeEmitter->SetShouldReviveParticle(true);

    Object::AddComponent(new TriggerButton(this, player1, player2, button, button1, openDoor, closeDoor, timerButton, openEmitter, closeEmitter));
    
    objManager->FindLayer(LayerNames::Stage)->AddObject(openEmitter);
    objManager->FindLayer(LayerNames::Stage)->AddObject(closeEmitter);
}

/*OPEN ONE DOOR WITH ONE BUTTON*/
DoorSystem::DoorSystem(Player* player1, Player* player2, vector2 buttonPos, vector2 buttonScale, vector2 doorPos, vector2 doorScale, bool isOpen)
{
    button = new Object();
    button->SetObjectType(Object::ObjectType::BUTTON);
    button->SetTranslation(buttonPos);
    button->SetScale(buttonScale);
    Animation* buttonAnimation = new Animation(button);
    button->AddComponent(buttonAnimation);
    buttonAnimation->SetImage("../assets/textures/pressurePlate.png");
    buttonAnimation->SetNumOfState(2);
    buttonAnimation->SetSpeed(0.f);
    buttonAnimation->SetState(0);
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
    openDoor->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/BLOCK_W.png");
    openDoor->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(openDoor->GetScale() / 75.f);
    openDoor->SetDepth(-1.f);

    openEmitter = new ParticleEmitter(7.5f, 5.f, 35, [&]()
        {
            Particle::ParticleObject p;
            p.color = Graphics::Color4f(0.65f);
            p.transform.SetScale(vector2{ 10.f });
            float x = ((rand() % 100) / 100.f) - 0.5f;
            float y = ((rand() % 100) / 100.f) - 0.5f;

            p.transform.SetTranslation(FindPositionOfParticle(vector2{ x, y }, openDoor->GetTranslation(), openDoor->GetScale()));

            p.velocity = vector2{ x, y };
            p.life = 5.f;
            return p;
        }
        ,
            [&](Particle::ParticleObject& p, float dt)
        {
            p.transform.SetTranslation(p.transform.GetTranslation() + (p.velocity * 50.f * dt));
            p.color.alpha -= dt * 0.3f;
        }
        );
    openEmitter->SetParticleImage("../assets/textures/circle.png");
    openEmitter->SetDepth(Depth_Standard::DustVFX);
    openEmitter->SetShouldReviveParticle(false);

    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(button);
    objManager->FindLayer(LayerNames::Stage)->AddObject(openDoor);
    objManager->FindLayer(LayerNames::Stage)->AddObject(openEmitter);

    Object::AddComponent(new TriggerButton(this, player1, player2, button, openDoor, openEmitter));
}

void DoorSystem::SetButtonAndDoorColor(Graphics::Color4f button_1_Color, Graphics::Color4f button_2_Color, Graphics::Color4f openDoorColor, Graphics::Color4f closeDoorColor)
{
    button->GetComponentByTemplate<Sprite>()->SetColor(button_1_Color);
    button1->GetComponentByTemplate<Sprite>()->SetColor(button_2_Color);
    openDoor->GetComponentByTemplate<Sprite>()->SetColor(openDoorColor);
    closeDoor->GetComponentByTemplate<Sprite>()->SetColor(closeDoorColor);
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

void DoorSystem::SetButtonAndDoorName(std::string button_1_Name, std::string button_2_Name, std::string openDoorName, std::string closeDoorName)
{
    button->SetObjectName(button_1_Name);
    button1->SetObjectName(button_2_Name);
    openDoor->SetObjectName(openDoorName);
    closeDoor->SetObjectName(closeDoorName);
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
