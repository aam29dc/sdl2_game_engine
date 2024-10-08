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
	#ifdef DEBUG
		std::cout << "pushed " << state->getStateID() << "\n";
	#endif
}

void GameStateMachine::changeState(GameState* state) {
	if (!_gameStates.empty()) {
		if (_gameStates.back()->getStateID() == state->getStateID()) {
			return;
		}

		if (_gameStates.back()->onExit()) {
			#ifdef DEBUG
				std::cout << "pop " << _gameStates.back()->getStateID() << "\n";
			#endif
			_gameStates.pop_back();
		}

		_gameStates.push_back(state);
		#ifdef DEBUG
			std::cout << "push " << _gameStates.back()->getStateID() << "\n";
		#endif
		_gameStates.back()->onEnter();
	}
}

void GameStateMachine::popState() {
	if (!_gameStates.empty()) {
		if (_gameStates.back()->onExit()) {
			#ifdef DEBUG
				std::cout << "popped " << _gameStates.back()->getStateID() << "\n";
			#endif
			_gameStates.pop_back();
		}
	}
}

#ifdef DEBUG
	void GameStateMachine::print() const {
		for (int i = 0; i < _gameStates.size(); i++) {
			std::cout << i << " " << _gameStates[i]->getStateID() << "\n";
		}
	}
#endif