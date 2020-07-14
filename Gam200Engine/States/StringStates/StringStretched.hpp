/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringStretched.hpp
Author
		sinil.gang rtd99062@gmail.com
Creation Date: 01.29.2020

	Header file for StringStretched State
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Strings/String.hpp>

class StringStretched : public State<String>
{
public:
	static StringStretched* Get();
	~StringStretched() = default;
	
	void Enter(String* obj) override;
	void Execute(String* obj, float dt) override;
	void Exit(String* obj) override;
private:
	StringStretched() = default;

	float lastT;
	bool DidPlaySound;
};