#pragma once
#ifndef GAMESTATEMACHINE_HPP
#define GAMESTATEMACHINE_HPP

#include "gamestate.hpp"
#include <vector>

struct SDL_Renderer;

class GameStateMachine {
public:
	void update();
	void render(SDL_Renderer* renderer) const;

	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();
private:
	std::vector<GameState*> _gameStates;
};

#endif