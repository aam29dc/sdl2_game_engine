#pragma once
#ifndef FONT_HPP
#define FONT_HPP

#include <SDL_ttf.h>
#include <string>

#ifdef DEBUG
	#include <iostream>
#endif

inline extern const int TEXTSIZE_SMALL = 12;
inline extern const int TEXTSIZE_MEDIUM = 17;
inline extern const int TEXTSIZE_LARGE = 22;

inline extern const int FONTWIDTH = 13;

enum class FONT_SIZE {
	LARGE = 3,
	MEDIUM = 2,
	SMALL = 1,
};

extern TTF_Font* font_l;
extern TTF_Font* font_m;
extern TTF_Font* font_s;

bool initFont(const std::string& src = "assets/fonts/RobotoMono-VariableFont_wght.ttf");

/* Draws text on screen.
* \param str text to display
* \param xpos [-1,1]
* \param ypos [-1,1]
* \returns void
*/
void drawString(SDL_Renderer* renderer, const std::string& str, const FONT_SIZE f, const float& xpos, const float& ypos, const SDL_Color& color, const unsigned& maxtext = 0, const bool& limit = false);
#endif