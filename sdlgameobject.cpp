#include "sdlgameobject.hpp"

SDL_FRect arrayToRect(const std::array<float, 2>& arr) {
	return { arr[0], arr[1], SDLGameObject::SIZE, SDLGameObject::SIZE };
}

SDLGameObject::SDLGameObject() {
	size = { SIZE, SIZE };
	pos = { 0 };

	velocity = { 0 };

	textureID = 0;

	src = { 0, 0, SIZE, SIZE };

	z = 0;
}

void SDLGameObject::draw(SDL_Renderer* renderer, const float& cameraX, const float& cameraY) const {
	SDL_FRect ds = { pos[0] - cameraX, pos[1] - cameraY, size[0], size[1] };

	TextureManager::getInstance()->draw(renderer, textureID, src, ds);
	return;

	//default rect draw if no texture
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRectF(renderer, &ds);
}

void SDLGameObject::spawn(const float& x, const float& y) {
	pos[0] = x;
	pos[1] = y;
}

void SDLGameObject::update() {

}

void SDLGameObject::clean() {

}

SDLGameObject::~SDLGameObject() {

}