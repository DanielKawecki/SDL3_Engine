#pragma once

#include "../vec2.h"
#include <SDL3/SDL.h>

struct Transform {
	vec2	position;
	float	rotation;
};

struct Motion {
	vec2 direction;
	vec2 velocity;
	float speed;
};

struct Collision {
	SDL_FRect	hitbox;
	bool		active;
};

struct Sprite {
	SDL_Texture*	texture;
	SDL_FRect		srcRect;
	SDL_FRect		dstRect;
	SDL_FlipMode	flip;
	float			sizeX;
	float			sizeY;
};

struct Animation {
	int		frameIndex;
	int		frameCount;
	float	frameTime;
	float	accumulator;
};