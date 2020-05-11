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
    /**
     * \brief
     * @extraInfo:
     *		no extraInfo
     *
     * @Predictable receiver and function
     *		SceneStateManager: Save which player is in goal position.
                                            Change its state into SceneComplete state, if both players are in goal position.
     */
    PlayerReachedGoal,


    /**
     * \brief
     * @extraInfo:
     *		no extraInfo
     *
     * @Predictable receiver and function
     *		SceneStateManager: Save which player is not in goal position.
     */
    PlayerExitedFromGoal,

    StringAttached,
    StringDetached,

    /**
     * \brief
     * When this message is received, extra information would have how many force do apply on receiver.
     * For example, Receiver would do like a
     *		AddForce(ExtraInfo);
     */
     AddStringForce,

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
        * When this message is received, extra information would be a length of current string.
        *
		* @Predictable receiver and function
		*		StringLengthUI: receiver will do an appropriate calculation. Let them know about current state of string.
        */
        StringIsStreching,

       /**
  * \brief
  * When the player collide with key, then key dissappear and send lock the message to dissappear.
  */
       GetKey,

	   /**
		* \brief
		* When this message is received, no extra information may be supplied.
		*
		* @Predictable receiver and function
		*		SceneStateManager: receiver will change its state into PlayerIsDead State.
		*		Players: receiver will change its state into Dead State.
		*/
	   PlayerIsDead,

	   /**
		* \brief
		* When this message is received, no extra information may be supplied.
		* 
		* @Predictable receiver and function
		*		SceneStateManager: receiver will change its state into PlayerIsDead State.
		*		Players: receiver will change its state into (Idle or LevelStart) State.
		*/
	   GameRestarted,

       /**
        * \brief
        * @extraInfo:
        *		string value of next Level.
        *
        *
        * @Predictable receiver and function
        *		Players: receiver will change its state into SceneComplete State.
        */
        SceneComplete,

        /**
         * \brief
         * @Predictable receiver and function
         *		SceneStateManager: receiver will turn on isHostageRescused.
         */
         HostageRescued,

        /**
         * \brief
         * @Predictable receiver and function
         *		HostageAlertsUI: receiver will update their position.
         */
        HostageNotRescuedYet,

        /**
         * \brief
         * @Predictable receiver and function
         *		Player: player will change their state into Pause State
         */
        Pause,

        /**
         * \brief
         * @Predictable receiver and function
         *		Player: player will change their state into Idle State
         */
        Resume,

       NUM_OF_MESSAGE_TYPES,
};


// In Message Objects, if you have any issue about it.
// Look up in Object::ObjectType
enum class MessageObjects
{
    Player1,
    Player2,

    // Hostage who is a little cheese in jail
    // In some what perspective, it might be a goal of each round
    Hostage,

    //for key&lock system
    Key1,
    Key2,
    Lock1,
    Lock2,

    String_Object,
    Test_Crushable_Object,

	SceneStateManager,

    // Object type for StringLengthUI
    StringLengthUI,
    // Object type for HostageAlertsUI
    HostageAlertsUI,

    // Mouse Object! This is a main enemy of player..
    Mouse,

    NUM_OF_MESSAGE_OBJECTS,
};

inline constexpr double SendImmediately = 0.0;
