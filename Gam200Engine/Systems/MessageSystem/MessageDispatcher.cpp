/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MessageDispatcher.cpp
Author
		sinil.gang
		rtd99062@gmail.com
Creation Date: 01.14.2020

	Source file for Message Dispatcher
		It manages dispatching message
******************************************************************************/

#include <Systems/MessageSystem/MessageDispatcher.hpp>

MessageDispatcher* MessageDispatcher::GetDispatcher()
{
	static MessageDispatcher* messageDispatcher = new MessageDispatcher();
	return messageDispatcher;
}

void MessageDispatcher::DispatchMessage(int sender, int receiver, int msg, double delay, void* ExtraInfo)
{
}

void MessageDispatcher::DispatchDelayedMessages()
{
}

MessageDispatcher::MessageDispatcher()
{
}

void MessageDispatcher::Discharge(Object* receiver, const Message& msg)
{
}
