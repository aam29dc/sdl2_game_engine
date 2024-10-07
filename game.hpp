#pragma once
#ifndef GAME_H
#define GAME_H

#include "input.hpp"
#include "font.hpp"
#include "window.hpp"
#include "time.hpp"
#include "gameoverstate.hpp"
#include "gamestatemachine.hpp"
#include "menustate.hpp"
#include "pausestate.hpp"
#include "playstate.hpp"

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