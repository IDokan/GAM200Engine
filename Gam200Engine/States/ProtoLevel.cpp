/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ProtoLevel.hpp
Author
        Hyerin Jung
        junghl0621@gmail.com
Creation Date: 11.11.2019

    
******************************************************************************/

#include "ProtoLevel.hpp"
#include <Object\ObjectManager.hpp>
// Include Components
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <Component\Animation.cpp>
#include <Graphics\GL.cpp>
#include <Component\TextComponent.hpp>
#include <Input.hpp>
#include <States\StateManager.hpp>



void ProtoLevel::Load() {
    
    auto objManager = ObjectManager::GetObjectManager();

    background = new Object();
    background->SetObjectName("background");
    background->SetTranslation(vector2{ 0.f });
    background->SetScale(vector2{ 700000 });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 0.f, 0.f });
    background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(1000);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

    /*objectA = new Object();
    objectA->SetObjectName("MouseInput");
    objectA->SetObjectType(Object::ObjectType::MOUSE);
    objectA->SetTranslation(vector2{ 200.f });
    objectA->SetScale(vector2{ 200.f });
    objectA->AddComponent(new Sprite(objectA));
    objectA->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 1.f, 1.f });
    objectA->SetDepth(-0.1f);
    objectA->AddComponent(new Physics(objectA));
    objManager->FindLayer(LayerNames::Stage)->AddObject(objectA);*/

}
void ProtoLevel::Update(float dt) {

    //vector2 objectAPosition = objectA->GetComponentByTemplate<Physics>()->GetPosition();

    
    cameraManager.CameraMove(vector2{ -1.f }, vector2{ -1.f }, 1.1f);
    ObjectManager* objManager = ObjectManager::GetObjectManager();

    is_next = false;
    if (input.IsKeyTriggered(GLFW_KEY_SPACE)) {
        is_next = true;
        //change the level
        LevelChangeTo("testLevel");
    }
}
void ProtoLevel::Unload() {
    ObjectManager* objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::BackGround)->DeleteObject("background");

}

void ProtoLevel::Draw() const noexcept {

    Graphics::GL::begin_drawing();

    for (const auto& element : ObjectManager::GetObjectManager()->GetLayerContainer())
    {
        for (const auto& obj : element->GetObjContainer())
        {
            if (const auto& sprite = obj.get()->GetComponentByTemplate<Sprite>())
            {
                const auto matrix = cameraManager.GetWorldToNDCTransform() * obj.get()->GetTransform().GetModelToWorld();
                sprite->UpdateUniforms(matrix,
                    obj.get()->GetTransform().CalculateWorldDepth());
                Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());
            }
        }
    }
    Graphics::GL::end_drawing();
}
