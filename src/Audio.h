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
	static bool Play_SFX(std::string label);
private:
	static bool _isInit;
	static Mix_Music* _music;
	static std::map<std::string, Mix_Chunk*> _sfx;
};

