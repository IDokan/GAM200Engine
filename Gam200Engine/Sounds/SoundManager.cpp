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

SoundManager::SoundManager()
{
	theResult = FMOD_System_Create(&fmod_system);
	ERRCHECK(theResult, "System Create");
	theResult = FMOD_System_Init(fmod_system, MAX_SOUND_TRACK, FMOD_INIT_NORMAL, NULL);
	ERRCHECK(theResult, "System Init");
}

void SoundManager::Load_Sound()
{
	theResult = FMOD_System_CreateSound(fmod_system, "SoundAssets/bgm.mp3", FMOD_LOOP_NORMAL, nullptr, &sound[JAMJAMTEST_SOUND]);//fmod_system->createSound("SoundAssets/jamjam.mp3", FMOD_DEFAULT, nullptr, &sound[JAMJAMTEST_SOUND]);//Guess...we can know what kinds of sound it is by the last parameter
	ERRCHECK(theResult, "Load Sound");
	theResult = FMOD_System_CreateSound(fmod_system, "SoundAssets/dash.mp3", FMOD_DEFAULT, nullptr, &sound[DASH_SOUND]);//fmod_system->createSound("SoundAssets/jamjam.mp3", FMOD_DEFAULT, nullptr, &sound[JAMJAMTEST_SOUND]);//Guess...we can know what kinds of sound it is by the last parameter
	ERRCHECK(theResult, "Load Sound");
	theResult = FMOD_System_CreateSound(fmod_system, "SoundAssets/collision.mp3", FMOD_DEFAULT, nullptr, &sound[COLLISION_SOUND]);//fmod_system->createSound("SoundAssets/jamjam.mp3", FMOD_DEFAULT, nullptr, &sound[JAMJAMTEST_SOUND]);//Guess...we can know what kinds of sound it is by the last parameter
	ERRCHECK(theResult, "Load Sound");
}

void SoundManager::Play_Sound(SOUNDS sound_name)
{
	FMOD_System_Update(fmod_system);
	theResult = FMOD_System_PlaySound(fmod_system, sound[sound_name], nullptr, false, &ch[sound_name]); //fmod_system->playSound(sound[sound_name], nullptr, false, &ch[sound_name]);
	ERRCHECK(theResult, "Play Sound");
}

void SoundManager::Stop_Sound(int _chNum)
{
	FMOD_Channel_Stop(ch[_chNum]);
}

//The volume bound is between 0 ~ 1 
void SoundManager::SetVolume(int sound_name, float volume)
{
	theResult = FMOD_Channel_SetVolume(ch[sound_name], volume);   /* ERRCHECK(theResult,"Set Volume");*/
	ERRCHECK(theResult, "Set Volume");
}

void SoundManager::ERRCHECK(FMOD_RESULT _theResult, const std::string errorReason)
{
	if (_theResult != FMOD_OK)
	{
		std::cout << errorReason << " Error!\n";
	}
}


