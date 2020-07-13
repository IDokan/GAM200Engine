/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MessageCapableObjectManager.cpp
Author
		sinil.gang
		rtd99062@gmail.com
Creation Date: 01.16.2020

	Source file for Message Capable Object Manager
		It manages message capable object in world
******************************************************************************/

#include <Systems/MessageSystem/MessageCapableObjectManager.hpp>
#include <Object/Object.hpp>
#include <Component/MessageCapable.hpp>

MessageCapableObjectManager* MessageCapableObjectManager::GetMessageObjectManager()
{
	static MessageCapableObjectManager* messageCapableObjectManager = new MessageCapableObjectManager();
	return messageCapableObjectManager;
}

void MessageCapableObjectManager::RegisterEntity(Object* object)
{
	MessageCapable* messageCapable = object->GetComponentByTemplate<MessageCapable>();
	messageObjectMap[messageCapable->GetMessageObjectType()] = object;
}

void MessageCapableObjectManager::RegisterEntity(Object* object, MessageObjects id)
{
	messageObjectMap[id] = object;
}

Object* MessageCapableObjectManager::GetObjectFromID(MessageObjects id)
{
	Object* returnValue;
	try
	{
		returnValue = messageObjectMap.at(id);
	}
	catch (const std::exception&)
	{
		returnValue = nullptr;
	}
	return returnValue;
}

void MessageCapableObjectManager::RemoveObjectFromList(MessageObjects id)
{
	messageObjectMap.erase(id);
}
