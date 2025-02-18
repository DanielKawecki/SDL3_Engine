#include "input.h"
#include "backend.h"

#include <SDL3/SDL.h>
#include <iostream>

namespace Input {

	bool _keyDown[232];
	bool _keyPressed[232];
	bool _keyDownLastFrame[232];

	float _mouseX = 0.f;
	float _mouseY = 0.f;
	float _mouseOffsetX = 0.f;
	float _mouseOffsetY = 0.f;

	bool _mouseLeftDown = false;
	bool _mouseMiddleDown = false;
	bool _mouseRightDown = false;

	bool _mouseLeftPressed = false;
	bool _mouseMiddlePressed = false;
	bool _mouseRightPressed = false;

	bool _mouseLeftDownLastFrame = false;
	bool _mouseMiddleDownLastFrame = false;
	bool _mouseRightDownLastFrame = false;

	void Update() {

		// Event polling

		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				BackEnd::ForceCloseWindow();
			}
		}

		// Keyboard check

		const bool* keyboardState = SDL_GetKeyboardState(NULL);

		for (int i = 4; i <= 231; ++i) {

			if (keyboardState[i]) {
				_keyDown[i] = true;
			}
			else {
				_keyDown[i] = false;
			}

			if (keyboardState[i] && !_keyDownLastFrame[i]) {
				_keyPressed[i] = true;
			}
			else {
				_keyPressed[i] = false;
			}

			_keyDownLastFrame[i] = _keyDown[i];
		}

		// Force close window

		if (keyboardState[SDL_SCANCODE_ESCAPE]) {
			BackEnd::ForceCloseWindow();
		}

		// Mouse check

		float x, y;

		Uint32 mouseFlags = SDL_GetMouseState(&x, &y);

		_mouseOffsetX = x - _mouseX;
		_mouseOffsetY = y - _mouseY;

		_mouseX = x;
		_mouseY = y;

		// Mouse buttons down

		if (mouseFlags & SDL_BUTTON_LMASK) _mouseLeftDown = true;
		else _mouseLeftDown = false;

		if (mouseFlags & SDL_BUTTON_MMASK) _mouseMiddleDown = true;
		else _mouseMiddleDown = false;

		if (mouseFlags & SDL_BUTTON_RMASK) _mouseRightDown = true;
		else _mouseRightDown = false;

		// Mouse buttons pressed

		if (mouseFlags & SDL_BUTTON_LMASK && !_mouseLeftDownLastFrame)
			_mouseLeftPressed = true;
		else
			_mouseLeftPressed = false;

		if (mouseFlags & SDL_BUTTON_MMASK && !_mouseMiddleDownLastFrame)
			_mouseMiddleDown = true;
		else
			_mouseMiddleDown = false;

		if (mouseFlags & SDL_BUTTON_RMASK && !_mouseRightDownLastFrame)
			_mouseRightDown = true;
		else
			_mouseRightDown = false;

		_mouseLeftDownLastFrame = _mouseLeftDown;
		_mouseMiddleDownLastFrame = _mouseMiddleDown;
		_mouseRightDownLastFrame = _mouseRightDown;
	}

	bool IsKeyDown(int sdl_scancode) {
		return _keyDown[sdl_scancode];
	}

	bool IsKeyPressed(int sdl_scancode) {
		return _keyPressed[sdl_scancode];
	}

	int GetMouseX() {
		return (int)_mouseX;
	}

	int GetMouseY() {
		return (int)_mouseY;
	}

	vec2 GetMousePos() {
		return vec2(_mouseX, _mouseY);
	}

	bool MouseLeftDown() {
		return _mouseLeftDown;
	}

	bool MouseMiddleDown() {
		return _mouseMiddleDown;
	}

	bool MouseRightDown() {
		return _mouseRightDown;
	}

	bool MouseLeftPressed() {
		return _mouseLeftPressed;
	}

	bool MouseMiddlePressed() {
		return _mouseMiddlePressed;
	}

	bool MouseRightPressed() {
		return _mouseRightPressed;
	}

}