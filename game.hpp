#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include "input.hpp"
#include "font.hpp"
#include "window.hpp"
#include "time.hpp"

#include "gamestatemachine.hpp"
#include "menustate.hpp"

#ifdef DEBUG
	#include <iostream>
#endif

class Game {
private:
	static Game* _instance;
	GameStateMachine* _GSM;
	bool _quit;
public:
	Game();
	~Game();
	static Game* getInstance();

	GameStateMachine* getGSM();

	bool init();					// this calls window init, which creates the renderer
	void handleEvents();
	void update();
	void render(SDL_Renderer* renderer) const;
};

#endif