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

StringStretched* StringStretched::Get()
{
	static StringStretched* state = new StringStretched();
	return state;
}

void StringStretched::Enter(String* /*obj*/)
{
	printf("String is began to stretched!\n");
}

void StringStretched::Execute(String* obj)
{
	const float stringLength = obj->GetStringLength();

	const auto& vertices = obj->GetVertices();

	// To be calculated
	vector2 delta{3.f, 0.f};
	MessageDispatcher::GetDispatcher()->DispatchMessage(MessageObjects::String_Object, MessageObjects::Player1, MessageTypes::MoveTo, 0, &delta);
	if (stringLength < String::String_Stretching_Length)
	{
		obj->GetComponentByTemplate < StateMachine<String>>()->ChangeState(StringIdle::Get());
	}
}

void StringStretched::Exit(String* /*obj*/)
{
	printf("No more stretching\n");
}