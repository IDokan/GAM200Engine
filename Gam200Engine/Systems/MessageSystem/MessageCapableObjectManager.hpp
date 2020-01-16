/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MessageCapableObjectManager.h
Author
		sinil.gang
		rtd99062@gmail.com
Creation Date: 01.14.2020

	Header file for Message Capable Object Manager
		It manages message capable object in world
******************************************************************************/
#pragma once
#include <map>
enum class MessageObjects;
class Object;

class MessageCapableObjectManager
{
public:
	static MessageCapableObjectManager* GetMessageObjectManager();

	/*	Example of usage of RegisterEntity()
	When an entity is created it is registered with the entity manager like so:

	// ent_Miner_Bob is declared in "MessageTypes.h"
	Miner* Bob = new Miner(); // enumerated ID
	Bob->AddComponent<MessageCapable>(this, ent_Miner_Bob);
	MsgObjMgr->RegisterEntity(Bob);
	*/

	// this method stores a pointer to the entity in the std::vector
	// m_Entities at the index position indicated by the entity's ID
	// (makes for faster access)
	void RegisterEntity(Object* object);

	/*	Example of usage of GetEntityFromId()
	A client can now request a pointer to a specific entity by passing its ID
	to the method EntityManager::GetEntityFromID in this way:

	// ent_Miner_Bob is declared in "MessageTypes.h"
	Entity* pBob = MsgObjMgr->GetEntityFromID(ent_Miner_Bob);
	*/
	// returns a pointer to the entity with the ID given as a parameter
	Object* GetObjectFromID(MessageObjects id);

	// this method removes the entity from the list
	void RemoveObjectFromList(MessageObjects id);
	
	
private:
	// to save the ol' fingers
	using MessageObjectMap = std::map<MessageObjects, Object*>;

private:
	// to facilitate quick lookup the entites are stored in a std::map,
	// in which pointers to entities are cross-referenced by their identifying number
	MessageObjectMap messageObjectMap;

	MessageCapableObjectManager();

	MessageCapableObjectManager(const MessageCapableObjectManager&) noexcept;
	MessageCapableObjectManager& operator=(const MessageCapableObjectManager&) noexcept;
	MessageCapableObjectManager(MessageCapableObjectManager&&) noexcept;
	MessageCapableObjectManager&& operator=(const MessageCapableObjectManager&&) noexcept;
	
};

// How can I make it works..
//using MsgObjMgr = MessageCapableObjectManager::GetMessageObjectManager();