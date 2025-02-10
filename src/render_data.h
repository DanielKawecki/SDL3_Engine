#pragma once

#include <SDL3/SDL.h>

struct line_struct {
	
	float x1, y1, x2, y2;
	line_struct() = default;
};

struct color_type {

	int red;
	int green;
	int blue;
	int alpha;

	color_type() = default;

	color_type(int red, int green, int blue, int alpha) :
		red(red), green(green), blue(blue), alpha(alpha) {}
};

struct render_data {

	SDL_FRect		src_rect;
	SDL_FRect		dst_rect;
	SDL_Color		color;
	SDL_Texture*	texture;
	SDL_FlipMode	flip;
	float			rotation;
	bool			is_text;
	bool			use_src_rect;

	render_data() {
	
		is_text = false;
		use_src_rect = false;
		flip = SDL_FLIP_NONE;
		rotation = 0.f;
		src_rect = SDL_FRect(0.f, 0.f, 10.f, 10.f);
		dst_rect = SDL_FRect(0.f, 0.f, 10.f, 10.f);
		color = SDL_Color(255, 255, 255, 255);
		texture = nullptr;
	};

	/*render_data(SDL_FRect src_rect, SDL_FRect dst_rect, SDL_Color color, SDL_Texture* texture, bool is_text = false) :
		src_rect(src_rect), dst_rect(dst_rect), color(color), texture(texture), is_text(is_text) {}*/
};

//struct render_data {
//
//	float x, y;
//	float w, h;
//	SDL_FRect rect;
//	SDL_Color color;
//	SDL_Texture* texture;
//
//	render_data() = default;
//
//	render_data(float x, float y) : x(x), y(y) {
//		color = SDL_Color(255, 255, 255, 255);
//		w = 20.f;
//		h = 20.f;
//		texture = nullptr;
//	}
//};