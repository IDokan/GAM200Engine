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
     * When this message is received, extra information would have how many force do apply on receiver.
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

       /**
  * \brief
  * When the player collide with key, then key dissappear and send lock the message to dissappear.
  */
       GetKey,

	   /**
		* \brief
		* When this message is received, no extra information may be supplied.
		*		If message sent to SceneStateManager, receiver will change its state into PlayerIsDead State.
		*/
	   PlayerIsDead,

	   /**
		* \brief
		* When this message is received, no extra information may be supplied.
		*		If message sent to SceneStateManager which is current scene is PlayerIsDead, receiver will change its state into GameIsRunning State.
		*/
	   GameRestarted,

	   /**
		* \brief
		* When this message is received, no extra information may be supplied.
		*		If message sent to SceneStateManager, receiver will change its state into SceneComplete State.
		*/
	   SceneComplete,

       NUM_OF_MESSAGE_TYPES,
};


// In Message Objects, if you have any issue about it.
// Look up in Object::ObjectType
enum class MessageObjects
{
    Player1,
    Player2,

    //for key&lock system
    Key1,
    Key2,
    Lock1,
    Lock2,

    String_Object,
    Test_Crushable_Object,

	SceneStateManager,

    NUM_OF_MESSAGE_OBJECTS,
};

inline constexpr double SendImmediately = 0.0;
