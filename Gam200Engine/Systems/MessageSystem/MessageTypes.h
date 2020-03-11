/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MessageTypes.h
Author
	- sinil.gang rtd99062@gmail.com
Creation Date: 01.14.2020

	Source file for store message types to use improve code quality
******************************************************************************/
#pragma once

enum class MessageTypes
{
	PlayerIsDead,
	PlayerReachedGoal,
	StringAttached,
	StringDetached,

	/**
	 * \brief
	 * When this message is received, extra information would have how much force do apply on receiver.
	 * For example, Receiver would do like a
	 *		AddForce(ExtraInfo);
	 */
	AddForce,
	
	/**
	 * \brief
	 * When this message is received, extra information would be required as change based on receiver.
	 * For example, Receiver would do like a
	 *		SetTranslation(GetTranslation + ExtraInfo);
	 */
	MoveToRelativePosition,
	/**
	 * \brief
	 * When this message is received, extra information would indicate new position where player would be as a result.
	 * For example, Receiver would do like a
	 *		SetTranslation(ExtraInfo);
	 */
	MoveToAbsolutePosition,
	
	NUM_OF_MESSAGE_TYPES,
};
enum class MessageObjects
{
	Player1,
	Player2,
	
	String_Object,
	Test_Crushable_Object,

	NUM_OF_MESSAGE_OBJECTS,
};

inline constexpr double SendImmediately = 0.0;
