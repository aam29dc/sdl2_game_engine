#pragma once
#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "gamestate.hpp"

class GameOverState : public GameState {
public:
	void update(SDL_Renderer* renderer);
	void render() const;

	bool onEnter();
	bool onExit();

	const std::string& getStateID() const;
private:
	static const std::string _ID;
};

#endif