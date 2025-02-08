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

	float x, y;
	float w, h;
	color_type color;
	SDL_Texture* texture;

	render_data() = default;

	render_data(float x, float y) : x(x), y(y) { 
		color = color_type(255, 255, 255, 255); 
		w = 20.f;
		h = 20.f;
		texture = nullptr;
	}
};