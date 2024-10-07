#pragma once
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#ifdef DEBUG
	#include <iostream>
#endif

class TextureManager {
private:
	static TextureManager* _instance;
	std::vector<SDL_Texture*> textureMap;
public:
	TextureManager();
	~TextureManager();

	static TextureManager* getInstance();

	bool load(SDL_Renderer* renderer, size_t& id, const std::string& imgFile);
	void draw(SDL_Renderer* renderer, const size_t& id, const SDL_Rect& src, const SDL_FRect& pos, const float& angle = 0.0f) const;
};

#endif