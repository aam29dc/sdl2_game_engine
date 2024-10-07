#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "sdlgameobject.hpp"
#include "input.hpp"
#include "projectile.hpp"
#include "time.hpp"
#include "texturemanager.hpp"
#include "item.hpp"

#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

class Player : public SDLGameObject {
public:
	Player();
	~Player();
	virtual void draw(SDL_Renderer* renderer, const float& cameraX = 0, const float& cameraY = 0) const;
	virtual void update(const float& dt, const int& width, const int& height);
	virtual void clean();
	void move(const float& dt, const int& width, const int& height);
	void attack(const float& dt);

	void drawInventory(SDL_Renderer* renderer, const unsigned int& WIDTH, const unsigned int& HEIGHT) const;
	bool useItem(const unsigned int slot);
	bool pickup(Item* const item);

	std::vector<Projectile> proj;

	static constexpr int MAXHP = 100;
	static constexpr float SPEED = 40.0f;
	static constexpr float PROJ_SPEED = 100.0f;
	static constexpr float PROJ_SIZE = 2.0f;

	enum { bagSize = 10, numButtons = 5 };

	const int& getHealth() const;

	void setHealth(const unsigned int health);

	void takeDmg(const int&);
protected:
	float _angle;
	float _rof;
	Uint32 _lastFireTime;
	int _health;
	Item* _bag[bagSize];
	Uint32 _lastItemUseTime;
};

#endif