#pragma once
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>

struct SDL_Renderer;

class GameState {
public:
	virtual void update() = 0;
	virtual void render(SDL_Renderer* renderer) const = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual const std::string& getStateID() const = 0;
};

#endif