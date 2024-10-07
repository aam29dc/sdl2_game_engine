#pragma once
#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "gamestate.hpp"
#include "font.hpp"
#include "input.hpp"

#include "game.hpp"

class PauseState : public GameState {
public:
	void update();
	void render(SDL_Renderer* renderer) const;
	bool onEnter();
	bool onExit();
	const std::string& getStateID() const;
private:
	static const std::string _ID;
};

#endif