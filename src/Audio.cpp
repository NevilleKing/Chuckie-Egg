#include "Audio.h"

// static variables
bool Audio::_isInit = false;
Mix_Music* Audio::_music;
std::map<std::string, Mix_Chunk*> Audio::_sfx;

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

	// delete music if it already exists
	if (_music != nullptr)
		Mix_FreeMusic(_music);

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

	auto newSFX = Mix_LoadWAV(path.c_str());
	if (newSFX == nullptr)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("Loading SFX Failed : ") + Mix_GetError()));
		return false;
	}

	_sfx[label] = newSFX;

	return true;
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

int Audio::Play_SFX(std::string label)
{
	if (!_isInit)
	{
		init_Error();
		return -1;
	}

	// check if the label doesn't exist
	if (_sfx.find(label) == _sfx.end())
	{
		char error[] = "Playing SFX Failed: SFX Doesn't Exist";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return -1;
	}

	return Mix_PlayChannel(-1, _sfx[label], 0);
}

int Audio::Play_SFX_Looping(std::string label, int loops)
{
	if (!_isInit)
	{
		init_Error();
		return -1;
	}

	if (loops < -1)
		return -1;

	// check if the label doesn't exist
	if (_sfx.find(label) == _sfx.end())
	{
		char error[] = "Playing SFX Failed: SFX Doesn't Exist";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return -1;
	}

	return Mix_PlayChannel(-1, _sfx[label], loops);
}

bool Audio::Pause_SFX(int channel)
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	Mix_Pause(channel);

	return true;
}

bool Audio::Resume_SFX(int channel)
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	Mix_Resume(channel);

	return true;
}

bool Audio::Set_SFX_Volume(int volume, std::string label)
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

	Mix_VolumeChunk(_sfx[label], volume);

	return true;
}

int Audio::Fade_In_SFX(std::string label, float seconds)
{
	if (!_isInit)
	{
		init_Error();
		return -1;
	}

	// check if the label doesn't exist
	if (_sfx.find(label) == _sfx.end())
	{
		char error[] = "Setting Volume of SFX Failed: SFX Doesn't Exist";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return -1;
	}

	return Mix_FadeInChannel(-1, _sfx[label], 0, seconds * 1000);
}

int Audio::Fade_In_SFX_And_Loop(std::string label, float seconds, int loops)
{
	if (!_isInit)
	{
		init_Error();
		return -1;
	}

	// check if the label doesn't exist
	if (_sfx.find(label) == _sfx.end())
	{
		char error[] = "Setting Volume of SFX Failed: SFX Doesn't Exist";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return -1;
	}

	return Mix_FadeInChannel(-1, _sfx[label], loops, seconds * 1000);
}

bool Audio::Fade_Out_SFX(int channel, float seconds)
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	// check if the channel is playing
	if (!Mix_Playing(channel))
	{
		char error[] = "Stopping SFX Failed: Channel isn't playing";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	Mix_FadeOutChannel(channel, seconds * 1000);

	return true;
}

bool Audio::Set_SFX_Panning(int channel, int left, int right)
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	// check if the channel is playing
	if (!Mix_Playing(channel))
	{
		char error[] = "Setting SFX Panning: Channel isn't playing";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	Mix_SetPanning(channel, left, right);

	return true;
}

bool Audio::Set_SFX_Panning_Based_On_Position(int channel, Vector position, float winwidth)
{
	int right = (position.x / winwidth) * 254.0f;

	if (position.x < 0)
		right = 0;
	else if (position.x > winwidth)
		right = 254;

	return Set_SFX_Panning(channel, 254 - right, right);
}

bool Audio::Stop_SFX(int channel)
{
	if (!_isInit)
	{
		init_Error();
		return false;
	}

	// check if the channel is playing
	if (!Mix_Playing(channel))
	{
		char error[] = "Stopping SFX: Channel isn't playing";
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, error);
		return false;
	}

	Mix_HaltChannel(channel);

	return true;
}
