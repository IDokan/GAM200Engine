/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MessageCapable.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 11.16.2019

	Header file for Message Capable class
		This is need to be added to objects
			if the objects want to send or receive messages.
******************************************************************************/
#include <Component/MessageCapable.hpp>
#include <utility>

MessageCapable::MessageCapable(Object* obj, MessageObjects objType,
	std::function<bool(const Message& msg)> handleMsgFunc)
	: Component(obj), handleMessageFunc(std::move(handleMsgFunc)), objectType(objType)
{
}

void MessageCapable::Init()
{
}

void MessageCapable::Update(float /*dt*/)
{
}

void MessageCapable::Clear()
{
}

bool MessageCapable::HandleMessage(const Message& msg)
{
	return handleMessageFunc(msg);
}

void MessageCapable::ChangeHandleMessageFunc(std::function<bool(const Message& msg)> handleMsgFunc)
{
	handleMessageFunc = std::move(handleMsgFunc);
}

MessageObjects MessageCapable::GetMessageObjectType()
{
	return objectType;
}

void MessageCapable::SetMessageObjectType(MessageObjects objType)
{
	objectType = objType;
}
