/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MessageDispatcher.hpp
Author
		sinil.gang
		rtd99062@gmail.com
Creation Date: 01.14.2020

	Header file for Message Dispatcher
		It manages dispatching message
******************************************************************************/
#pragma once

#include <set>

class Message;
class Object;

class MessageDispatcher
{
public:
	static MessageDispatcher* GetDispatcher();

	void DispatchMessage(
		int sender,
		int receiver,
		int msg,
		double delay = 0.0,
		void* ExtraInfo = nullptr
	);

	// Send out any delayed messages.
	// This method is called each time through the main game loop.
	void DispatchDelayedMessages();
	
private:
	MessageDispatcher();

	// a std::set is used as the container for the delayed messages
	// because of the benefit of automatic sorting and avoidance of duplicates.
	// Messages are sorted by their dispatch time.
	std::set<Message> delayed_Messages;

	// This method is utilized by DispatchMessage or DispatchDelayedMessages.
	// This method calls the message handling member function of
	// the receiving entity, receiver, with the newly created telegram
	void Discharge(Object* receiver, const Message& msg);
};