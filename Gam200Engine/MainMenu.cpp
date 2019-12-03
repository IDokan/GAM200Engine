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

#include "MainMenu.hpp"
#include <Object\ObjectManager.hpp>
// Include Components
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>
#include <Component\Animation.cpp>
#include <Graphics\GL.cpp>
#include <Component\TextComponent.hpp>
#include <Input.hpp>
#include <States\StateManager.hpp>



void MainMenu::Load() {

    auto objManager = ObjectManager::GetObjectManager();

    background = new Object();
    background->SetObjectName("background");
    background->SetTranslation(vector2{ 0.f });
    background->SetScale(vector2{ 700000 });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f, 0.2f, 0.2f });
    background->GetComponentByTemplate<Sprite>()->ExpandTextureCoordinate(1000);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    
    select_menu = new Object();
    select_menu->SetObjectName("select_menu");
    select_menu->SetObjectType(Object::ObjectType::OBSTACLE);
    select_menu->SetTranslation(vector2{ cameraManager.GetPosition().x,cameraManager.GetPosition().y+100.f });
    select_menu->SetScale(vector2{ 500.f,100.f });
    select_menu->AddComponent(new Sprite(select_menu));
    select_menu->AddComponent(new Physics(select_menu));
    select_menu->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/select_menu.png");
    select_menu->SetDepth(-2.f);
    objManager->FindLayer(LayerNames::HUD)->AddObject(select_menu);

    exit = new Object();
    exit->SetObjectName("exit");
    exit->SetObjectType(Object::ObjectType::OBSTACLE);
    exit->SetTranslation(vector2{ cameraManager.GetPosition().x,cameraManager.GetPosition().y-100.f });
    exit->SetScale(vector2{ 500.f,100.f });
    exit->AddComponent(new Sprite(exit));
    exit->AddComponent(new Physics(exit));
    exit->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/exit.png");
    exit->SetDepth(-2.f);
    objManager->FindLayer(LayerNames::HUD)->AddObject(exit);


}
void MainMenu::Update(float dt) {


    cameraManager.CameraMove(vector2{ -1.f }, vector2{ -1.f }, 1.1f);
    ObjectManager* objManager = ObjectManager::GetObjectManager();

    is_next = false;
    if (input.IsKeyPressed(GLFW_KEY_SPACE))
    {
        is_next = true;
        //change the level 
        LevelChangeTo("protoLevel");
    }

}
void MainMenu::Unload() {
    ObjectManager* objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::BackGround)->DeleteObject("background");

}

void MainMenu::Draw() const noexcept {

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
