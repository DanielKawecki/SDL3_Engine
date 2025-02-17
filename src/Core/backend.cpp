#include "backend.h"

namespace BackEnd {

	SDL_Window* _window = nullptr;

	int _screenWidth = 1280;
	int _screenHeight = 720;

	void Initialize() {

		if (!SDL_Init(SDL_INIT_VIDEO)) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return;
		}

		if (!TTF_Init()) {
			SDL_Log("Unable to initialize TTF: %s", SDL_GetError());
			return;
		}

		_window = SDL_CreateWindow("Apathy", _screenWidth, _screenHeight, NULL);

		if (!_window) {
			SDL_Log("Could not create window: %s", SDL_GetError());
			SDL_Quit();
			return;
		}
	}

	void ForceCloseWindow() {

		if (_window) {
			SDL_DestroyWindow(_window);
			_window = nullptr;
		}
	}

	void CleanUp() {

		SDL_Quit();
	}

	bool IsWindowOpen() {
		return _window != nullptr;
	}

	SDL_Window* GetWindowPointer() {
		return _window;
	}

	int GetScreenWidth() {
		return _screenWidth;
	}

	int GetScreenHeight() {
		return _screenHeight;
	}

}