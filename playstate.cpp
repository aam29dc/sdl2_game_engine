#include "playstate.hpp"

const std::string PlayState::_ID = "Play";

void PlayState::update() {
	//scroll background
	_scrollX += 10.0f * Time::getTime()->_dt;
	if (_scrollX >= _WIDTH) {
		_scrollX = 0;
	}

	//press esc -> goto pause state
	if(Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_ESCAPE)) {
		Game::getInstance()->getGSM()->pushState(new PauseState());
	}

	//update entities
	_player->update(Time::getTime()->_dt, _WIDTH, _HEIGHT);

	for (size_t i = 0; i < numBots; i++) {
		_bot.at(i).update(Time::getTime()->_dt, _player->pos);

		//bot attacks player if in range
		if (circlesIntersect(_player->pos, SDLGameObject::RADIUS, _bot.at(i).pos, SDLGameObject::RADIUS)) {
			if (_bot.at(i).attack()) {
				_player->takeDmg(10);
			}
		}
	}

	if (_player->getHealth() <= 0) {
		gameOver = true;
		return;
	}

	//apply gravity to our player
	//_player->velocity[1] += 20 * Time::getTime()->_dt;

	//check for collisions
	_checkCollisions();

	//remove dead bots
	for (std::vector<Bot>::iterator it = _bot.begin(); it != _bot.end();) {
		if (it->getHealth() <= 0) {
			it = _bot.erase(it);
			_score++;
		}
		else ++it;
	}

	//remove collided projectiles
	for (std::vector<Projectile>::iterator it = _player->proj.begin(); it != _player->proj.end();) {
		if (it->collided) {
			it = _player->proj.erase(it);
		}
		else ++it;
	}

	//the velocities for colliding objects were set to 0, in checkCollisions()
	//update positions of all our entites
	_player->pos[0] += _player->velocity[0];
	_player->pos[1] += _player->velocity[1];

	for (size_t i = 0; i < _player->proj.size(); i++) {
		_player->proj.at(i).pos[0] += _player->proj.at(i).velocity[0];
		_player->proj.at(i).pos[1] += _player->proj.at(i).velocity[1];
	}

	for (size_t i = 0; i < numBots; i++) {
		_bot.at(i).pos[0] += _bot.at(i).velocity[0];
		_bot.at(i).pos[1] += _bot.at(i).velocity[1];
	}

	//_cameraX = _player->pos[0];
	//_cameraX = _player->pos[1];
}

void PlayState::render(SDL_Renderer* renderer) const {
	SDL_Rect rec = { 0 };
	rec.w = _WIDTH;
	rec.h = _HEIGHT;

	TextureManager::getInstance()->draw(renderer, _bgID, rec, { _scrollX, 0, _WIDTH, _HEIGHT });
	TextureManager::getInstance()->draw(renderer, _bgID, rec, { -_WIDTH + _scrollX, 0, _WIDTH, _HEIGHT });

	//level
	_level->draw(renderer, _cameraX, _cameraY);

	//entities
	_player->draw(renderer);
	yeppers.draw(renderer);
	
	for (size_t i = 0; i < numBots; i++) {
		_bot.at(i).draw(renderer, _cameraX, _cameraY);
	}

	//ui
	drawBar(renderer, { 5.0f, 5.0f, 100.0f, 25.0f }, _player->getHealth(), Player::MAXHP);
	drawString(renderer, std::to_string(_score), FONT_SIZE::LARGE, _WIDTH / 2.0f, 0, { 255,255,255,0 });
	//drawString(renderer, std::to_string(Time::getTime()->_elapsed / 10000000), _WIDTH / 2.0f, 32.0f, { 255,255,255,0 });
	_player->drawInventory(renderer, _WIDTH, _HEIGHT);

	if (gameOver) {
		gameOverScreen(renderer);
	}
}

