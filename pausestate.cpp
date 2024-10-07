#include "pausestate.hpp"

const std::string PauseState::_ID = "Pause";

void PauseState::update() {
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_ESCAPE)) {
		Game::getInstance()->getGSM()->popState();
	}
}

void PauseState::render(SDL_Renderer* renderer) const {
	drawString(renderer, "Game Paused...", FONT_SIZE::LARGE, 300, 300, { 255,255,255,255 });
}

bool PauseState::onEnter() {
	return true;
}

bool PauseState::onExit() {
	return true;
}

const std::string& PauseState::getStateID() const {
	return _ID;
}