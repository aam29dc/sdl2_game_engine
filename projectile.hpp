#pragma once
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "sdlgameobject.hpp"

#include <glm/glm.hpp>
#include <SDL.h>
#include <array>

class Projectile : public SDLGameObject {
public:
	Projectile(const float& dt, const std::array<float, 2>&ppos, const std::array<float, 2>&psize, const float& a, const float& sz, const float& sp);
	~Projectile();

	virtual void draw(SDL_Renderer * renderer, const float& cameraX = 0, const float& cameraY = 0) const;
	virtual void update(const float& dt);
	virtual void clean();

	bool collided;
	float speed;
	float angle;
};

#endif