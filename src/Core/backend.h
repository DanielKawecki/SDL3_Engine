#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>

namespace BackEnd {

	void Initialize();
	void ForceCloseWindow();
	void CleanUp();

	SDL_Window* GetWindowPointer();
	bool IsWindowOpen();
	int GetScreenWidth();
	int GetScreenHeight();

}