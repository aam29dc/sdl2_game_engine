#pragma once
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "sdlgameobject.hpp"
#include "texturemanager.hpp"

#ifdef DEBUG
	#include <iostream>
#endif

/*
	read a lvl file, load numbers/chars into array,
		each char is assigned a different block in blocks.bmp 0 - 9, a - z, etc
		0 is empty (draw bg), and no collision
		other chars have collision
		lvl is Static ... for now, no need to call update
*/

class Level {
private:
	std::vector<SDLGameObject> _objects;
	size_t _textureID;						//texture is 8x8 grid of 24x24 squares with a margin of 1px, margins are shared between consecutive blocks
public:
	Level();
	~Level();

	//blocks are 24x24,	(33.33.. ~= 34) max each column, 25 max rows = 850 max blocks
	static constexpr int MAX_COL_BLOCKS = 34;
	static constexpr int MAX_ROW_BLOCKS = 25;
	static constexpr int MARGIN = 1;

	bool load(SDL_Renderer* renderer, const std::string& lvl, const std::string& image, const std::string& zmap);
	void draw(SDL_Renderer* renderer, const float& cameraX = 0, const float& cameraY = 0) const;

	const std::vector<SDLGameObject>& getObjects() const;
};

#endif