#include "player.h"
#include "input.h"
#include "mth.h"
#include "renderer.h"
#include "render_data.h"

#include <SDL3/SDL.h>
#include <iostream>

player::player(int id) : _id(id) {
	_x = 100.f;
	_y = 100.f;
}

void player::update(float delta_time) {
	
	update_movement(delta_time);
	upload_render_data();
}

void player::update_movement(float delta_time) {

	mth::vec2 direction(0.f, 0.f);

	if (input::is_key_down(SDL_SCANCODE_W)) {
		direction.y -= 1.f;
	}
	if (input::is_key_down(SDL_SCANCODE_S)) {
		direction.y += 1.f;
	}
	if (input::is_key_down(SDL_SCANCODE_A)) {
		direction.x -= 1.f;
	}
	if (input::is_key_down(SDL_SCANCODE_D)) {
		direction.x += 1.f;
	}

	mth::vec2 displacement = mth::normalize(direction) * _speed;

	_x += displacement.x * delta_time;
	_y += displacement.y * delta_time;
}

void player::upload_render_data() const {

	render_data data = render_data();
	data.x = _x;
	data.y = _y;
	data.w = 50.f;
	data.h = 50.f;
	data.color = color_type(0, 255, 0, 255);

	renderer::submit_render_data(data);
}

float player::get_x() const {
	return _x;
}

float player::get_y() const {
	return _y;
}
