/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   State.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.13.2020

	Header file for State abstract class
		Each derived state classes need to be derived from this class
******************************************************************************/
#pragma once

template<class object_type>
class State
{
public:
	virtual ~State(){}

	// this will execute when  the state is entered
	virtual void Enter(object_type* obj) = 0;

	// this is called by the object's update function in each update step
	virtual void Update(object_type* obj) = 0;

	// this will execute when the state is exited
	virtual void Exit(object_type* obj) = 0;
};