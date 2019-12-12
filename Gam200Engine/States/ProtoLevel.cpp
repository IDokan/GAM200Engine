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
#include <Object/ObjectManager.hpp>
// Include Components
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <Graphics/GL.hpp>
#include <Systems/Input.hpp>
#include <States\StateManager.hpp>


void ProtoLevel::GameRestart()
{
}

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

    //make the start point. and the players have to displayed near that point.
    startPoint = new Object();
    startPoint->SetObjectName("startPoint");
    startPoint->SetTranslation(vector2{ -1000.f });
    startPoint->SetScale(vector2{ 300 });
    startPoint->AddComponent(new Sprite(startPoint));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("asset/texture/Circle.png");
    startPoint->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f });
    objManager->FindLayer(LayerNames::BackGround)->AddObject(startPoint);

    goalPoint = new Object();
    goalPoint->SetObjectName("goalPoint");
    goalPoint->SetTranslation(vector2{ 1000.f });
    goalPoint->SetScale(vector2{ 300 });
    goalPoint->AddComponent(new Sprite(goalPoint));
    goalPoint->AddComponent(new Physics(goalPoint));
    goalPoint->GetComponentByTemplate<Sprite>()->SetImage("asset/texture/Circle.png");
    goalPoint->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{0.f, 1.f, 1.f });
    objManager->FindLayer(LayerNames::BackGround)->AddObject(goalPoint);


}
void ProtoLevel::Update(float /*dt*/)
{
    cameraManager.CameraMove(vector2{ -1.f }, vector2{ -1.f }, 1.1f);
}
void ProtoLevel::Unload() 
{

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
