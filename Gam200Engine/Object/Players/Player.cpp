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
#include <Object/DepthStandard.hpp>
#include <States/PlayerStates/Idle.hpp>
#include <Component/MessageCapable.hpp>
#include <Systems/MessageSystem/Message.hpp>

Player::Player(Identifier player)
	:Object(), id(player)
{
	Object::AddComponent(new StateMachine<Player>(this));
	GetComponentByTemplate<StateMachine<Player>>()->SetCurrentState(Idle::Get());

	Object::AddComponent(new Sprite(this));
	GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f{ 1.f });

	switch (player)
	{
	case Identifier::Player1:
		LoadPlayer1Layout();
		break;
	case Identifier::Player2:
		LoadPlayer2Layout();
		break;
	default:;
	}

	Object::AddComponent(new Physics(this));
	GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, Physics::ObjectType::RECTANGLE);
}

Player::Player(std::string _playerName, const vector2 playerPos, const vector2 playerScale, Physics::ObjectType _objectType,
	float _depth, Graphics::Color4f _color, vector2 positionAdj, vector2 scaleAdj)
	:Object(), id(Identifier::UNDEFINED)
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

Player::Identifier Player::GetID() const noexcept
{
	return id;
}

void Player::LoadPlayer1Layout()
{
	Object::SetObjectName("Player 1");
	Object::SetObjectType(ObjectType::PLAYER_1);

	// TODO: Implement with File I/O
	Object::SetTranslation(vector2{ -200.f, -400.f });
	SetScale(vector2{ 150.f });
	SetDepth(Depth_Standard::Player);
	//

	AddComponent(new MessageCapable(this, MessageObjects::Player1,
		[&](const Message& msg) -> bool
		{
			switch(msg.Msg)
			{
			case MessageTypes::PlayerIsDead:
				break;
			case MessageTypes::PlayerReachedGoal:
				break;
			case MessageTypes::MoveToRelativePosition:
				SetTranslation(GetTranslation() + *reinterpret_cast<vector2*>(msg.ExtraInfo));
				GetComponentByTemplate<Physics>()->SetPosition(GetTranslation());
				break;
			case MessageTypes::MoveToAbsolutePosition:
				SetTranslation(*reinterpret_cast<vector2*>(msg.ExtraInfo));
				GetComponentByTemplate<Physics>()->SetPosition(GetTranslation());
				break;
			case MessageTypes::AddForce:
				GetComponentByTemplate<Physics>()->AddForce(*reinterpret_cast<vector2*>(msg.ExtraInfo));
			default:
				return false;
			}
			return true;
		}
	));

	GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p1.png");
}

void Player::LoadPlayer2Layout()
{
	Object::SetObjectName("Player 2");
	Object::SetObjectType(ObjectType::PLAYER_2);
	
	// TODO: Implement with File I/O
	Object::SetTranslation(vector2{ 200.f, -400.f });
	SetScale(vector2{ 150.f });
	SetDepth(Depth_Standard::Player);
	//
	
	AddComponent(new MessageCapable(this, MessageObjects::Player2,
		[&](const Message& msg) -> bool
		{
			switch (msg.Msg)
			{
			case MessageTypes::PlayerIsDead:
				break;
			case MessageTypes::PlayerReachedGoal:
				break;
			case MessageTypes::MoveToRelativePosition:
				SetTranslation(GetTranslation() + *reinterpret_cast<vector2*>(msg.ExtraInfo));
				GetComponentByTemplate<Physics>()->SetPosition(GetTranslation());
				break;
			case MessageTypes::MoveToAbsolutePosition:
				SetTranslation(*reinterpret_cast<vector2*>(msg.ExtraInfo));
				GetComponentByTemplate<Physics>()->SetPosition(GetTranslation());
				break;
			case MessageTypes::AddForce:
				GetComponentByTemplate<Physics>()->AddForce(*reinterpret_cast<vector2*>(msg.ExtraInfo));
			default:
				return false;
			}
			return true;
		}
	));

	GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");
}
