#pragma once
#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "gamestate.hpp"

#include "button.hpp"
#include "input.hpp"
#include "game.hpp"

class GameOverState : public GameState {
public:
	void update();
	void render(SDL_Renderer* renderer) const;

	bool onEnter();
	bool onExit();

	const std::string& getStateID() const;
private:
	static const std::string _ID;

	static void _GameOverStateToMainMenu();
	static void _GameOverStateToPlay();
	static void _GameOverStateToExit();

	enum {numButtons = 3};
	Button* _button[numButtons];
};

#endif