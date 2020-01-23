/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Player.cpp
Author
		dbsqhd106@gmail.com
Creation Date: 23th/Jan/2020

	Source file for the Player
******************************************************************************/
#include  <Object/Players/Player.h>
#include <Systems/Input.hpp>
#include <Component/StateMachine.hpp>

Player::Player(Player_Identifier player)
	:Object(), id(player)
{
	Object::AddComponent(new StateMachine<Player>(this));
	
	Object::AddComponent(new Sprite(this));
	GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f });

	switch (player)
	{
	case Player_Identifier::Player1:
		LoadPlayer1Layout();
		break;
	case Player_Identifier::Player2:
		LoadPlayer2Layout();
		break;
	default: ;
	}
	
	Object::AddComponent(new Physics(this));
	GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, Physics::ObjectType::RECTANGLE);
}

Player::Player(std::string _playerName, const vector2 playerPos, const vector2 playerScale, Physics::ObjectType _objectType,
    float _depth, Graphics::Color4f _color, vector2 positionAdj, vector2 scaleAdj)
    :Object()
{
	Object::SetObjectName(std::move(_playerName));

	Object::SetTranslation(playerPos);

	SetScale(playerScale);

	SetDepth(_depth);

	Object::AddComponent(new Sprite(this));

	Object::AddComponent(new Physics(this));

	GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, _objectType, positionAdj, scaleAdj);

	GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ _color });
	GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");
};


void Player::Move() noexcept
{
    /**********************Moving player 2*******************************************/
    if (input.IsKeyPressed(GLFW_KEY_UP))
    {
        GetComponentByTemplate<Physics>()->SetVelocity(0.f, 3.f);
        if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_LEFT))
    {
        GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            GetComponentByTemplate<Physics>()->SetVelocity(-3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_DOWN))
    {
        GetComponentByTemplate<Physics>()->SetVelocity(0.f, -3.f);

        if (input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            GetComponentByTemplate<Physics>()->SetVelocity(-3.f, -3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyPressed(GLFW_KEY_RIGHT))
    {
        GetComponentByTemplate<Physics>()->SetVelocity(3.f, 0.f);
        if (input.IsKeyPressed(GLFW_KEY_UP))
        {
            GetComponentByTemplate<Physics>()->SetVelocity(3.f, 3.f);
        }
        else if (input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            GetComponentByTemplate<Physics>()->SetVelocity(3.f, -3.f);
        }
    }
    if (input.IsKeyReleased(GLFW_KEY_UP) && input.IsKeyReleased(GLFW_KEY_LEFT) && input.IsKeyReleased(GLFW_KEY_DOWN) && input.IsKeyReleased(GLFW_KEY_RIGHT))
    {
        GetComponentByTemplate<Physics>()->SetVelocity(0.f, 0.f);
    }
}

void Player::LoadPlayer1Layout()
{
	Object::SetObjectName("Player 1");
	
	// TODO: Implement with File I/O
	Object::SetTranslation(vector2{ -200.f, -400.f });
	SetScale(vector2{ 150.f });
	SetDepth(Depth_Standard::Player);
	//

	GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p1.png");
}

void Player::LoadPlayer2Layout()
{
	Object::SetObjectName("Player 2");

	// TODO: Implement with File I/O
	Object::SetTranslation(vector2{ 200.f, -400.f });
	SetScale(vector2{ 150.f });
	SetDepth(Depth_Standard::Player);
	//

	GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");
}