bool PlayState::onEnter() {
	std::cout << "Play enter.\n";

	_cameraX = 0.0f;
	_cameraY = 0.0f;

	_level = new Level();

	_player = new Player();

	for (size_t i = 0; i < numBots; i++) {
		_bot.push_back(Bot());
	}

	_score = 0;

	gameOver = false;

	_blocksID = 0;
	_bgID = 0;

	_scrollX = 0;

	// create our game items here, we should use a method that automatically assigns id numbers
	healPotion = Item(0, 5, "heal", 20, 5);

	/**/
	SDL_Texture* tex = 0;
	SDL_Surface* temp = 0;

	//load level
	_level->load(Window::getInstance()->_renderer, "assets/level.lvl", "assets/blocks_24.bmp", "assets/blocks_24.zmap");

	// Load Textures	// (we could use a basic texture for textureID = 0 for safety)
		//load background texture
	if (!TextureManager::getInstance()->load(Window::getInstance()->_renderer, _bgID, "assets/bg.bmp")) {
		#ifdef DEBUG
			std::cout << "assets/bg.bmp failed.\n";
		#endif
		return false;
	}

	//load player texture
	if (!TextureManager::getInstance()->load(Window::getInstance()->_renderer, _player->textureID, "assets/user.bmp")) {
		#ifdef DEBUG
			std::cout << "assets/user.bmp failed.\n";
		#endif
		return false;
	}

	//load bot texture
	if (numBots > 0) {
		if (!TextureManager::getInstance()->load(Window::getInstance()->_renderer, _bot.at(0).textureID, "assets/bot.bmp")) {
			#ifdef DEBUG
				std::cout << "assets/bot.bmp failed.\n";
			#endif
			return false;
		}
	}

	//load textures for pickup Items
	if (!TextureManager::getInstance()->load(Window::getInstance()->_renderer, yeppers.textureID, "assets/potion_pickup.png")) {
		#ifdef DEBUG
			std::cout << "assets/potion_pickup.png failed.\n";
		#endif
		return false;
	}

	//load textures for Inventory items
	if (!TextureManager::getInstance()->load(Window::getInstance()->_renderer, healPotion.getTextureID(), "assets/potion.bmp")) {
		#ifdef DEBUG
			std::cout << "assets/potion.bmp failed.\n";
		#endif
		return false;
	}

	//were using the same texture for all our bots
	for (size_t i = 1; i < numBots; i++) {
		_bot.at(i).textureID = _bot.at(0).textureID;
	}

	SDL_FreeSurface(temp);

	//give player items in their inventory
	_player->pickup(&healPotion);
	_player->pickup(&healPotion);

	//spawn entities
	_player->spawn(_WIDTH / 2, _HEIGHT / 2);

	yeppers.spawn(100, 100);

	unsigned int xpos = 0;
	unsigned int ypos = 0;

	for (size_t i = 0; i < numBots;) {
		xpos = distW(rng);
		ypos = distH(rng);

		//don't spawn ontop of players ... or other bots
		if (!((xpos >= _player->pos[0] && xpos <= _player->pos[0] + _player->size[0])
			|| (ypos >= _player->pos[1] && ypos <= _player->pos[1] + _player->size[1]))) {
			_bot.at(i).spawn((float)xpos, (float)ypos);
			i++;
		}
	}

	return true;
}

bool PlayState::onExit() {
	_bot.clear();
	_player->clean();

	return true;
}

void drawBar(SDL_Renderer* renderer, const SDL_FRect& rec, const int& rs, const int& maxrs) {
	SDL_FRect ol = rec;
	ol.x -= 1.0f;
	ol.y -= 1.0f;
	ol.w += 2.0f;
	ol.h += 2.0f;

	//outline
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRectF(renderer, &ol);

	SDL_FRect meter = rec;
	meter.w = float(rs) / float(maxrs) * rec.w;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRectF(renderer, &meter);

	//draw text
	drawString(renderer, std::to_string(rs) + "/" + std::to_string(maxrs), FONT_SIZE::LARGE, rec.x, rec.y, { 255,255,255,0 });
}

