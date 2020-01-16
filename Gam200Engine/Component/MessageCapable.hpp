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

#pragma once
#include <Component/Component.hpp>
#include <functional>
#include <Systems/MessageSystem/MessageTypes.h>

struct Message;

class MessageCapable : public Component
{
public:
	MessageCapable(Object* obj, MessageObjects objType, std::function<bool(const Message& msg)> handleMsgFunc = [](const Message&) {return false; });

	void Init() override;
	void Update(float dt) override;
	void Clear() override;
	
	bool HandleMessage(const Message& msg);
	void ChangeHandleMessageFunc(std::function<bool(const Message& msg)> handleMsgFunc);

	MessageObjects GetMessageObjectType();
	void SetMessageObjectType(MessageObjects objType);

private:
	std::function<bool(const Message& msg)> handleMessageFunc;
	MessageObjects objectType;
};