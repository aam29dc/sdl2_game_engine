#include "soundmanager.hpp"

SoundManager* SoundManager::_instance = nullptr;

SoundManager::SoundManager() {
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
		#ifdef DEBUG
			std::cout << "Could not init mixer:  " << Mix_GetError() << std::endl;
		#endif
	}
	Mix_Volume(-1, 32);
}

SoundManager::~SoundManager() {
	Mix_CloseAudio();
}

SoundManager* SoundManager::getInstance() {
	if (_instance == nullptr) {
		_instance = new SoundManager();
	}
	return _instance;
}

bool SoundManager::load(const std::string fileName, const std::string id, const sound_type type) {
	if (type == SOUND_MUSIC) {
		Mix_Music* Music = Mix_LoadMUS(fileName.c_str());
		if (Music == 0) {
			#ifdef DEBUG
				std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			#endif
			return false;
		}
		_music[id] = Music;
		return true;
	}
	else if (type == SOUND_SFX) {
		Mix_Chunk* Chunk = Mix_LoadWAV(fileName.c_str());
		if (Chunk == 0) {
			#ifdef DEBUG
				std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			#endif
		}
		_sfxs[id] = Chunk;

		return true;
	}
	return false;
}

void SoundManager::playSound(const std::string id, const int loop) {
	Mix_PlayChannel(-1, _sfxs[id], loop);
}

void SoundManager::playMusic(const std::string id, const int loop) {
	Mix_PlayMusic(_music[id], loop);
}