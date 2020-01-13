/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StateMachine.inl
Author
		Kang rtd99062@gmail.com
Creation Date: 01.13.2020

	inline file for State Machine that manage each states
******************************************************************************/

template <class object_type>
StateMachine<object_type>::StateMachine(object_type* owner)
	: Component(owner), originalOwner(owner), currentState(nullptr), previousState(nullptr), globalState(nullptr)
{
}

template <class object_type>
void StateMachine<object_type>::SetCurrentState(State<object_type>* currentState_) noexcept
{
	currentState = currentState_;
}

template <class object_type>
void StateMachine<object_type>::SetPreviousState(State<object_type>* previousState_) noexcept
{
	previousState = previousState_;
}

template <class object_type>
void StateMachine<object_type>::SetGlobalState(State<object_type>* globalState_) noexcept
{
	globalState = globalState_;
}

template <class object_type>
State<object_type>* StateMachine<object_type>::GetCurrentState() const noexcept
{
	return currentState;
}

template <class object_type>
State<object_type>* StateMachine<object_type>::GetPreviousState() const noexcept
{
	return previousState;
}

template <class object_type>
State<object_type>* StateMachine<object_type>::GetGlobalState() const noexcept
{
	return globalState;
}

template <class object_type>
void StateMachine<object_type>::Init()
{
}

template <class object_type>
void StateMachine<object_type>::Clear()
{
}


template <class object_type>
void StateMachine<object_type>::Update(float dt)
{
	// if a global state exists, call its execute method
	if (globalState)
	{
		globalState->Execute(originalOwner);
	}

	if (currentState)
	{
		currentState->Execute(originalOwner);
	}
}

template <class object_type>
void StateMachine<object_type>::ChangeState(State<object_type>* pNewState)
{
	assert(pNewState &&
		"<StateMachine::ChangeState>: trying to change to a null state");

	// keep a record of the previous state
	previousState = currentState;

	// call the exit method of the existing state
	currentState->Exit(originalOwner);

	// change state to the new state
	currentState = pNewState;

	// call the entry method of the new state
	currentState->Enter(originalOwner);
}

template <class object_type>
void StateMachine<object_type>::RevertToPreviousState()
{
	ChangeState(previousState);
}

template <class object_type>
bool StateMachine<object_type>::isInState(const State<object_type>* state) const
{
	// TODO: test it after instantiate this code
	return typeid(currentState) == typeid(state);
}