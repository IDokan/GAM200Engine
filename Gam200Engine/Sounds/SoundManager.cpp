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
#include  "SoundManager.hpp"
#include <Scenes/SceneManager.hpp>


void SoundManager::Load_Sound()
{
    theResult = FMOD_System_Create(&fmod_system);
    ERRCHECK(theResult, "System Create");
    theResult = FMOD_System_Init(fmod_system, MAX_SOUND_TRACK, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(theResult, "System Init");

    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/TheFirstBgm.wav", FMOD_LOOP_NORMAL, nullptr, &sound[BACKGROUND_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/Glass_Crush.mp3", FMOD_DEFAULT, nullptr, &sound[CRUSH_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/Goal_Sound.mp3", FMOD_DEFAULT, nullptr, &sound[GOAL_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/CursorMove.ogg", FMOD_DEFAULT, nullptr, &sound[CURSOR_MOVEMENT_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/LevelClearSound.wav", FMOD_DEFAULT, nullptr, &sound[LEVEL_CLEAR_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/MousePatrolSound.wav", FMOD_DEFAULT, nullptr, &sound[MOUSE_PATROL_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/Select.ogg", FMOD_DEFAULT, nullptr, &sound[SELECT_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/PushableBox.ogg", FMOD_LOOP_NORMAL, nullptr, &sound[PUSHABLE_BOX_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/ButtonTriggered.ogg", FMOD_DEFAULT, nullptr, &sound[BUTTON_TRIGGERED_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/doorOpen.mp3", FMOD_DEFAULT, nullptr, &sound[DOOR_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/Undo.ogg", FMOD_DEFAULT, nullptr, &sound[UNDO_SOUND]);
    ERRCHECK(theResult, "Load Sound");

    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/sizeSharing.mp3", FMOD_LOOP_NORMAL, nullptr, &sound[SIZE_SHARE_SOUND]);
    ERRCHECK(theResult, "Load Sound");    
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/hostageNOTSaved.mp3", FMOD_DEFAULT, nullptr, &sound[NOT_SAVED_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/hostageSaved.ogg", FMOD_DEFAULT, nullptr, &sound[SAVED_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/mouseGotCheese.wav", FMOD_DEFAULT, nullptr, &sound[DIED_BY_MOUSE_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    for (int sound = 0; sound < SOUNDS::NONE; sound++) {
        current_ch_volume[sound] = initialVolume;
    }
}

void SoundManager::Play_Sound(SOUNDS sound_name)
{
    FMOD_System_Update(fmod_system);
    theResult = FMOD_System_PlaySound(fmod_system, sound[sound_name], nullptr, false, &ch[sound_name]);
    ERRCHECK(theResult, "Play Sound");
}

void SoundManager::Stop_Sound(int _chNum)
{
    theResult = FMOD_Channel_Stop(ch[_chNum]);
    ERRCHECK(theResult, "Stop Sound");
}

//The volume bound is between 0 ~ 1 
void SoundManager::SetVolume(int sound_name, float volume)
{
    //masterVolume = volume;
    current_ch_volume[sound_name] = volume;
    theResult = FMOD_Channel_SetVolume(ch[sound_name], volume);
    ERRCHECK(theResult, "Set Volume");
}

void SoundManager::ERRCHECK(FMOD_RESULT _theResult, const std::string errorReason)
{
    if (_theResult != FMOD_OK)
    {
        std::cout << errorReason << " Error!\n";
    }
}

float SoundManager::GetCurrentChVolume(int sound_name)
{
    return current_ch_volume[sound_name];
}

void SoundManager::MASTER_VOLUME_DOWN()
{
    float newVolume = 0.f;
    float checkVolumeSize = (GetCurrentChVolume(0) * contorolVolumeSize);

    if (static_cast<int>(GetCurrentChVolume(0) * 100) > static_cast<int>(checkVolumeSize * 100)) {
        for (int currentSound = 0; currentSound < SOUNDS::NONE; currentSound++) {
            newVolume = GetCurrentChVolume(currentSound);
            newVolume -= newVolume * contorolVolumeSize;

            current_ch_volume[currentSound] = newVolume;
            FMOD_Channel_SetVolume(ch[currentSound], newVolume);
        }
    }
}


void SoundManager::MASTER_VOLUME_UP()
{
    float newVolume = 0;
    float checkVolumeSize = (GetCurrentChVolume(0) * contorolVolumeSize);

    if (GetCurrentChVolume(0) + checkVolumeSize < 1.0f)
    {
        for (int currentSound = 0; currentSound < SOUNDS::NONE; currentSound++) {
            newVolume = GetCurrentChVolume(currentSound);
            newVolume += newVolume * contorolVolumeSize;

            current_ch_volume[currentSound] = newVolume;
            FMOD_Channel_SetVolume(ch[currentSound], newVolume);
        }
    }
}
