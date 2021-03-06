/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
        dbsqhd106@gmail.com
Creation Date: 12.OCT.2019

    Header file for the Application.cpp
******************************************************************************/
#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>

const int MAX_SOUND_TRACK = 35;
using  namespace  FMOD;

//!!!USAGE OF SETVOLUME!!!//(It must be after the Play_Sound function.)
// Load_Sound
// Play_Sound
// SetVolume


//The orders are important to set up the Play_Sound function.
enum  SOUNDS
{
    BACKGROUND_SOUND = 0,
    BACKGROUND_SOUND2,
    CREADIT_BGM,
    HOWTOPLAY_MAIN_BGM,


    CRUSH_SOUND,
    GOAL_SOUND,
    CURSOR_MOVEMENT_SOUND,
    LEVEL_CLEAR_SOUND,
    MOUSE_PATROL_SOUND,
    SELECT_SOUND,
    PUSHABLE_BOX_SOUND1,
    PUSHABLE_BOX_SOUND2,
    BUTTON_TRIGGERED_SOUND,
    DOOR_SOUND,
    UNDO_SOUND,

    SIZE_SHARE_SOUND,
    NOT_SAVED_SOUND,
    SAVED_SOUND,
    DIED_BY_MOUSE_SOUND,

    BUTTON_PRESSED_SOUND,
    CHEESE_RESTORED_SOUND,
    GOAL_DOORTRIGGER_SOUND,
    JAIL_CRUSHING_SOUND,
    RESPAWN_SOUND1,
    RESPAWN_SOUND2,
    STRUGGLE_SOUND,
    STRUGGLE_SOUND2,
    REFRIGERATOR_TRIGGERED_SOUND,


    NONE
};

class SoundManager
{
public:
    void Load_Sound();

    void UnLoad_Sound();

    void Play_Sound(SOUNDS sound_name);

    void Stop_Sound(int _chNum);

    void SetVolume(int sound_name, float volume);

    void ERRCHECK(FMOD_RESULT _r, const std::string errorReason);

    float GetCurrentChVolume(int sound_name);

    void MASTER_VOLUME_DOWN();

    void MASTER_VOLUME_UP();

    void SetVolumeOnMenu();

    void SetVolumeOnGameRunning();

    void StopCurrentBGM();


private:
    FMOD_SYSTEM* fmod_system;
    FMOD_SOUND* sound[MAX_SOUND_TRACK];
    FMOD_CHANNEL* ch[MAX_SOUND_TRACK];
    FMOD_RESULT         theResult;
    float current_ch_volume[MAX_SOUND_TRACK];
    float initialVolume = 0.1f;
    float contorolVolumeSize = 0.5f;

};