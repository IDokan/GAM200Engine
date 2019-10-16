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
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>


const int MAX_SOUND_TRACK = 10;
using  namespace  FMOD;

enum  SOUNDS
{
    JAMJAMTEST_SOUND =0 ,
	DASH_SOUND ,
	COLLISION_SOUND	
};

class SoundManager 
{
public:
    SoundManager();

	void Load_Sound();

	void Play_Sound(SOUNDS sound_name);

	void Stop_Sound(int _chNum);

    void SetVolume(int sound_name, float volume);

	void ERRCHECK(FMOD_RESULT _r, const std::string errorReason);

private:
    FMOD_SYSTEM*		fmod_system;					
    FMOD_SOUND*        sound[MAX_SOUND_TRACK];          
    FMOD_CHANNEL*      ch[MAX_SOUND_TRACK];
	FMOD_RESULT         theResult;
	
};