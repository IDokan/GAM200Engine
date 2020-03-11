/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringIdle.hpp
Author
		sinil.gang rtd99062@gmail.com
Creation Date: 01.29.2020

	Header file for StringIdle State
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/Strings/String.hpp>

class StringIdle : public State<String>
{
public:
	static StringIdle* Get();
	~StringIdle() = default;
	
	void Enter(String* obj) override;
	void Execute(String* obj) override;
	void Exit(String* obj) override;
private:
	StringIdle() = default;
};