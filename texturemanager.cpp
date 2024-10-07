#include "texturemanager.hpp"

TextureManager* TextureManager::_instance = nullptr;

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {
	for (size_t i = 0; i < textureMap.size(); i++) {
		SDL_DestroyTexture(textureMap.at(i));
	}
	textureMap.clear();
}

TextureManager* TextureManager::getInstance() {
	if (_instance == nullptr) _instance = new TextureManager();
	return _instance;
}

bool TextureManager::load(SDL_Renderer* renderer, size_t& id, const std::string& imgFile) {
	SDL_Surface* temp = 0;
	SDL_Texture* tex = 0;

	temp = IMG_Load(imgFile.c_str());
	if (temp == 0) {
		#ifdef DEBUG
			std::cout << "IMG_Load failed\n";
		#endif
		return false;
	}
	tex = SDL_CreateTextureFromSurface(renderer, temp);
	if (tex == 0) {
		#ifdef DEBUG
			std::cout << "CreateTexture failed\n";
		#endif
		return false;
	}

	SDL_FreeSurface(temp);
	
	textureMap.push_back(tex);

	id = textureMap.size() - 1;

	return true;
}

void TextureManager::draw(SDL_Renderer* renderer, const size_t& id, const SDL_Rect& src, const SDL_FRect& pos, const float& angle) const {
	SDL_RenderCopyExF(renderer, textureMap.at(id), &src, &pos, (double)angle * 180 / M_PI, NULL, SDL_FLIP_NONE);
}