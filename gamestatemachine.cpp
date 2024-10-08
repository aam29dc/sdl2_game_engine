#include "gamestatemachine.hpp"

void GameStateMachine::update() {
	if (!_gameStates.empty()) {
		_gameStates.back()->update();
	}
}
void GameStateMachine::render(SDL_Renderer* renderer) const {
	if (!_gameStates.empty()) {
		_gameStates.back()->render(renderer);
	}
}

void GameStateMachine::pushState(GameState* state) {
	_gameStates.push_back(state);
	_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* state) {
	if (!_gameStates.empty()) {
		if (_gameStates.back()->getStateID() == state->getStateID()) {
			return;
		}

		if (_gameStates.back()->onExit()) {
			_gameStates.pop_back();
		}
		_gameStates.push_back(state);
		_gameStates.back()->onEnter();
	}
}

void GameStateMachine::popState() {
	if (!_gameStates.empty()) {
		if (_gameStates.back()->onExit()) {
			_gameStates.pop_back();
		}
	}
}

void GameStateMachine::print() const {
	for (int i = 0; i < _gameStates.size(); i++) {
		std::cout << i << " " << _gameStates[i]->getStateID() << "\n";
	}
}