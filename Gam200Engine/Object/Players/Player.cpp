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
#include <States/PlayerStates/InRefrigerator.hpp>
#include <States/PlayerStates/Idle.hpp>
#include <Component/MessageCapable.hpp>
#include <Systems/MessageSystem/Message.hpp>
#include <Object/DepthStandard.hpp>

#include <States/PlayerStates/UpdateAnimation.hpp>
#include <States/PlayerStates/Pause.hpp>
#include <States/PlayerStates/PlayerReachesGoal.hpp>

#include <Scenes/SceneManager.hpp>

Player::Player(Identifier player, const Transform& playerTransformData)
    :Object(), id(player), isBlock(false), lastAnimationState(0)
{
	// Initialize transform data
	Object::SetTranslation(playerTransformData.GetTranslation());
	SetScale(playerTransformData.GetScale());
	SetRotation(playerTransformData.GetRotation());
	SetDepth(Depth_Standard::Player);

	Animation* playerAnimation = new Animation(this);
	Object::AddComponent(playerAnimation);
	playerAnimation->SetFrame(8);
	playerAnimation->SetNumOfState(7);
	playerAnimation->SetImage("../assets/textures/Cheese/cheese_move.png");
	playerAnimation->SetSpeed(5.f);
	

	Object::AddComponent(new Physics(this));
    GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, Physics::ObjectType::RECTANGLE, vector2{ 0.f,0.f }, vector2{-40.f,-40.f});

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

	// Add essential components 
	Object::AddComponent(new StateMachine<Player>(this));

	if (SceneManager::GetSceneManager()->GetCurrentScene()->IsMenu() == true)
	{
		GetComponentByTemplate<StateMachine<Player>>()->SetCurrentState(Pause::Get());
	}
	else
	{
		GetComponentByTemplate<StateMachine<Player>>()->SetCurrentState(InRefrigerator::Get());
		InRefrigerator::Get()->Enter(this);
	}
	GetComponentByTemplate<StateMachine<Player>>()->SetGlobalState(UpdateAnimation::Get());
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

void Player::SetIsBlock(bool flag)
{
    isBlock = flag;
}

bool Player::GetIsBlock()
{
    return isBlock;
}

void Player::SetCurrentAnimationState(int state)
{
    lastAnimationState = state;
}

int Player::GetLastAnimationState()
{
    return lastAnimationState;
}

void Player::LoadPlayer1Layout()
{
	Object::SetObjectName("Player1");
	Object::SetObjectType(ObjectType::PLAYER_1);

	GetComponentByTemplate<Animation>()->SetColor(Graphics::Color4f{ 1.f, 0.95f, 0.f });

	AddComponent(new MessageCapable(this, MessageObjects::Player1,
		[&](const Message& msg) -> bool
		{
			const float scalerWhenPlayerIsStopping = (String::String_Max_Length - String::String_Stretching_Length) / 10.f;
			vector2 force{};
			vector2 velocity{};
			float scalerBasedOnVelocity = 0;
			switch(msg.Msg)
			{
			case MessageTypes::PlayerIsDead:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Pause::Get());
				break;
			case MessageTypes::PlayerReachedGoal:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Pause::Get());
				break;
			case MessageTypes::MoveToRelativePosition:
				SetTranslation(GetTranslation() + *reinterpret_cast<vector2*>(msg.ExtraInfo));
				GetComponentByTemplate<Physics>()->SetPosition(GetTranslation());
				break;
			case MessageTypes::MoveToAbsolutePosition:
				SetTranslation(*reinterpret_cast<vector2*>(msg.ExtraInfo));
				GetComponentByTemplate<Physics>()->SetPosition(GetTranslation());
				break;
			case MessageTypes::AddStringForce:
				velocity = GetComponentByTemplate<Physics>()->GetVelocity();
				force = *reinterpret_cast<vector2*>(msg.ExtraInfo);
				scalerBasedOnVelocity = magnitude(velocity);

				// When player stop, force much more stronger dramatically..
				if ((GetComponentByTemplate<StateMachine<Player>>()->GetCurrentState() == Idle::Get())
					)
				{
					GetComponentByTemplate<Physics>()->AddForce(force * scalerWhenPlayerIsStopping);
				}
				else
				{
					GetComponentByTemplate<Physics>()->AddForce(force * scalerBasedOnVelocity);
				}
				break;
			case MessageTypes::SceneComplete:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Pause::Get());
				break;
			case MessageTypes::GameRestarted:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(InRefrigerator::Get());
				GetComponentByTemplate<StateMachine<Player>>()->SetGlobalState(UpdateAnimation::Get());
				break;
			case MessageTypes::Pause:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Pause::Get());
				break;
			case MessageTypes::Resume:
				GetComponentByTemplate<StateMachine<Player>>()->RevertToPreviousState();
				break;
			case MessageTypes::CancelScaling:

				if (GetScale().x > UpdateAnimation::minimum_scaling_limit)
				{
					SetScale(GetScale().x + UpdateAnimation::scaling_constant);
					GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, Physics::ObjectType::RECTANGLE, vector2{ 0.f, 0.f }, vector2{ UpdateAnimation::collisionBoxOffset });
				}
				break;
			case MessageTypes::YouDead:
				GetComponentByTemplate<Animation>()->SetState(3);
				GetComponentByTemplate<StateMachine<Player>>()->SetGlobalState(nullptr);
				break;
			case MessageTypes::ObserveFriendIsDied:
				GetComponentByTemplate<Animation>()->SetState(6);
				GetComponentByTemplate<StateMachine<Player>>()->SetGlobalState(nullptr);
				break;
			default:
				return false;
			}
			return true;
		}
	));
}

