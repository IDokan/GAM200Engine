/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringIdle.cpp
Author
		sinil.gang rtd99062@gmail.com
Creation Date: 01.29.2020

	Source file for StringIdle State
******************************************************************************/
#include <States/StringStates/StringIdle.hpp>
#include <Component/StateMachine.hpp>
#include <States/StringStates/StringStretched.hpp>

StringIdle* StringIdle::Get()
{
	static StringIdle* state = new StringIdle();
	return state;
}

void StringIdle::Enter(String* /*obj*/)
{
	printf("String enter StringIdle State\n");
}

void StringIdle::Execute(String* obj, float /*dt*/)
{
	const float stringLength = obj->GetStringLength();
	
	if (stringLength > String::String_Stretching_Length)
	{
		obj->GetComponentByTemplate<StateMachine<String>>()->ChangeState(StringStretched::Get());
	}
}

void StringIdle::Exit(String* /*obj*/)
{
	printf("String exit StringIdle State\n");
}
