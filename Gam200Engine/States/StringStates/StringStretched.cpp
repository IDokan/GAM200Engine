/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringStretched.cpp
Author
		sinil.gang rtd99062@gmail.com
Creation Date: 01.29.2020

	Source file for StringStretched State
******************************************************************************/
#include <States/StringStates/StringStretched.hpp>
#include <Component/StateMachine.hpp>
#include <States/StringStates/StringIdle.hpp>
#include <Systems/MessageSystem/MessageDispatcher.hpp>
#include <Scenes/SceneManager.hpp>

StringStretched* StringStretched::Get()
{
	static StringStretched* state = new StringStretched();
	return state;
}

void StringStretched::Enter(String* /*obj*/)
{
	printf("String is began to stretched!\n");
}

void StringStretched::Execute(String* obj, float /*dt*/)
{
	const float stringLength = obj->GetStringLength();

	const auto& vertices = obj->GetVertices();

	if (stringLength < String::String_Stretching_Length)
	{
		obj->GetComponentByTemplate < StateMachine<String>>()->ChangeState(StringIdle::Get());
	}
	else
	{
		vector2 force1{ normalize(vertices.at(1).position - vertices.at(0).position) };
		vector2 force2{ normalize(vertices.at(vertices.size() - 2).position - vertices.back().position) };

		float t = (stringLength - String::String_Stretching_Length) / (String::String_Max_Length - String::String_Stretching_Length);
		// I can be happy when there is a minimum value.
		static const float MinimumScale = (String::String_Max_Length - String::String_Stretching_Length) / (String::String_Max_Length * 100.f);
		if (t < MinimumScale)
		{
			t = MinimumScale;
		}
		
		force1 *= t;
		force2 *= t;
		
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::String_Object, MessageObjects::Player1, MessageTypes::AddStringForce, 0, &force1);
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::String_Object, MessageObjects::Player2, MessageTypes::AddStringForce, 0, &force2);

		float currentStringLength = obj->GetStringLength();
		MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::String_Object, MessageObjects::StringLengthUI, MessageTypes::StringIsStreching, 0, &currentStringLength);
	}
}

void StringStretched::Exit(String* /*obj*/)
{
	SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(CHEESE_RESTORED_SOUND);
	printf("No more stretching\n");

}