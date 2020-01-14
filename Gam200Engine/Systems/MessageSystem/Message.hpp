/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Message.hpp
Author
	- sinil.gang rtd99062@gmail.com
Creation Date: 01.14.2020

	Source file for message that going to use to dispatch by sender
										and going to use to received by recipient
******************************************************************************/
#pragma once

enum class MessageObjects;
enum class MessageTypes;

struct Message
{
	Message(MessageObjects  Sender, MessageObjects  Receiver, MessageTypes Msg, double DispatchTime = 0.0, void* ExtraInfo = nullptr)
		: Sender(Sender), Receiver(Receiver), Msg(Msg), DispatchTime(DispatchTime), ExtraInfo(ExtraInfo)
	{}
	
	// the entity that sent this message
	MessageObjects Sender;

	// the entity that is to receive this telegram
	MessageObjects Receiver;

	// the message itself. These are all enumerated in the file
	// "MessageTypes.h"
	MessageTypes Msg;

	// messages can be dispatched immediately or delayed for a specified amount of time.
	// If a delay is necessary, this field is stamped with the time the message should be dispatched.
	double DispatchTime;

	// any additional information that may accompany the message
	void* ExtraInfo;
};