#pragma once

#include <SDL3/SDL.h>

namespace physics {

	bool check_collision(const SDL_FRect& a, const SDL_FRect& b);

}