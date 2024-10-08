#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "font.hpp"

inline extern const unsigned int SCREEN_WIDTH = 800;
inline extern const unsigned int SCREEN_HEIGHT = 600;

#ifdef DEBUG
	#include <iostream>
#endif

class Window {
private:
	static Window* _instance;
	unsigned int _height;
	unsigned int _width;

	bool _mouseFocus;
	bool _keyboardFocus;
	bool _fullScreen;
	bool _minimized;
	bool _quit;
public:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	const unsigned int& getWidth() const;
	const unsigned int& getHeight() const;
	const bool& getMouseFocus() const;
	const bool& getKeyboardFocus() const;
	const bool& getFullscreen() const;
	const bool& getMinimized() const;
	const bool& getQuit() const;

	Window(const unsigned width = SCREEN_WIDTH, const unsigned height = SCREEN_HEIGHT);
	~Window();

	bool init();
	void loadingScreen() const;

	static Window* getInstance();

	void handleWindowEvent(SDL_Event& e);
};

#endif