void Player::LoadPlayer2Layout()
{
	Object::SetObjectName("Player2");
	Object::SetObjectType(ObjectType::PLAYER_2);
	
	AddComponent(new MessageCapable(this, MessageObjects::Player2,
		[&](const Message& msg) -> bool
		{
			const float scalerWhenPlayerIsStopping = (String::String_Max_Length - String::String_Stretching_Length) / 10.f;
			vector2 force{};
			vector2 velocity{};
			float scalerBasedOnVelocity = 0;
			switch (msg.Msg)
			{
			case MessageTypes::PlayerIsDead:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Pause::Get());
				break;
			case MessageTypes::PlayerReachedGoal:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Pause::Get());
				break;
			case MessageTypes::MoveToRelativePosition:
				SetTranslation(GetTranslation() + *reinterpret_cast<vector2*>(msg.ExtraInfo));
				GetComponentByTemplate<Physics>()->SetPosition(GetTranslation());
				break;
			case MessageTypes::MoveToAbsolutePosition:
				SetTranslation(*reinterpret_cast<vector2*>(msg.ExtraInfo));
				GetComponentByTemplate<Physics>()->SetPosition(GetTranslation());
				break;
			case MessageTypes::AddStringForce:
				velocity = GetComponentByTemplate<Physics>()->GetVelocity();
				force = *reinterpret_cast<vector2*>(msg.ExtraInfo);
				scalerBasedOnVelocity = magnitude(velocity);

				// When player stop, force much more stronger dramatically..
				if ((GetComponentByTemplate<StateMachine<Player>>()->GetCurrentState() == Idle::Get())
					)
				{
						GetComponentByTemplate<Physics>()->AddForce(force * scalerWhenPlayerIsStopping);
				}
				else
				{
					GetComponentByTemplate<Physics>()->AddForce(force * scalerBasedOnVelocity	);
				}
				break;
			case MessageTypes::SceneComplete:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Pause::Get());
				break;
			case MessageTypes::GameRestarted:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(InRefrigerator::Get());
				GetComponentByTemplate<StateMachine<Player>>()->SetGlobalState(UpdateAnimation::Get());
				break;
			case MessageTypes::Pause:
				GetComponentByTemplate<StateMachine<Player>>()->ChangeState(Pause::Get());
				break;
			case MessageTypes::Resume:
				GetComponentByTemplate<StateMachine<Player>>()->RevertToPreviousState();
				break;
			case MessageTypes::CancelScaling:

				if (GetScale().x > UpdateAnimation::minimum_scaling_limit)
				{
					SetScale(GetScale().x + UpdateAnimation::scaling_constant);
					GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(this, Physics::ObjectType::RECTANGLE, vector2{ 0.f, 0.f }, vector2{ UpdateAnimation::collisionBoxOffset });
				}
				break;
			case MessageTypes::YouDead:
				GetComponentByTemplate<Animation>()->SetState(3);
				GetComponentByTemplate<StateMachine<Player>>()->SetGlobalState(nullptr);
				break;
			case MessageTypes::ObserveFriendIsDied:
				GetComponentByTemplate<Animation>()->SetState(6);
				GetComponentByTemplate<StateMachine<Player>>()->SetGlobalState(nullptr);
				break;
			default:
				return false;
			}
			return true;
		}
	));
}
