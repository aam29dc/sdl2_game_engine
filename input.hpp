#pragma once
#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL.h>
#include <vector>

#include "window.hpp"

enum mouse_buttons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class Input {
private:
	static Input* _input;	//instance

	std::vector<bool> _mouseButtonStates;
	std::vector<bool> _prevMouseButtonStates;

	SDL_FPoint _mPos;

	const Uint8* _keyStates;
	Uint8 _prevKeyStates[SDL_NUM_SCANCODES];
	int _numkeys;

	void _onMouseButtonDown(const SDL_Event& event);
	void _onMouseButtonUp(const SDL_Event& event);
	void _onMouseMotion(const SDL_Event& event);
public:
	Input();
	static Input* getInputHandler();
	void updatePrevKeyStates();
	bool update();
	const bool& getMouseButtonState(const int& buttonNumber) const;
	const SDL_FPoint& getMousePosition() const;
	bool isKeyDown(const SDL_Scancode& key) const;
	bool isKeyReleased(const SDL_Scancode& key) const;
	bool isMouseKeyReleased(const int& buttonNumber) const;
};

#endif