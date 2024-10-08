#include "window.hpp"

Window* Window::_instance = nullptr;

Window::Window(const unsigned width, const unsigned height) {
	_height = SCREEN_HEIGHT;
	_width = SCREEN_WIDTH;
	_mouseFocus = false;
	_keyboardFocus = false;
	_fullScreen = false;
	_minimized = false;
	_quit = false;
	_window = nullptr;
	_renderer = nullptr;
}

Window* Window::getInstance() {
	if (_instance == nullptr) _instance = new Window();
	return _instance;
}

Window::~Window() {
	_quit = true;
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		_window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			#ifdef DEBUG
				std::cout << "Warning: Linear texture filtering not enabled!" << "\n";
			#endif
			return false;
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			#ifdef DEBUG
				std::cout << "SDL_image could not initialize! SDL_image Error :" << IMG_GetError() << "\n";
			#endif
			return false;
		}

		if (!initFont()) {
			#ifdef DEBUG
				std::cout << "Init font error SDL_ttf: " << TTF_GetError() << "\n";
			#endif
			return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			#ifdef DEBUG
				std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << "\n";
			#endif
			return false;
		}

		loadingScreen();

		//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
		SDL_RenderSetIntegerScale(_renderer, SDL_FALSE);
		SDL_RenderSetLogicalSize(_renderer, _width, _height);

		return true;
	}
	return false;
}

void Window::handleWindowEvent(SDL_Event& e) {
	if (e.type == SDL_WINDOWEVENT) {
		bool updateCaption = false;

		switch (e.window.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			_width = e.window.data1;
			_height = e.window.data2;

			if (_width <= SCREEN_WIDTH) {
				_width = SCREEN_WIDTH;
			}
			if (_height <= SCREEN_HEIGHT) {
				_height = SCREEN_HEIGHT;
			}

			SDL_SetWindowSize(_window, _width, _height);
			SDL_RenderPresent(_renderer);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(_renderer);
			break;
		case SDL_WINDOWEVENT_ENTER:
			_mouseFocus = true;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_LEAVE:
			_mouseFocus = false;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			_keyboardFocus = true;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			_keyboardFocus = false;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			_minimized = true;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			_minimized = false;
			break;
		case SDL_WINDOWEVENT_RESTORED:
			_minimized = false;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			_quit = true;
			break;
		}
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
		if (_fullScreen) {
			SDL_SetWindowFullscreen(_window, 0);
			_fullScreen = false;
		}
		else {
			SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			_fullScreen = true;
			_minimized = false;
		}
	}
}

void Window::loadingScreen() const {
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
	drawString(_renderer, "Loading...", FONT_SIZE::LARGE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, { 255,255,255,0 });
	SDL_RenderPresent(_renderer);
}

const unsigned int& Window::getWidth() const {
	return _width;
}

const unsigned int& Window::getHeight() const {
	return _height;
}

const bool& Window::getMouseFocus() const {
	return _mouseFocus;
}

const bool& Window::getKeyboardFocus() const {
	return _keyboardFocus;
}

const bool& Window::getFullscreen() const {
	return _fullScreen;
}

const bool& Window::getMinimized() const {
	return _minimized;
}

const bool& Window::getQuit() const {
	return _quit;
}