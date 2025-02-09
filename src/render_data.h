#pragma once

#include <SDL3/SDL.h>

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

	SDL_FRect rect;
	SDL_Color color;
	SDL_Texture* texture;
	bool is_text;

	render_data() {
	
		is_text = false;
		rect = SDL_FRect(0.f, 0.f, 10.f, 10.f);
		color = SDL_Color(255, 255, 255, 255);
		texture = nullptr;
	};

	render_data(SDL_FRect rect, SDL_Color color, SDL_Texture* texture, bool is_text = false) :
		rect(rect), color(color), texture(texture), is_text(is_text) {}
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