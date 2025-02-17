#pragma once

#include <SDL3/SDL.h>

struct Line {
	
	float x1, y1, x2, y2;
	Line() = default;
};

struct AnimationInfo {

	int		frame_index;
	int		frame_count;
	float	frame_time;
	float	frame_size_x;
	float	frame_size_y;

	AnimationInfo() {

		frame_index = 0;
		frame_count = 1;
		frame_time = 0.05f;
		frame_size_x = 32.f;
		frame_size_y = 32.f;
	}
};

struct RenderData {

	SDL_FRect		srcRect;
	SDL_FRect		dstRect;
	SDL_Color		color;
	SDL_Texture*	texture;
	SDL_FlipMode	flip;
	float			rotation;
	bool			isText;
	bool			useSrcRect;
	bool			filled;
	int				layer;

	RenderData() {
	
		isText = false;
		useSrcRect = false;
		filled = true;
		flip = SDL_FLIP_NONE;
		rotation = 0.f;
		srcRect = SDL_FRect(0.f, 0.f, 10.f, 10.f);
		dstRect = SDL_FRect(0.f, 0.f, 10.f, 10.f);
		color = SDL_Color(255, 255, 255, 255);
		texture = nullptr;
		layer = 1;
	};

};
