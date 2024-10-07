#include "game.hpp"
#include "time.hpp"

#include <iostream>

#include <SDL.h>

#undef main

using namespace std;

auto main() -> int {
	if (!Game::getInstance()->init()) {
		return 0;
	}

	SDL_SetRenderDrawBlendMode(Window::getInstance()->_renderer, SDL_BLENDMODE_BLEND);

	Time::getTime()->_start = SDL_GetPerformanceCounter();

	while (!Window::getInstance()->getQuit()) {
		Time::getTime()->_current = SDL_GetTicks();

		Game::getInstance()->handleEvents();
		Game::getInstance()->update();
		Game::getInstance()->render(Window::getInstance()->_renderer);

		Time::getTime()->_dt = (float)((Time::getTime()->_current - Time::getTime()->_last) / 1000.0f);
		Time::getTime()->_last = Time::getTime()->_current;
		Time::getTime()->_elapsed = (SDL_GetPerformanceCounter() - Time::getTime()->_start);
	}

	return 0;
}