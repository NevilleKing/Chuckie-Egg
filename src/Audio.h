#pragma once

#include <map>
#include <memory>
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Audio
{
public:
	static void init_Error();
	static bool init();
	static bool Load_Music(std::string path);
	static bool Load_SFX(std::string path, std::string label);
	static void Free_Memory();
	static bool Start_Music();
	static bool Pause_Music();
	static bool Resume_Music();
	static bool Pause_Play_Music();
	static bool Stop_Music();
	static bool Play_SFX(std::string label);
private:
	static bool _isInit;
	static Mix_Music *_music;
	static std::map<std::string, std::unique_ptr<Mix_Chunk>> _sfx;
};

