#include "menustate.hpp"

const std::string MenuState::_ID = "Menu";

void MenuState::update() {
	SDL_FPoint mpos = Input::getInputHandler()->getMousePosition();

	for (int i = 0; i < numButtons; i++) {
		if (mpos.x >= _button[i]->_posx && mpos.x <= _button[i]->_posx + _button[i]->_width
			&& mpos.y >= _button[i]->_posy && mpos.y <= _button[i]->_posy + _button[i]->_height) {
			_button[i]->_hover = true;
			if (Input::getInputHandler()->isMouseKeyReleased(mouse_buttons::LEFT)) {
				_button[i]->_click = true;
			}
			else { _button[i]->_click = false; }
		}
		else { _button[i]->_hover = false; }
	}

	for (int i = 0; i < numButtons; i++) {
		if (_button[i]->_click == true) {
			SoundManager::getInstance()->playSound(sfx_click);
			_button[i]->_callback();
		}
	}
}

void MenuState::render(SDL_Renderer* renderer) const {
	for (int i = 0; i < numButtons; i++) {
		_button[i]->draw(renderer);
	}
}

bool MenuState::onEnter() {
	for (int i = 0; i < numButtons; i++) {
		_button[i] = new Button("Null", 100.0f, 32.0f, 350, 100 + (i*50));
	}

	_button[0]->_text = "Play";
	_button[1]->_text = "Exit";

	_button[0]->_callback = _MenuToPlay;
	_button[1]->_callback = _MenuToQuit;

	sfx_click = "click";

	if (SoundManager::getInstance()->load("assets/sounds/click.wav", sfx_click, SOUND_SFX)==false) {
	#ifdef DEBUG
		std::cout << "failed to load click.mp3\n";
	#endif
		return false;
	}

	return true;
}

bool MenuState::onExit() {
	for (int i = 0; i < numButtons; i++) {
		delete _button[i];
	}
	return true;
}

const std::string& MenuState::getStateID() const {
	return _ID;
}

void MenuState::_MenuToPlay() {
	Game::getInstance()->getGSM()->changeState(new PlayState());
}

void MenuState::_MenuToQuit() {
	Game::getInstance()->~Game();
	Window::getInstance()->~Window();
}