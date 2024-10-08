#pragma once
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

struct SDL_Renderer;

class GameObject {
private:
public:
	virtual void draw(SDL_Renderer* renderer, const float& cameraX = 0, const float& cameraY = 0) const = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
protected:
	GameObject() {}
	virtual ~GameObject() {}
};

#endif