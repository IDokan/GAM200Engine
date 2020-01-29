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

#include <cassert>
#include <Systems/MessageSystem/MessageDispatcher.hpp>
#include <Systems/MessageSystem/MessageCapableObjectManager.hpp>
#include <Systems/MessageSystem/Message.hpp>
#include <Component/MessageCapable.hpp>
#include <Timer.hpp>
#include <Object/Object.hpp>

MessageDispatcher* MessageDispatcher::GetDispatcher()
{
	static MessageDispatcher* messageDispatcher = new MessageDispatcher();
	return messageDispatcher;
}

void MessageDispatcher::DispatchMessage(MessageObjects sender, MessageObjects receiver, MessageTypes msg, double delay,
	void* ExtraInfo)
{
	// Get a pointer to the receiver of the message
	Object* objReceiver = MessageCapableObjectManager::GetMessageObjectManager()->GetObjectFromID(receiver);

	// Create the message
	Message message(sender, receiver, msg, 0.0, ExtraInfo);

	// if there is no delay, route the telegram immediately
	if (delay <= 0.0)
	{
		Discharge(objReceiver, message);
	}
	// else calculate the time when the message should be diapatched
	else
	{
		double currentTime = Timer::GetTimer()->GetCurrentTime();

		message.DispatchTime = currentTime + delay;

		// and put it in the queue
		delayed_messages.insert(message);
	}
}

void MessageDispatcher::DispatchDelayedMessages()
{
	// when message queue is missing, do nothing for a few of optimizing.
	if (delayed_messages.empty())
	{
		return;
	}
	
	// first get current time
	double currentTime = Timer::GetTimer()->GetCurrentTime();

	// now peek at the queue to see if any messages need dispatching.
	// remove all messages from the front of the queue that have gone
	// past their sell-by date
	while (
		(delayed_messages.begin()->DispatchTime < currentTime) &&
		(delayed_messages.begin()->DispatchTime > 0)
		)
	{
		// read the message from the front of the queue
		Message message = *delayed_messages.begin();

		// find the recipient
		Object* receiver = MessageCapableObjectManager::GetMessageObjectManager()->GetObjectFromID(message.Receiver);

		// send the telegram to the recipient
		Discharge(receiver, message);

		// and remove it from the queue
		delayed_messages.erase(delayed_messages.begin());
	}
}

MessageDispatcher::MessageDispatcher()
	:delayed_messages()
{
}

void MessageDispatcher::Discharge(Object* receiver, const Message& msg)
{
	MessageCapable* messageCapable = receiver->GetComponentByTemplate<MessageCapable>();
	assert(messageCapable
		&& "Receiver does not have Message Capable Component!");

	// Call the message handle function
	messageCapable->HandleMessage(msg);
}
