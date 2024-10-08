#pragma once
#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "gamestate.hpp"
#include "button.hpp"
#include "input.hpp"

#include "playstate.hpp"

#include "soundmanager.hpp"

#include "game.hpp"

#include <iostream>

class MenuState : public GameState {
public:
	void update();
	void render(SDL_Renderer* renderer) const;

	bool onEnter();
	bool onExit();

	const std::string& getStateID() const;
private:
	static const std::string _ID;

	static void _MenuToPlay();
	static void _MenuToQuit();

	enum { numButtons = 2 };
	Button* _button[numButtons];

	std::string sfx_click;
};

#endif