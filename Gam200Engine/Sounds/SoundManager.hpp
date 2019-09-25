#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

using namespace FMOD;
const int MAX_SOUND_TRACK = 10;

enum  SOUNDS
{
	BACKGROUND_SOUND = 0,
	MENU_SOUND	
};

class SoundManager
{
public:
	static SoundManager* GetSoundManager();
	
	static SoundManager* Instance;

	void init();

	void Loading_Music();

	void Play_Music(int _type);

	void Stop_Music(int _chNum);

	void ErrorCheck(FMOD_RESULT _r);

private:
	System*		system;
	Sound*		music[MAX_SOUND_TRACK];
	Channel*	ch[MAX_SOUND_TRACK];
	FMOD_RESULT theResult;
};