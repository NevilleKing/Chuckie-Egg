#include "Audio.h"

bool Audio::_isInit = false;
Mix_Music* Audio::_music;
std::map<std::string, std::unique_ptr<Mix_Chunk>> Audio::_sfx;

void Audio::init_Error()
{
	char error[] = "Audio not Initialised. Call Audio::init() first";
	SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
}

bool Audio::init()
{

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("OpenAudio Failed : ") + Mix_GetError()));
		return false;
	}

	_isInit = true;

	return true;

}

bool Audio::Load_Music(std::string path)
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	_music = Mix_LoadMUS(path.c_str());
	if (_music == nullptr)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("Loading Music Failed : ") + Mix_GetError()));
		return false;
	}

	return true;
}

bool Audio::Load_SFX(std::string path, std::string label)
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	// check if the label already exists
	if (_sfx.find(label) != _sfx.end())
	{
		char error[] = "Loading SFX Failed: SFX Label Already Exists";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	auto newSFX = Mix_LoadWAV("./assets/sfx1.wav");
	if (newSFX == nullptr)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("Loading SFX Failed : ") + Mix_GetError()));
		return false;
	}

	_sfx[label] = std::unique_ptr<Mix_Chunk>(newSFX);

	return true;
}

void Audio::Free_Memory()
{
	if (_music != nullptr) Mix_FreeMusic(_music);
}

bool Audio::Start_Music()
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	if (_music == nullptr)
	{
		char error[] = "Playing Music Failed: Music not Loaded";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	Mix_PlayMusic(_music, -1);

	return true;
}

bool Audio::Pause_Music()
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	if (_music == nullptr)
	{
		char error[] = "Pausing Music Failed: Music not Loaded";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	Mix_PauseMusic();

	return true;
}

bool Audio::Resume_Music()
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	if (_music == nullptr)
	{
		char error[] = "Pausing Music Failed: Music not Loaded";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	Mix_ResumeMusic();

	return true;
}

// Plays the music if it is stopped or paused, pauses the music if it is playing
// returns true if music is now playing, false if it is not
bool Audio::Pause_Play_Music()
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	if (_music == nullptr)
	{
		char error[] = "Pausing Music Failed: Music not Loaded";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	if (Mix_PlayingMusic())
	{
		if (Mix_PausedMusic() == 0)
		{
			Mix_PauseMusic();
			return false;
		}
		else
		{
			Mix_ResumeMusic();
			return true;
		}
	}
	else
	{
		Mix_PlayMusic(_music, -1);
		return true;
	}
}

bool Audio::Stop_Music()
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	if (_music == nullptr)
	{
		char error[] = "Pausing Music Failed: Music not Loaded";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	Mix_HaltMusic();

	return true;
}

bool Audio::Play_SFX(std::string label)
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	// check if the label doesn't exist
	if (_sfx.find(label) == _sfx.end())
	{
		char error[] = "Playing SFX Failed: SFX Doesn't Exist";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	Mix_PlayChannel(-1, &(*_sfx[label]), 0);

	return true;
}