#pragma once
#ifndef SDLGAMEOBJECT_HPP
#define SDLGAMEOBJECT_HPP

#include "gameobject.hpp"
#include "texturemanager.hpp"

#include <SDL.h>
#include <array>

SDL_FRect arrayToRect(const std::array<float, 2>& arr);

class SDLGameObject : public GameObject {
protected:
public:
	SDLGameObject();
	virtual ~SDLGameObject();

	virtual void draw(SDL_Renderer* renderer, const float& cameraX = 0, const float& cameraY = 0) const;
	virtual void update();
	virtual void clean();

	virtual void spawn(const float& x, const float& y);

	static constexpr int SIZE = 24;
	static constexpr float RADIUS = 1.42f*SIZE/2.0f;	// 1.42 ~= sqrt(2)

	size_t textureID;

	SDL_Rect src;	// used for objects that use one big texture / frames

	int z;
	std::array<float, 2> pos;
	std::array<float, 2> size;
	std::array<float, 2> velocity;
};

#endif