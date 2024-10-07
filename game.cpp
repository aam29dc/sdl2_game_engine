#include "game.hpp"

Game* Game::_instance = nullptr;

Game::Game() {
	_quit = false;
	_GSM = nullptr;
}

Game::~Game() {
	_quit = true;
}

Game* Game::getInstance() {
	if (_instance == nullptr) _instance = new Game();
	return _instance;
}

void Game::handleEvents() {
	Input::getInputHandler()->update();
}

bool Game::init() {
	if (!Window::getInstance()->init()) return false;

	_GSM = new GameStateMachine();
	_GSM->pushState(new MenuState());

	return true;
}

void Game::render(SDL_Renderer* renderer) const {
	//SDL_RenderSetScale(renderer, 1.0f, 1.0f);
	//SDL_RenderSetViewport(renderer, &rec);

	//clear
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	_GSM->render(renderer);

	SDL_RenderPresent(renderer);
}

void Game::update() {
	_GSM->update();
}

GameStateMachine* Game::getGSM() {
	return _GSM;
}