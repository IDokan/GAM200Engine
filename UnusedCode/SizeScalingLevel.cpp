/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SizeScalingLevel.cpp
Author
	- Sinil.Kang rtd99062@gmail.com
    - Hyerin Jung junghl0621@gmail.com

Creation Date: 12.10.2019

	Source file for level that teach size scaling
******************************************************************************/
#include <Scenes/SizeScalingLevel.hpp>
#include <Component/Scripts/GoalComponent.hpp>

SizeScalingLevel::SizeScalingLevel(): background(nullptr), scaleObject1(nullptr), scaleObject2(nullptr)
{
}

SizeScalingLevel::~SizeScalingLevel()
{
}

void SizeScalingLevel::Load()
{
    SizeScalingLevel::InitObject();

    cameraManager.Init();
}

void SizeScalingLevel::Update(float /*dt*/)
{
    SizeScalingLevel::Input();
    SizeScalingLevel::Collision();
	PlayerScaling();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

	cameraManager.CameraMove(player1, player2, 1.1f);
}

void SizeScalingLevel::GameRestart()
{
}

void SizeScalingLevel::Unload()
{
}
void SizeScalingLevel::Input()
{
    /**********************Moving Object 1*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_W))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_D))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_A))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_A))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_S))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_A))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_D))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_D))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_W))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_S))
        {
            player1->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_W) && input.IsKeyReleased(GLFW_KEY_A) && input.IsKeyReleased(GLFW_KEY_S) && input.IsKeyReleased(GLFW_KEY_D))
    {
        player1->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }




    /**********************Moving Object 2*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_UP))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_LEFT))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_DOWN))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_RIGHT))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            player2->GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_UP) && input.IsKeyReleased(GLFW_KEY_LEFT) && input.IsKeyReleased(GLFW_KEY_DOWN) && input.IsKeyReleased(GLFW_KEY_RIGHT))
    {
        player2->GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }
    if (input.IsKeyTriggered(GLFW_KEY_G))
    {
        if (player1->GetComponentByTemplate<Physics>()->GetIsGhost() == true)
        {
            player1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
        }
        else
        {
            player1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
        }
    }

}

void SizeScalingLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void SizeScalingLevel::InitObject() {

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 0.f });
    background->SetScale(vector2{ 2000.f,2000.f });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

    player1 = new Object();
    player1->SetObjectType(Object::ObjectType::PLAYER_1);
    player1->SetObjectName("player1");
    player1->SetTranslation(vector2{ -200.f, -800.f });
    player1->SetScale(vector2{ 150.f });
    player1->AddComponent(new Sprite(player1));
    player1->AddComponent(new Physics(player1));
    player1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p1.png");
    player1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player1, Physics::ObjectType::RECTANGLE);
    player1->SetDepth(-1.f);

    player2 = new Object();
    player2->SetObjectName("player2");
    player2->SetObjectType(Object::ObjectType::PLAYER_2);
    player2->SetTranslation(vector2{ 200.f, -800.f });
    player2->SetScale(vector2{ 150.f });
    player2->AddComponent(new Sprite(player2));
    player2->AddComponent(new Physics(player2));
    player2->SetDepth(-1.f);
    player2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player2, Physics::ObjectType::RECTANGLE);
    player2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");

    string = new String(player1, player2);

    startPoint = new Object();
    startPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    startPoint->SetObjectName("startPoint");
    startPoint->SetTranslation(vector2{ 0.f, -1000.f });
    startPoint->SetScale(vector2{ 150.f });
    startPoint->AddComponent(new Sprite(startPoint));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
    startPoint->SetDepth(-1.f);

    scaleObject1 = new Object();
    scaleObject1->SetObjectType(Object::ObjectType::OBSTACLE);
    scaleObject1->SetObjectName("scaleObj1");
    scaleObject1->SetTranslation(vector2{ -600.f, -300.f });
    scaleObject1->SetScale(vector2{ 1000.f, 150.f });
    scaleObject1->SetRotation(97.7f);
    scaleObject1->AddComponent(new Sprite(scaleObject1));
    scaleObject1->AddComponent(new Physics(scaleObject1));
    scaleObject1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(scaleObject1, Physics::ObjectType::RECTANGLE);
    scaleObject1->SetDepth(-1.f);

    scaleObject2 = new Object();
    scaleObject2->SetObjectType(Object::ObjectType::OBSTACLE);
    scaleObject2->SetObjectName("scaleObj2");
    scaleObject2->SetTranslation(vector2{ -600.f, 300.f });
    scaleObject2->SetScale(vector2{ 1000.f,150.f });
    scaleObject2->SetRotation(150.4f);
    scaleObject2->AddComponent(new Sprite(scaleObject2));
    scaleObject2->AddComponent(new Physics(scaleObject2));
    scaleObject2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(scaleObject2, Physics::ObjectType::RECTANGLE);
    scaleObject2->SetDepth(-1.f);


    auto objManager = ObjectManager::GetObjectManager();
    objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
    objManager->FindLayer(Stage)->AddObject(string);
    objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
    objManager->FindLayer(LayerNames::Stage)->AddObject(scaleObject1);
    objManager->FindLayer(LayerNames::Stage)->AddObject(scaleObject2);
    objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
    

}



void SizeScalingLevel::UpdateCollisionBox(Object* obj1, Object* obj2)
{
	obj1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(obj1, Physics::ObjectType::RECTANGLE);
	obj2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(obj2, Physics::ObjectType::RECTANGLE);
}

void SizeScalingLevel::PlayerScaling()
{
	const float minimum_scaling_limit = 125.f;
	const float scaling_constant = 1.f;

	if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		if (player1->GetScale().x <= minimum_scaling_limit || player2->GetComponentByTemplate<Physics>()->IsCollided())
		{
			return;
		}
		vector2 player1OldScale = player1->GetScale();
		vector2 player2OldScale = player2->GetScale();

		player1->SetScale(player1->GetScale() - scaling_constant);
		player2->SetScale(player2->GetScale() + scaling_constant);
		UpdateCollisionBox(player1, player2);

		Collision();
		if (player2->GetComponentByTemplate<Physics>()->IsCollided())
		{
			player1->SetScale(player1OldScale);
			player2->SetScale(player2OldScale);
			UpdateCollisionBox(player1, player2);
		}
	}
	if (input.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
	{
		if (player2->GetScale().x <= minimum_scaling_limit || player1->GetComponentByTemplate<Physics>()->IsCollided())
		{
			return;
		}
		vector2 player1OldScale = player1->GetScale();
		vector2 player2OldScale = player2->GetScale();

		player1->SetScale(player1->GetScale() + scaling_constant);
		player2->SetScale(player2->GetScale() - scaling_constant);
		UpdateCollisionBox(player1, player2);

		Collision();

		if (player1->GetComponentByTemplate<Physics>()->IsCollided())
		{
			player1->SetScale(player1OldScale);
			player2->SetScale(player2OldScale);
			UpdateCollisionBox(player1, player2);
		}
	}
}