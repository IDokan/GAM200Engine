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
    if (fmod_system == nullptr) {
        theResult = FMOD_System_Create(&fmod_system);
        ERRCHECK(theResult, "System Create");
        theResult = FMOD_System_Init(fmod_system, MAX_SOUND_TRACK, FMOD_INIT_NORMAL, NULL);
        ERRCHECK(theResult, "System Init");
    }

    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/TheFirstBgm.wav", FMOD_LOOP_NORMAL, nullptr, &sound[BACKGROUND_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/Glass_Crush.mp3", FMOD_DEFAULT, nullptr, &sound[CRUSH_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/Goal_Sound.mp3", FMOD_DEFAULT, nullptr, &sound[GOAL_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/CursorMove.mp3", FMOD_DEFAULT, nullptr, &sound[CURSOR_MOVEMENT_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/LevelClearSound.mp3", FMOD_DEFAULT, nullptr, &sound[LEVEL_CLEAR_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/MousePatrolSound.wav", FMOD_DEFAULT, nullptr, &sound[MOUSE_PATROL_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/Select.mp3", FMOD_DEFAULT, nullptr, &sound[SELECT_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/PushableBox.mp3", FMOD_LOOP_NORMAL, nullptr, &sound[PUSHABLE_BOX_SOUND1]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/PushableBox.mp3", FMOD_LOOP_NORMAL, nullptr, &sound[PUSHABLE_BOX_SOUND2]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/ButtonTriggered.mp3", FMOD_DEFAULT, nullptr, &sound[BUTTON_TRIGGERED_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/DOOOOR.mp3", FMOD_DEFAULT, nullptr, &sound[DOOR_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/Undo.mp3", FMOD_DEFAULT, nullptr, &sound[UNDO_SOUND]);
    ERRCHECK(theResult, "Load Sound");

    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/sizeSharing.mp3", FMOD_LOOP_NORMAL, nullptr, &sound[SIZE_SHARE_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/hostageNOTSaved.mp3", FMOD_DEFAULT, nullptr, &sound[NOT_SAVED_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/hostageSaved.mp3", FMOD_DEFAULT, nullptr, &sound[SAVED_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/YumYum.mp3", FMOD_DEFAULT, nullptr, &sound[DIED_BY_MOUSE_SOUND]);
    ERRCHECK(theResult, "Load Sound");

    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/ButtonPressed.mp3", FMOD_DEFAULT, nullptr, &sound[BUTTON_PRESSED_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/CheeseRestored.mp3", FMOD_DEFAULT, nullptr, &sound[CHEESE_RESTORED_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/GoalDoortriggered.mp3", FMOD_DEFAULT, nullptr, &sound[GOAL_DOORTRIGGER_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/JailCrushingSFX.mp3", FMOD_DEFAULT, nullptr, &sound[JAIL_CRUSHING_SOUND]);
    ERRCHECK(theResult, "Load Sound");  
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/RespawnSFX1.mp3", FMOD_DEFAULT, nullptr, &sound[RESPAWN_SOUND1]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/RespawnSFX2.mp3", FMOD_DEFAULT, nullptr, &sound[RESPAWN_SOUND2]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/StruggleSFX.mp3", FMOD_DEFAULT, nullptr, &sound[STRUGGLE_SOUND]);
    ERRCHECK(theResult, "Load Sound");
    theResult = FMOD_System_CreateSound(fmod_system, "../assets/SoundAssets/RefrigeratorTriggered.mp3", FMOD_DEFAULT, nullptr, &sound[REFRIGERATOR_TRIGGERED_SOUND]);
    ERRCHECK(theResult, "Load Sound");

    for (int sound = 0; sound < SOUNDS::NONE; sound++) {
        current_ch_volume[sound] = initialVolume;
    }
}
void SoundManager::UnLoad_Sound()
{
    theResult = FMOD_Sound_Release(sound[BACKGROUND_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[CRUSH_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[GOAL_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[CURSOR_MOVEMENT_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[LEVEL_CLEAR_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[MOUSE_PATROL_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[SELECT_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[PUSHABLE_BOX_SOUND1]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[BUTTON_TRIGGERED_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[DOOR_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[UNDO_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[SIZE_SHARE_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[NOT_SAVED_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[SAVED_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
    theResult = FMOD_Sound_Release(sound[DIED_BY_MOUSE_SOUND]);
    ERRCHECK(theResult, "UnLoad Sound");
}

void SoundManager::Play_Sound(SOUNDS sound_name)
{

    FMOD_System_Update(fmod_system);
    theResult = FMOD_System_PlaySound(fmod_system, sound[sound_name], nullptr, false, &ch[sound_name]);
    ERRCHECK(theResult, "Play Sound");
}

void SoundManager::Stop_Sound(int _chNum)
{
    if (ch[_chNum] != nullptr) {
        theResult = FMOD_Channel_Stop(ch[_chNum]);
        ERRCHECK(theResult, "Stop Sound");
    }
}

//The volume bound is between 0 ~ 1 
void SoundManager::SetVolume(int sound_name, float volume)
{
    if (ch[sound_name] != nullptr) {
        current_ch_volume[sound_name] = volume;

        theResult = FMOD_Channel_SetVolume(ch[sound_name], volume);
        ERRCHECK(theResult, "Set Volume");
    }
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

void SoundManager::SetVolumeOnMenu()
{
    if (ch[SOUNDS::BACKGROUND_SOUND] != nullptr) {
        theResult = FMOD_Channel_SetVolume(ch[SOUNDS::BACKGROUND_SOUND], GetCurrentChVolume(BACKGROUND_SOUND) / 4);
        ERRCHECK(theResult, "Set Volume On Menu");
    }
}

void SoundManager::SetVolumeOnGameRunning()
{
    if (ch[SOUNDS::BACKGROUND_SOUND] != nullptr) {
        theResult = FMOD_Channel_SetVolume(ch[SOUNDS::BACKGROUND_SOUND], GetCurrentChVolume(BACKGROUND_SOUND));
        ERRCHECK(theResult, "Set Volume On Game Running");
    }
}


void SoundManager::MASTER_VOLUME_DOWN()
{
    float newVolume = 0.f;
    float checkVolumeSize = (GetCurrentChVolume(0) * contorolVolumeSize);

    if (static_cast<int>(GetCurrentChVolume(0) * 100) > static_cast<int>(checkVolumeSize * 100)) {
        for (int currentSound = 0; currentSound < SOUNDS::NONE; currentSound++) {
            if (ch[currentSound] != nullptr) {
                newVolume = GetCurrentChVolume(currentSound);
                newVolume -= newVolume * contorolVolumeSize;

                if (newVolume > initialVolume) {
                    current_ch_volume[currentSound] = newVolume;
                    theResult = FMOD_Channel_SetVolume(ch[currentSound], newVolume);
                    ERRCHECK(theResult, "MasterVolume Error");
                }
            }
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
            if (ch[currentSound] != nullptr) {
                newVolume = GetCurrentChVolume(currentSound);
                newVolume += newVolume * contorolVolumeSize;

                current_ch_volume[currentSound] = newVolume;
                theResult = FMOD_Channel_SetVolume(ch[currentSound], newVolume);
                ERRCHECK(theResult, "MasterVolume Error");
            }
        }
    }
}
