#include "level.hpp"

Level::Level() {
	_objects.clear();
	_textureID = 0;
}

Level::~Level() {
	_objects.clear();
}

const std::vector<SDLGameObject>& Level::getObjects() const {
	return _objects;
}

/*	.lvl and .zmap files are Common Seperated Values (CSV) files */
bool Level::load(SDL_Renderer* renderer, const std::string& lvl, const std::string& image, const std::string& zmap) {
	//load level texture
	if (!TextureManager::getInstance()->load(renderer, _textureID, "assets/textures/blocks_24.bmp")) return false;

	//parse level for objects
	std::ifstream level(lvl);
	if (!level.is_open()) return false;

	//parse zmap for objects, this is for stairs, etc
	std::ifstream zlvl(zmap);
	if (!zlvl.is_open()) return false;

	char ch = 0;
	int i = 0;
	int num = 0;

	int zvalues[64] = { 0 };

	while (zlvl.get(ch)) {
		if (ch != ' ' && ch != '\n' && ch != '\t' && ch != EOF) {
			if (ch != ',') {
				num *= 10;
				num += (ch - '0');
			}
			else if (ch == ',') {
				zvalues[i] = num;
				num = 0;
				i++;
			}
		}
	}

	ch = 0;
	i = 0;
	num = 0;

	while (level.get(ch)) {
		if (ch != ' ' && ch != '\n' && ch != '\t' && ch != EOF) {

			if (ch != ',') {
				num *= 10;
				num += (ch - '0');
			}

			else if (ch == ',') {
				if (num != 0) {
					_objects.push_back(SDLGameObject());

					//set position of object based on the position of the char in the file
					_objects.back().pos[0] = (i % 34) * SDLGameObject::SIZE;
					_objects.back().pos[1] = std::floor(i / 34) * SDLGameObject::SIZE;

					//set texture of object based on the character. off by 1
					_objects.back().textureID = _textureID;
					_objects.back().src.x = MARGIN + (((num) % 8) * (SDLGameObject::SIZE + MARGIN));
					_objects.back().src.y = MARGIN + (std::floor((num) / 8) * (SDLGameObject::SIZE + MARGIN));
					_objects.back().z = zvalues[num];
				}
				num = 0;
				i++;
			}

		}
	}

	level.close();

	return true;
}

/*
 CHAR-SET: 0 to 9, then A to Z, then a to z ( 62 total chars )
	48,0	57,9	65,A	90,Z	97,a	122,z
*/

void Level::draw(SDL_Renderer* renderer, const float& cameraX, const float& cameraY) const {
	for (size_t i = 0; i < _objects.size(); i++) {
		_objects.at(i).draw(renderer, cameraX, cameraY);
	}
}