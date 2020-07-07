/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   UpdateAnimation.hpp
Author
        Kang rtd99062@gmail.com
Creation Date: 03.08.2020

    Source file for UpdateAnimation State
        This state is global state which update animation with object's velocity.
******************************************************************************/
#include <States/PlayerStates/UpdateAnimation.hpp>
#include <Component/StateMachine.hpp>

#include <Systems/Input.hpp>
#include <Scenes\SceneManager.hpp>

#include <Systems/MessageSystem/MessageDispatcher.hpp>
class SoundManager smAnimation;
UpdateAnimation* UpdateAnimation::Get()
{
    static UpdateAnimation* state = new UpdateAnimation();
    return state;
}

void UpdateAnimation::Resizing(Player* player)
{
    switch (player->GetID())
    {
    case Player::Identifier::Player1:
        ResizingPlayer1(player);
        break;
    case Player::Identifier::Player2:
        ResizingPlayer2(player);
        break;
    default:
        break;
    }
}

void UpdateAnimation::ResizingPlayer1(Player* player)
{
    if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {

        if (player->GetScale().x <= minimum_scaling_limit)
        {
            return;
        }

		vector2 player1OldScale = player->GetScale();
		player->SetScale(player1OldScale - scaling_constant);
		UpdateCollisionBox(player);

        player->GetComponentByTemplate<Physics>()->ManageCollision();
    }
    else if (input.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
    {
        if (player->GetScale().x >= maximum_scaling_limit)
        {
            return;
        }

		vector2 player1OldScale = player->GetScale();
		player->SetScale(player1OldScale + scaling_constant);
		UpdateCollisionBox(player);


		player->GetComponentByTemplate<Physics>()->ManageCollision();

		if (player->GetComponentByTemplate<Physics>()->IsCollided())
		{
			player->SetScale(player->GetScale() - scaling_constant);
			MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Player1, MessageObjects::Player2, MessageTypes::CancelScaling);
			UpdateCollisionBox(player);
		}
	}
}

void UpdateAnimation::ResizingPlayer2(Player* player)
{
	if (input.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
	{
		if (player->GetScale().x <= minimum_scaling_limit)
		{
			return;
		}

		vector2 player2OldScale = player->GetScale();
		player->SetScale(player2OldScale - scaling_constant);
		UpdateCollisionBox(player);


		player->GetComponentByTemplate<Physics>()->ManageCollision();
	}
	if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		if (player->GetScale().x >= maximum_scaling_limit)
		{
			return;
		}

		vector2 player2OldScale = player->GetScale();
		player->SetScale(player2OldScale + scaling_constant);
		UpdateCollisionBox(player);


		player->GetComponentByTemplate<Physics>()->ManageCollision();

		if (player->GetComponentByTemplate<Physics>()->IsCollided())
		{
			player->SetScale(player->GetScale() - scaling_constant);
			MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::Player2, MessageObjects::Player1, MessageTypes::CancelScaling);
			UpdateCollisionBox(player);
		}
	}
}


UpdateAnimation::UpdateAnimation() :isSoundPlay(false)
{
}

void UpdateAnimation::UpdateCollisionBox(Player* player)
{
	player->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player, Physics::ObjectType::RECTANGLE, vector2{ 0.f, 0.f }, vector2{ collisionBoxOffset });
}

void UpdateAnimation::Enter(Player* /*obj*/)
{
    isSoundPlay = false;
}

void UpdateAnimation::PlayResizingSound()
{
    if (isSoundPlay == true) 
    {
        if (input.IsKeyReleased(GLFW_KEY_LEFT_SHIFT) && input.IsKeyReleased(GLFW_KEY_RIGHT_SHIFT)) 
        {
            isSoundPlay = false;  
         //   smAnimation = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
            smAnimation.Stop_Sound(SOUNDS::SIZE_SHARE_SOUND);
        }
    }
    else 
    {
        if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT) || input.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
        {
            isSoundPlay = true;
            smAnimation = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager();
            smAnimation.Play_Sound(SOUNDS::SIZE_SHARE_SOUND);
        }
    }

}

void UpdateAnimation::Execute(Player* obj, float /*dt*/)
{

	if (input.IsKeyTriggered(GLFW_KEY_0))
	{
		Physics* physics = obj->GetComponentByTemplate<Physics>();
		physics->ActiveGhostCollision(!physics->GetIsGhost());
	}

    // TODO: Change Mechs with Co-developer's feedbacks.
    vector2 playerDistance = obj->GetComponentByTemplate<Physics>()->GetVelocity();
    static constexpr int RIGHT = 0;
    static constexpr int LEFT = 1;
    static constexpr int UP = 2;
    static constexpr int STRUGGLE_RIGHT = 4;
    static constexpr int STRUGGLE_LEFT = 5;

    if (obj->GetIsBlock() == true)
    {
        if (obj->GetLastAnimationState() == RIGHT)
        {
            obj->GetComponentByTemplate<Animation>()->SetState(STRUGGLE_RIGHT);
        }
        else
        {
            obj->GetComponentByTemplate<Animation>()->SetState(STRUGGLE_LEFT);
        }
    }
    else if (playerDistance.x > 0)
    {
        obj->SetCurrentAnimationState(RIGHT);
        obj->GetComponentByTemplate<Animation>()->SetState(RIGHT);
    }
    else if (playerDistance.x < 0)
    {
        obj->SetCurrentAnimationState(LEFT);
        obj->GetComponentByTemplate<Animation>()->SetState(LEFT);
    }
    else
    {
        if (obj->GetLastAnimationState() == RIGHT)
        {
            obj->GetComponentByTemplate<Animation>()->SetState(RIGHT);
        }
        else
        {
            obj->GetComponentByTemplate<Animation>()->SetState(LEFT);
        }
        // Do nothing
    }
   
    Resizing(obj);
    PlayResizingSound();
    
}

void UpdateAnimation::Exit(Player* /*obj*/)
{
}
