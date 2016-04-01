#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <memory>
#include <string>

class Audio
{
public:
	static void init_Error();
	static bool init();
	static bool Load_Music(std::string path);
	static bool Load_SFX(std::string path, std::string label);
	static bool Start_Music();
	static bool Pause_Music();
	static bool Resume_Music();
	static bool Pause_Play_Music();
	static bool Stop_Music();
	static int Play_SFX(std::string label);
	static bool Set_SFX_Volume(int volume, std::string label);
	static int Fade_In_SFX(std::string label, float seconds);
	static bool Fade_Out_SFX(int channel, float seconds);
private:
	static bool _isInit;
	static Mix_Music* _music;
	static std::map<std::string, Mix_Chunk*> _sfx;
};

