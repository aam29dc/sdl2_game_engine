#include "bot.hpp"

Bot::Bot(const float& x, const float &y) : SDLGameObject() {
	_rof = 0.5f;
	_lastFireTime = 0;
	_health = 100;
	velocity = { 0, 0 };
	_angle = 0.0f;
	pos = { x , y };
}

Bot::~Bot() {
	_health = 0;
}

void Bot::draw(SDL_Renderer* renderer, const float& cameraX, const float& cameraY) const {
	TextureManager::getInstance()->draw(renderer, textureID, { 0, 0, SDLGameObject::SIZE, SDLGameObject::SIZE }, arrayToRect(pos), _angle);
}

void Bot::update(const float& dt, const std::array<float, 2>& ppos) {
	//move towards player
	float x = (ppos[0] + (SDLGameObject::SIZE/2.0f)) - (pos[0] + (SDLGameObject::SIZE/2.0f));
	float y = (ppos[1] + (SDLGameObject::SIZE/2.0f)) - (pos[1] + (SDLGameObject::SIZE/2.0f));

	float dist = sqrtf(powf(x, 2) + powf(y, 2));

	if (dist > 0.0f) {
		_angle = atan2f(y, x);

		x /= dist;	// x = cosf(_angle)
		y /= dist;	// y = sinf(_angle)

		velocity[0] = Bot::SPEED * x * dt;
		velocity[1] = Bot::SPEED * y * dt;
	}
	//check if direction would lead to a collision of an object

}

bool Bot::attack() {
	if ((SDL_GetTicks() - _lastFireTime) / 1000.0f >= _rof) {
		_lastFireTime = SDL_GetTicks();
		return true;
	}
	return false;
}

void Bot::clean() {

}

void Bot::takeDmg(const int& dmg) {
	_health -= dmg;
}

const int& Bot::getHealth() const {
	return _health;
}