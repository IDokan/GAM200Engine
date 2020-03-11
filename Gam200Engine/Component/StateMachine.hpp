/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StateMachine.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.13.2020

	Header file for State Machine that manage each states
******************************************************************************/
#pragma once

#include <Component/Component.hpp>
#include <cassert>
#include <States/State.hpp>

template <class object_type>
class StateMachine : public Component
{
public:
	StateMachine(object_type* owner);
	~StateMachine() = default;

	// Setters
	void SetCurrentState(State<object_type>* currentState_) noexcept;
	void SetPreviousState(State<object_type>* previousState_) noexcept;
	void SetGlobalState(State<object_type>* globalState_) noexcept;
	
	// Getters
	State<object_type>* GetCurrentState() const noexcept;
	State<object_type>* GetPreviousState() const noexcept;
	State<object_type>* GetGlobalState() const noexcept;

	// call this when FSM is attached or detached on arbitrary object
	void Init() override;
	void Clear() override;
	
	// call this to update the FSM
	void Update(float dt) override;

	// change to a new state
	void ChangeState(State<object_type>* pNewState);

	// change stateback to the previous state (Blip)
	void RevertToPreviousState();

	// returns true if the current state's type is equal to
	// the type of the class passed as a parameter.
	bool isInState(const State<object_type>* state) const;

private:
	// a pointer to the agent that owns this instance
	object_type* originalOwner;

	State<object_type>* currentState;

	// a record of the last state the agent was in
	State<object_type>* previousState;

	// this state logic is called every time the FSM is updated
	State<object_type>* globalState;
};

#include <Component/StateMachine.inl>