const float& PlayState::getCameraX() const {
	return _cameraX;
}

const float& PlayState::getCameraY() const {
	return _cameraY;
}

const std::string& PlayState::getStateID() const {
	return _ID;
}

void PlayState::gameOverScreen(SDL_Renderer* renderer) const {
	SDL_FRect rec = { (_WIDTH / 2), (_HEIGHT / 2), 150, 32 };

	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 127);
	SDL_RenderFillRectF(renderer, &rec);
	drawString(renderer, "Game Over", FONT_SIZE::LARGE, _WIDTH / 2.0f, _HEIGHT / 2.0f, { 255,255,255,0 });
	//press enter to restart game...
}

/*	All collision detection is done here. Checks collision w/ world, then other entities. If object collides, it stops checking collisions for that object.
	Player, and bot velocities have been set, but not final positions yet. Changes player, or bot velocity to zero if collided. Bots take dmg if collided w/ projectile.
*/

void PlayState::_checkPlayerCollisions(const SDL_FRect& pos, SDL_FRect& bpos) {
	// Player
	//player collision w/ world
	if (isOOB(pos)) {
		_player->velocity = { 0,0 };
	}
	else {
		//player collision w/ level objects
		for (size_t i = 0; i < _level->getObjects().size(); i++) {
			bpos.x = _level->getObjects().at(i).pos[0];
			bpos.y = _level->getObjects().at(i).pos[1];

			if (rectsIntersect(pos, bpos)) {
				//object isn't a stair
				if (_level->getObjects().at(i).z == 0) {
					_player->velocity = { 0,0 };
				}
				//object is a stair
				else if (_level->getObjects().at(i).z >= 1) {
					//player can't climb stairs / skip steps
					if (_level->getObjects().at(i).z - _player->z >= 2) {
						_player->velocity = { 0,0 };
					}
					//player is standing on stair
					else if (_level->getObjects().at(i).z == _player->z) {
						// do nothing
					}
					//player can climb consecutive stairs
					else {
						_player->z += 1;
					}
				}
				return;
			}
		}

		//player is on the floor since it isn't intersecting w/ any object
		_player->z = 0;

		/*if player velocity is 0, or was set to zero from previous loop, then we should be able to skip all checks afterwards*/
		//player collision w/ other bots
		for (size_t i = 0; i < numBots; i++) {

			bpos.x = _bot.at(i).pos[0] + _bot.at(i).velocity[0];
			bpos.y = _bot.at(i).pos[1] + _bot.at(i).velocity[1];

			if (rectsIntersect(pos, bpos)) {
				// if player collides with any bot: change player velocity to 0 and break out of loop
				_player->velocity = { 0 , 0 };
				return;
			}
		}
	}
}

void PlayState::_checkPlayerProjectileCollisions(SDL_FRect& pos, SDL_FRect& bpos) {
	// Player Projectiles
	for (size_t i = 0; i < _player->proj.size(); i++) {
		pos.x = _player->proj.at(i).pos[0] + _player->proj.at(i).velocity[0];
		pos.y = _player->proj.at(i).pos[1] + _player->proj.at(i).velocity[1];
		pos.w = pos.h = Player::PROJ_SIZE;

		//player projectiles collision w/ world
		if (isOOB(pos)) {
			_player->proj.at(i).collided = true;	//erasing a projectile here may mess up the iteration to proj.size(), we'd have to use an iterator
		}
		else {
			//player projectiles collision w/ level objects
			for (size_t j = 0; j < _level->getObjects().size(); j++) {
				bpos.x = _level->getObjects().at(j).pos[0];
				bpos.y = _level->getObjects().at(j).pos[1];

				if (rectsIntersect(pos, bpos)) {
					_player->proj.at(i).collided = true;
					return;
				}
			}
			/*if projectile collided, or was set to zero from previous loop, then we should be able to skip all checks afterwards*/
			//player projectiles collision w/ bots
			for (size_t j = 0; j < numBots; j++) {
				bpos = { _bot.at(j).pos[0] + _bot.at(j).velocity[0], _bot.at(j).pos[1] + _bot.at(j).velocity[1], SDLGameObject::SIZE, SDLGameObject::SIZE };
				if (rectsIntersect(pos, bpos)) {
					_player->proj.at(i).collided = true;	//^ so we store a bool value instead
					_bot.at(j).takeDmg(100);
					return;									//projectile only collides once, then we stop checking for collisions for that projectile
				}
			}
		}
	}
}

