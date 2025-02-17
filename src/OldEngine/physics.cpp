#include "physics.h"

namespace physics {

	bool check_collision(const SDL_FRect& a, const SDL_FRect& b) {

		if (
			a.x + a.w >= b.x &&
			a.x <= b.x + b.w &&
			a.y + a.h >= b.y &&
			a.y <= b.y + b.h
			)
			return true;

		return false;
	}

}