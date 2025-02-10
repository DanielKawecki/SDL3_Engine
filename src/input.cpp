#include "input.h"
#include "backend.h"

#include <SDL3/SDL.h>
#include <iostream>

namespace input {

	bool _key_down[232];
	bool _key_pressed[232];
	bool _key_down_last_frame[232];

	float _mouse_x = 0.f;
	float _mouse_y = 0.f;
	float _mouse_offset_x = 0.f;
	float _mouse_offset_y = 0.f;

	void update() {

		// Event polling

		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				backend::force_close_window();
			}
		}

		// Keyboard check

		const bool* keyboard_state = SDL_GetKeyboardState(NULL);

		for (int i = 4; i <= 231; ++i) {

			if (keyboard_state[i]) {
				_key_down[i] = true;
			}
			else {
				_key_down[i] = false;
			}

			if (keyboard_state[i] && !_key_down_last_frame[i]) {
				_key_pressed[i] = true;
			}
			else {
				_key_pressed[i] = false;
			}

			_key_down_last_frame[i] = _key_down[i];
		}

		// Force close window

		if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
			backend::force_close_window();
		}

		// Mouse check

		float x, y;

		SDL_GetMouseState(&x, &y);

		_mouse_offset_x = x - _mouse_x;
		_mouse_offset_y = y - _mouse_y;

		_mouse_x = x;
		_mouse_y = y;
	}

	bool is_key_down(int sdl_scancode) {
		return _key_down[sdl_scancode];
	}

	bool is_key_pressed(int sdl_scancode) {
		return _key_pressed[sdl_scancode];
	}

	int get_mouse_x() {
		return (int)_mouse_x;
	}

	int get_mouse_y() {
		return (int)_mouse_y;
	}

}