void PlayState::_checkBotCollisions() {
	SDL_FRect pos = { 0,0, SDLGameObject::SIZE, SDLGameObject::SIZE };
	SDL_FRect bpos = { 0, 0, SDLGameObject::SIZE, SDLGameObject::SIZE };
	//Bots
	// we don't check collision with bounds with world b.c they simply move towards the player
	// checks collision w/ other bots, not itself, and not previous bots already checked, 2d loop
	// ... keeping in mind the last bot in the list isn't checked against other bots, and therefore it's velocity won't change
	for (size_t i = 0; i < numBots; i++) {

		pos = { _bot.at(i).pos[0] + _bot.at(i).velocity[0], _bot.at(i).pos[1] + _bot.at(i).velocity[1] };

		for (size_t j = i + 1; j < numBots; j++) {

			bpos = { _bot.at(j).pos[0] + _bot.at(j).velocity[0], _bot.at(j).pos[1] + _bot.at(j).velocity[1] };

			if (rectsIntersect(pos, bpos)) {	// if bot collides with any bot: change that bots velocity to 0 and break out of loop
				_bot.at(i).velocity = { 0 , 0 };
				break;
			}
		}
	}
}

void PlayState::_checkCollisions() {
	SDL_FRect pos = { 0,0, SDLGameObject::SIZE, SDLGameObject::SIZE };
	SDL_FRect bpos = { 0, 0, SDLGameObject::SIZE, SDLGameObject::SIZE };

	//players future position
	pos.x = _player->pos[0] + _player->velocity[0];
	pos.y = _player->pos[1] + _player->velocity[1];

	_checkPlayerCollisions(pos, bpos);
	_checkPlayerProjectileCollisions(pos, bpos);
	_checkBotCollisions();
}

// given two points w/ radius a and b, if the distance between the points is less than (a+b) then they're intersecting circles
bool circlesIntersect(const std::array<float, 2>& apos, const float& arad, const std::array<float, 2>& bpos, const float& brad) {
	std::array<float, 2> diff = { apos[0] - bpos[0], apos[1] - bpos[1] };
	float dist = sqrtf(powf(diff.at(0), 2) + powf(diff.at(1), 2));
	float angle = atan2f(diff[1], diff[0]);

	std::array<float, 2> apt = { arad * cosf(angle), arad * sinf(angle) };
	std::array<float, 2> bpt = { brad * cosf(-angle), brad * sinf(-angle) };

	if (dist <= arad + brad) {
		return true;
	}
	return false;
}

// works for squares that are both at an angle of a multiple of 90 degrees (right angles)
bool rectsIntersect(const SDL_FRect& A, const SDL_FRect& B) {
	if (//top-left side of rectangle A
		(A.x >= B.x && A.x <= B.x + B.w
			&& A.y >= B.y && A.y <= B.y + B.h)
		|| //bottom-right side of rectangle A
		(A.x + A.w >= B.x && A.x + A.w <= B.x + B.w
			&& A.y + A.h >= B.y && A.y + A.h <= B.y + B.h))
	{
		return true;
	}
	return false;
}

/* game world is always a rectangle, and player can be at angle,
* we should check intersection of rectangle and an angled square
*/
bool PlayState::isOOB(const SDL_FRect& rec) const {
	if (rec.x < 0 || rec.x + rec.w > _WIDTH
		|| rec.y < 0 || rec.y + rec.h > _HEIGHT) {
		return true;
	}
	return false;
}