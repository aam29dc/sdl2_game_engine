#pragma once
#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "gamestate.hpp"
#include "player.hpp"
#include "level.hpp"
#include "bot.hpp"
#include "item.hpp"
#include "itemobject.hpp"

#include "texturemanager.hpp"

#include "pausestate.hpp"
#include "game.hpp"

#include <SDL.h>
#include <SDL_timer.h>

#include <iostream>
#include <random>
#include <float.h>
#include <map>
#include <cmath>

inline std::random_device dev;
inline std::mt19937 rng(dev());
inline std::uniform_int_distribution<std::mt19937::result_type> distW(0, 800);
inline std::uniform_int_distribution<std::mt19937::result_type> distH(0, 600);

void drawBar(SDL_Renderer* renderer, const SDL_FRect& rec, const int& rs, const int& maxrs);
bool rectsIntersect(const SDL_FRect& A, const SDL_FRect& B);
bool circlesIntersect(const std::array<float, 2>& apos, const float& arad, const std::array<float, 2>& bpos, const float& brad);

class PlayState : public GameState {
public:
	void update();
	void render(SDL_Renderer* renderer) const;
	bool onEnter();
	bool onExit();
	const std::string& getStateID() const;

	const float& getCameraX() const;
	const float& getCameraY() const;

	void gameOverScreen(SDL_Renderer* renderer) const;

	bool isOOB(const SDL_FRect& rec) const;
private:
	void _checkCollisions();
	void _checkPlayerCollisions(const SDL_FRect& pos, SDL_FRect& bpos);
	void _checkPlayerProjectileCollisions(SDL_FRect& pos, SDL_FRect& bpos);
	void _checkBotCollisions();

	static const std::string _ID;

	static constexpr int _WIDTH = 800;
	static constexpr int _HEIGHT = 600;

	bool gameOver;

	Player* _player;
	Level* _level;
	std::vector<Bot> _bot;
	const size_t numBots = 0;
	int _score;						//server tracks player scores

	float _cameraX;
	float _cameraY;

	size_t _blocksID, _bgID;		// texure ids

	float _scrollX;					//background scroll effect

	ItemObject yeppers;

	//Inventory items
	/* We would create/load all items, then any copies of items would be taken from here */
	Item healPotion;
};

#endif