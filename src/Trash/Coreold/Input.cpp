
#include "Input.h"

#include <SDL3/SDL.h>
#include <iostream>

Input::Input() : _forceCloseWindow(false) {}

Input::~Input() {}

void Input::Update() {

	// Event polling

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			//backend::force_close_window();
		}
	}

	// Keyboard check

	const bool* keyboard_state = SDL_GetKeyboardState(NULL);

	for (int i = 4; i <= 231; ++i) {

		if (keyboard_state[i]) {
			_keyDown[i] = true;
		}
		else {
			_keyDown[i] = false;
		}

		if (keyboard_state[i] && !_keyDownLastFrame[i]) {
			_keyPressed[i] = true;
		}
		else {
			_keyPressed[i] = false;
		}

		_keyDownLastFrame[i] = _keyDown[i];
	}

	// Force close window

	if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
		//backend::force_close_window();
	}
}

bool Input::IsKeyDown(int sdlScancode) const {
	return _keyDown[sdlScancode];
}

bool Input::IsKeyPressed(int sdlScancode) const {
	return _keyPressed[sdlScancode];
}

bool Input::ForceCloseWindow() const {
	return _forceCloseWindow;
}
