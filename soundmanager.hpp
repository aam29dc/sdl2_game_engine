#pragma once
#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SDL_mixer.h>

#include <string>
#include <map>

#ifdef DEBUG
	#include <iostream>
#endif

enum sound_type {
	SOUND_MUSIC = 0,
	SOUND_SFX = 1,
};

class SoundManager {
public:
	static SoundManager* getInstance();
	bool load(const std::string fileName, const std::string id, const sound_type type);
	void playSound(const std::string id, const int loop = false);
	void playMusic(const std::string id, const int loop = false);
private:
	static SoundManager* _instance;

	std::map<std::string, Mix_Chunk*> _sfxs;
	std::map<std::string, Mix_Music*> _music;

	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&) {}
	SoundManager& operator=(const SoundManager&) {}
};

#endif