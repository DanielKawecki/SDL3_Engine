#include "BackEnd.h"
//#include "renderer.h"
//#include "resource_manager.h"

#include <SDL3/SDL_ttf.h>

BackEnd::BackEnd() : _window(nullptr) {

	_screenWidth = 1280;
	_screenHeight = 720;
}

BackEnd::~BackEnd() {
	CleanUp();
}

void BackEnd::Initialize() {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}

	if (!TTF_Init()) {
		SDL_Log("Unable to initialize TTF: %s", SDL_GetError());
		return;
	}

	CreateWindow();

	if (!_window) {
		SDL_Log("Could not create window: %s", SDL_GetError());
		SDL_Quit();
		return;
	}

	//renderer::init();
	//resource_manager::init();
}

void BackEnd::CreateWindow() {
	_window = SDL_CreateWindow("SDL3 Engine", _screenWidth, _screenHeight, NULL);
}

bool BackEnd::IsWindowOpen() const {
	return _window != nullptr;
}

void BackEnd::ForceCloseWindow() {
	
	if (_window) {
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}
}

SDL_Window* BackEnd::GetWindowPointer() const {
	return _window;
}

void BackEnd::CleanUp() {
	//renderer::clean_up();
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

int BackEnd::GetScreenWidth() const {
	return _screenWidth;
}

int BackEnd::GetScreenHeight() const {
	return _screenHeight;
}
