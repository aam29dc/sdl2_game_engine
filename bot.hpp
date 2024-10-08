#pragma once
#ifndef BOT_H
#define BOT_H

#include "sdlgameobject.hpp"
#include "texturemanager.hpp"
#include "soundmanager.hpp"
#include <SDL.h>

class Bot : public SDLGameObject {
public:
	Bot(const float& x = 0, const float& y = 0);
	~Bot();

	virtual void draw(SDL_Renderer* renderer, const float& cameraX = 0, const float& cameraY = 0) const;
	virtual void update(const float& dt, const std::array<float, 2>& ppos);
	virtual void clean();

	void takeDmg(const int& dmg);
	bool attack();

	static constexpr float SPEED = 30.0f;

	const int& getHealth() const;
protected:
	/*	armor, health regen, movement speed, attack speed, dmg, ... */
	float _rof;
	Uint32 _lastFireTime;
	float _angle;
	int _health;
};

#endif