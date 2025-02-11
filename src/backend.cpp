#include "backend.h"
#include "renderer.h"
#include "resource_manager.h"

#include <SDL3/SDL_ttf.h>

namespace backend {

	SDL_Window* _window = nullptr;
	bool _running = true;

	int _screen_width = 1280;
	int _screen_height = 720;

	void init() {

		if (!SDL_Init(SDL_INIT_VIDEO)) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return;
		}

		if (!TTF_Init()) {
			SDL_Log("Unable to initialize TTF: %s", SDL_GetError());
			return;
		}

		create_window();

		if (!_window) {
			SDL_Log("Could not create window: %s", SDL_GetError());
			SDL_Quit();
			return;
		}

		renderer::init();
		resource_manager::init();
	}

	void create_window() {
		_window = SDL_CreateWindow("SDL3 Engine", _screen_width, _screen_height, NULL);
	}

	bool is_window_open() {
		return _running;
	}

	void force_close_window() {
		_running = false;
	}

	SDL_Window* get_window_pointer() {
		return _window;
	}

	void clean_up() {

		SDL_DestroyWindow(_window);
		SDL_Quit();
		renderer::clean_up();
	}

	int get_screen_width() {
		return _screen_width;
	}

	int get_screen_height() {
		return _screen_height;
	}

}
