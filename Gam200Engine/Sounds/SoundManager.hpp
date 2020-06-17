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

const int MAX_SOUND_TRACK = 30;
using  namespace  FMOD;

//!!!USAGE OF SETVOLUME!!!//(It must be after the Play_Sound function.)
// Load_Sound
// Play_Sound
// SetVolume


//The orders are important to set up the Play_Sound function.
enum  SOUNDS
{
    BACKGROUND_SOUND=0,
    CRUSH_SOUND,
    GOAL_SOUND,
    CURSOR_MOVEMENT_SOUND,
    LEVEL_CLEAR_SOUND,
    MOUSE_PATROL_SOUND,
    SELECT_SOUND,
    PUSHABLE_BOX_SOUND,
    BUTTON_TRIGGERED_SOUND,
    DOOR_SOUND,
    UNDO_SOUND,

    SIZE_SHARE_SOUND,
    NOT_SAVED_SOUND,
    SAVED_SOUND,
    DIED_BY_MOUSE_SOUND,
    NONE
};

class SoundManager
{
public:
    void Load_Sound();

    void Play_Sound(SOUNDS sound_name);

    void Stop_Sound(int _chNum);

    void SetVolume(int sound_name, float volume);

    void ERRCHECK(FMOD_RESULT _r, const std::string errorReason);

    float GetCurrentChVolume(int sound_name);

    void MASTER_VOLUME_DOWN();

    void MASTER_VOLUME_UP();

    void SetVolumeOnMenu();

    void SetVolumeOnGameRunning();


private:
    FMOD_SYSTEM* fmod_system;
    FMOD_SOUND* sound[MAX_SOUND_TRACK];
    FMOD_CHANNEL* ch[MAX_SOUND_TRACK];
    FMOD_RESULT         theResult;
    float current_ch_volume[MAX_SOUND_TRACK];
    float initialVolume = 0.2f;
    float contorolVolumeSize = 0.2f;

};