#include "gameoverstate.hpp"

const std::string GameOverState::_ID = "GameOver";

void GameOverState::update(SDL_Renderer* renderer) {

}

void GameOverState::render() const {

}

bool GameOverState::onEnter() {
	return true;
}

bool GameOverState::onExit() {
	return true;
}

const std::string& GameOverState::getStateID() const {
	return _ID;
}