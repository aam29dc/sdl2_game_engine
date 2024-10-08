#include "font.hpp"

TTF_Font* font_s;
TTF_Font* font_m;
TTF_Font* font_l;

bool initFont(const std::string& src) {
    if (TTF_Init() == -1) return false;

    font_l = TTF_OpenFont("assets/fonts/RobotoMono-VariableFont_wght.ttf", int(TEXTSIZE_LARGE));
    if (font_l == NULL) return false;

	font_m = TTF_OpenFont("assets/fonts/RobotoMono-VariableFont_wght.ttf", int(TEXTSIZE_MEDIUM));
	if (font_m == NULL) return false;

	font_s = TTF_OpenFont("assets/fonts/RobotoMono-VariableFont_wght.ttf", int(TEXTSIZE_SMALL));
	if (font_s == NULL) return false;

    return true;
}

void drawString(SDL_Renderer* renderer, const std::string& str, const FONT_SIZE f, const float& xpos, const float& ypos, const SDL_Color& color, const unsigned& maxtext, const bool& limit) {
	if (str.empty()) return;

	TTF_Font* font = nullptr;

	switch (f) {
	case FONT_SIZE::LARGE:
		font = font_l;
		break;
	case FONT_SIZE::MEDIUM:
		font = font_m;
		break;
	case FONT_SIZE::SMALL:
		font = font_s;
		break;
	}

	SDL_Surface* surfaceMsg = TTF_RenderText_Solid(font, str.c_str(), color);
	if (surfaceMsg == NULL) {
		#ifdef DEBUG
			std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << "\n";
		#endif
		return;
	}

	SDL_Texture* msg = SDL_CreateTextureFromSurface(renderer, surfaceMsg);
	if (msg == NULL) {
		#ifdef DEBUG
			std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << "\n";
		#endif
		return;
	}

	SDL_FRect dst_rect = { 0 };
	SDL_Rect src_rect = { 0 };

	dst_rect.x = xpos;
	dst_rect.y = ypos-4;													// the font RobotoMono-VariableFont_wght.ttf is shifted
	dst_rect.w = (float)surfaceMsg->w;
	dst_rect.h = (float)surfaceMsg->h;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = surfaceMsg->w;
	src_rect.h = surfaceMsg->h;

	if (limit && (str.length() > maxtext)) {
		src_rect.w = FONTWIDTH * maxtext;									// max length
		dst_rect.w = float(src_rect.w);
		src_rect.x = int(str.length() - maxtext) * FONTWIDTH;				// shift
	}

	SDL_RenderCopyF(renderer, msg, &src_rect, &dst_rect);

	SDL_FreeSurface(surfaceMsg);
	SDL_DestroyTexture(msg);
}