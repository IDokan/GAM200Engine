#include "Object/DoorSystem.hpp"
#include "Component/TriggerButton.hpp"
#include <Object/ObjectManager.hpp>

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
    
    Object::AddComponent(new TriggerButton(this, player1, player2, button, nullptr,openDoor, closeDoor));
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
}

void DoorSystem::SetButtonAndDoorName(std::string buttonName, std::string doorName)
{
    button->SetObjectName(buttonName);
    openDoor->SetObjectName(doorName);
}