#include "projectile.hpp"

Projectile::Projectile(const float& dt, const std::array<float, 2>& ppos, const std::array<float, 2>& psize, const float& a, const float& sz, const float& sp) {
	collided = false;
	angle = a;
	speed = sp;
	size[0] = sz;
	size[1] = sz;
	pos[0] = ppos[0] + (SDLGameObject::SIZE / 2.0f);
	pos[1] = ppos[1] + (SDLGameObject::SIZE / 2.0f);
	velocity[0] = speed * cosf(angle) * dt;
	velocity[1] = speed * sinf(angle) * dt;
}

Projectile::~Projectile() {

}

void Projectile::draw(SDL_Renderer* renderer, const float& cameraX, const float& cameraY) const {
	SDL_FRect rec = { pos[0], pos[1], size[0], size[1] };

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRectF(renderer, &rec);
}

void Projectile::update(const float& dt) {
	velocity[0] = speed * cosf(angle) * dt;
	velocity[1] = speed * sinf(angle) * dt;
}

void Projectile::clean() {

}