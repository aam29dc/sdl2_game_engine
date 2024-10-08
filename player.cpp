#include "player.hpp"

Player::Player() : SDLGameObject() {
	_rof = 0.5f;
	_lastFireTime = 0;
	_health = 20;
	_angle = 0.0f;
	velocity = { 0,0 };
	proj.clear();

	for (int i = 0; i < bagSize; i++) {
		_bag[i] = nullptr;
	}

	_lastItemUseTime = 0.0f;
}

Player::~Player() {

}

void Player::draw(SDL_Renderer* renderer, const float& cameraX, const float& cameraY) const {
	//draw player projectiles
	for (size_t i = 0; i < proj.size(); i++) {
		proj.at(i).draw(renderer, cameraX, cameraY);
	}

	//draw player
	TextureManager::getInstance()->draw(renderer, textureID, { 0, 0, SDLGameObject::SIZE, SDLGameObject::SIZE }, arrayToRect(pos), _angle);
}

void Player::move(const float& dt, const int& width, const int& height) {
	SDL_FPoint dir = { 0, -1 };

	//set angle
	if (Input::getInputHandler()->getMouseButtonState(RIGHT)) {
		dir = Input::getInputHandler()->getMousePosition();
		dir.x -= (pos[0] + (SDLGameObject::SIZE / 2.0f));	//center of player x
		dir.y -= (pos[1] + (SDLGameObject::SIZE / 2.0f));   //center of player y
		_angle = std::atan2f(dir.y, dir.x);
	}

	dir.x = cosf(_angle);
	dir.y = sinf(_angle);

	if (Input::getInputHandler()->isKeyDown(SDL_SCANCODE_W)) {
		velocity[0] += dir.x;
		velocity[1] += dir.y;
	}

	if (Input::getInputHandler()->isKeyDown(SDL_SCANCODE_S)) {
		velocity[0] += -dir.x;
		velocity[1] += -dir.y;
	}

	if (Input::getInputHandler()->isKeyDown(SDL_SCANCODE_A)) {
		velocity[0] += -dir.y;
		velocity[1] += dir.x;
	}

	if (Input::getInputHandler()->isKeyDown(SDL_SCANCODE_D)) {
		velocity[0] += dir.y;
		velocity[1] += -dir.x;

	}

	velocity[0] *= Player::SPEED * dt;
	velocity[1] *= Player::SPEED * dt;
}

void Player::attack(const float& dt) {
	if ((SDL_GetTicks() - _lastFireTime)/1000.0f >= _rof) {
		proj.push_back(Projectile(dt, pos, size, _angle, PROJ_SIZE, PROJ_SPEED));
		_lastFireTime = SDL_GetTicks();
		SoundManager::getInstance()->playSound("sfx_shoot");
	}
}

/* Ideally we would get our players input all at once, then process the input to their configured bindings */
void Player::update(const float& dt, const int& width, const int& height) {
	move(dt, width, height);

	for (int i = 0; i < numButtons; i++) {
		if (Input::getInputHandler()->isKeyDown((SDL_Scancode)(SDL_SCANCODE_1 + i))) {
			useItem(i);
		}
	}

	//spawn new projectiles
	if (Input::getInputHandler()->getMouseButtonState(LEFT)) {
		attack(dt);
	}

	//update player projectiles
	for (size_t i = 0; i < proj.size(); i++) {
		proj.at(i).update(dt);
	}
}

void Player::clean() {
	proj.clear();
}

const int& Player::getHealth() const {
	return _health;
}

void Player::takeDmg(const int& dmg) {
	_health -= dmg;
}

void Player::setHealth(const unsigned int health) {
	if (health >= 0 && health <= MAXHP) {
		_health = health;
	}
	else if (health > MAXHP) {
		_health = MAXHP;
	}
}

void Player::drawInventory(SDL_Renderer* renderer, const unsigned int& WIDTH, const unsigned int& HEIGHT) const {
	SDL_FRect rec = { 5, HEIGHT - 40 - 5, 40, 40 };

	//outline of Action Bar
	for (int i = 0; i < numButtons; i++) {
		if (_bag[i] != nullptr) {
			//draw whats inside of players inventory, in order, onto the Action Bar
			TextureManager::getInstance()->draw(renderer, _bag[i]->getTextureID(), { 0, 0, 32, 32 }, { rec.x, (float)HEIGHT - 40 - 5, 40, 40 }, 0);

			//draw cooldown for action bar
			if (_lastItemUseTime != 0 && ((SDL_GetTicks() - _lastItemUseTime) / 1000.0f <= 1.0f)) {
				rec.h = rec.h * ((SDL_GetTicks() - _lastItemUseTime) / 1000.0f);

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 127);
				SDL_RenderFillRectF(renderer, &rec);
			}

			//draw stack amount over icon
			if (_bag[i]->getAmount() >= 1) {
				drawString(renderer, std::to_string(_bag[i]->getAmount()), FONT_SIZE::MEDIUM, rec.x, rec.y, { 255,255,255,255 });
			}
		}

		rec.h = 40;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRectF(renderer, &rec);
		rec.x += 40;
	}
}

/* Probably not the best way to design how items work, but we use this method for now... */
bool Player::useItem(const unsigned int slot) {
	if ((slot < bagSize && _bag[slot] != nullptr) && ((SDL_GetTicks() - _lastItemUseTime) / 1000.0f >= 1.0f)) {
		//type of item effect
		if (_bag[slot]->getType() == "heal") {
			if (_health < MAXHP) {
				_health += _bag[slot]->getEffect();
				if (_health > MAXHP) _health = MAXHP;
				SoundManager::getInstance()->playSound("sfx_potion");
			}
			else return false;
		}

		//after using item, change the amount in the stack
		if (_bag[slot]->getAmount() <= 1) {	_bag[slot] = nullptr; }
		else { _bag[slot]->setAmount(_bag[slot]->getAmount() - 1); }

		//update cooldown on item
		_lastItemUseTime = SDL_GetTicks();

		return true;
	}
	return false;
}

bool Player::pickup(Item* const item) {
	//search for matching id item number to stack the items first
	for (int i = 0; i < bagSize; i++) {
		if (_bag[i] != nullptr) {
			if (_bag[i]->getID() == item->getID() && _bag[i]->getAmount() < _bag[i]->getMaxStack()) {
				_bag[i]->setAmount(_bag[i]->getAmount() + 1);
				return true;
			}
		}
	}

	//otherwise put it in another slot
	for (int i = 0; i < bagSize; i++) {
		if (_bag[i] == nullptr) {
			_bag[i] = item;
			_bag[i]->setAmount(1);
			return true;
		}
	}

	return false;
}