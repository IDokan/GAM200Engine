/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Walking.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.14.2020

	Header file for walking state to test FSM works correctly.
******************************************************************************/
#pragma once
#include <States/State.hpp>
#include <Object/Object.hpp>

// for DEBUG
#include <iostream>

class Walking : public State<Object>
{
public:
	virtual ~Walking();

	// this will execute when  the state is entered
	virtual void Enter(Object* obj);

	// this is called by the object's update function in each update step
	virtual void Execute(Object* obj);

	// this will execute when the state is exited
	virtual void Exit(Object* obj);
};