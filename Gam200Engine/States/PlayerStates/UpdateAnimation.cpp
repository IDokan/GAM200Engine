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




    //if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
    //{

    //    if (player1->GetScale().x <= minimum_scaling_limit || player2->GetComponentByTemplate<Physics>()->IsCollided())
    //    {

    //        return;
    //    }
    //    vector2 object1OldScale = player1->GetScale();
    //    vector2 object2OldScale = player2->GetScale();

    //    player1->SetScale(player1->GetScale() - scaling_constant);
    //    player2->SetScale(player2->GetScale() + scaling_constant);
    //    UpdateCollisionBox(player1, player2);

    //    player1->GetComponentByTemplate<Physics>()->ManageCollision();
    //    /// Below code does not apply currently,
    //    if (player2->GetComponentByTemplate<Physics>()->IsCollided())
    //    {
    //        player1->SetScale(object1OldScale);
    //        player2->SetScale(object2OldScale);
    //        UpdateCollisionBox(player1, player2);
    //    }
    //}
    //if (input.IsKeyReleased(GLFW_KEY_LEFT_SHIFT) || input.IsKeyReleased(GLFW_KEY_RIGHT_SHIFT))
    //{
    //    TestSoundForCrush.Stop_Sound(SOUNDS::SHAREWEIGHT_SOUND);

    //}

    //if (input.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
    //{
    //    if (player2->GetScale().x <= minimum_scaling_limit || player1->GetComponentByTemplate<Physics>()->IsCollided())
    //    {
    //        return;
    //    }
    //    vector2 object1OldScale = player1->GetScale();
    //    vector2 object2OldScale = player2->GetScale();

    //    player1->SetScale(player1->GetScale() + scaling_constant);
    //    player2->SetScale(player2->GetScale() - scaling_constant);
    //    UpdateCollisionBox(player1, player2);

    //    player1->GetComponentByTemplate<Physics>()->ManageCollision();

    //    if (player1->GetComponentByTemplate<Physics>()->IsCollided())
    //    {
    //        player1->SetScale(object1OldScale);
    //        player2->SetScale(object2OldScale);
    //        UpdateCollisionBox(player1, player2);
    //    }
    //}

    //if (input.IsKeyReleased(GLFW_KEY_LEFT_SHIFT) || input.IsKeyReleased(GLFW_KEY_RIGHT_SHIFT))
    //{
    //    TestSoundForCrush.Stop_Sound(SOUNDS::SHAREWEIGHT_SOUND);

    //}
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
    else if(input.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
    {
        if (player->GetScale().x >= maximum_scaling_limit)
        {
            return;
        }

        vector2 player1OldScale = player->GetScale();
        player->SetScale(player1OldScale + scaling_constant);
        UpdateCollisionBox(player);


        player->GetComponentByTemplate<Physics>()->ManageCollision();
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

        vector2 player1OldScale = player->GetScale();
        player->SetScale(player1OldScale - scaling_constant);
        UpdateCollisionBox(player);


        player->GetComponentByTemplate<Physics>()->ManageCollision();
    }
    else if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        if (player->GetScale().x >= maximum_scaling_limit)
        {
            return;
        }

        vector2 player1OldScale = player->GetScale();
        player->SetScale(player1OldScale + scaling_constant);
        UpdateCollisionBox(player);


        player->GetComponentByTemplate<Physics>()->ManageCollision();
    }
}

UpdateAnimation::UpdateAnimation()
{
}

void UpdateAnimation::UpdateCollisionBox(Player* player)
{
        player->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player, Physics::ObjectType::RECTANGLE);
}

void UpdateAnimation::Enter(Player* /*obj*/)
{
}

void UpdateAnimation::Execute(Player* obj, float /*dt*/)
{
	// TODO: Change Mechs with Co-developer's feedbacks.
	vector2 playerDistance = obj->GetComponentByTemplate<Physics>()->GetVelocity();
	static constexpr int RIGHT = 0;
	static constexpr int LEFT = 1;
	static constexpr int UP = 2;
	if (playerDistance.x > 0)
	{
		obj->GetComponentByTemplate<Animation>()->SetState(RIGHT);
	}
	else if (playerDistance.x < 0)
	{
		obj->GetComponentByTemplate<Animation>()->SetState(LEFT);
	}
	else
	{
		// Do nothing
	}

	Resizing(obj);
}

void UpdateAnimation::Exit(Player* /*obj*/)
{
}
