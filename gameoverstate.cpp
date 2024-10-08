#include "gameoverstate.hpp"

const std::string GameOverState::_ID = "GameOver";

void GameOverState::update() {
	SDL_FPoint mpos = Input::getInputHandler()->getMousePosition();

	for (int i = 0; i < numButtons; i++) {
		if (mpos.x >= _button[i]->_posx && mpos.x <= _button[i]->_posx + _button[i]->_width
			&& mpos.y >= _button[i]->_posy && mpos.y <= _button[i]->_posy + _button[i]->_height) {
			_button[i]->_hover = true;
			if (Input::getInputHandler()->getMouseButtonState(mouse_buttons::LEFT)) {
				_button[i]->_click = true;
			}
			else { _button[i]->_click = false; }
		}
		else { _button[i]->_hover = false; }
	}

	for (int i = 0; i < numButtons; i++) {
		if (_button[i]->_click == true) {
			_button[i]->_callback();
		}
	}
}

void GameOverState::render(SDL_Renderer* renderer) const {
	for (int i = 0; i < numButtons; i++) {
		_button[i]->draw(renderer);
	}
}

bool GameOverState::onEnter() {
	for (int i = 0; i < numButtons; i++) {
		_button[i] = new Button("Null", 120.0f, 32.0f, 350, 100 + (i * 50));
	}
	_button[0]->_text = "Menu";
	_button[1]->_text = "Restart";
	_button[2]->_text = "Exit";

	_button[0]->_callback = _GameOverStateToMainMenu;
	_button[1]->_callback = _GameOverStateToPlay;
	_button[2]->_callback = _GameOverStateToExit;

	return true;
}

bool GameOverState::onExit() {
	for (int i = 0; i < numButtons; i++) {
		delete _button[i];
	}

	return true;
}

const std::string& GameOverState::getStateID() const {
	return _ID;
}

void GameOverState::_GameOverStateToMainMenu() {
	Game::getInstance()->getGSM()->changeState(new MenuState());
}

void GameOverState::_GameOverStateToPlay() {
	Game::getInstance()->getGSM()->changeState(new PlayState());
}

void GameOverState::_GameOverStateToExit() {
	Game::getInstance()->~Game();
	Window::getInstance()->~Window();
}