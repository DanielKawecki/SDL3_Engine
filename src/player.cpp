#include "player.h"
#include "input.h"
#include "renderer.h"
#include "render_data.h"
#include "resource_manager.h"

#include <iostream>

player::player(int id) : _id(id) {}

void player::update(float delta_time) {
	
	update_movement(delta_time);
	update_frame();
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

	_position.x += displacement.x * delta_time;
	_position.y += displacement.y * delta_time;

	if (mth::length(displacement) == 0.f) _state = player_state::idle;
	else _state = player_state::walk;
}

void player::update_frame() {

	if (_state == player_state::idle) {
		_texture = resource_manager::get_texture_by_id(0);
	}
	else if (_state == player_state::walk) {
		_texture = resource_manager::get_texture_by_id(1);
	}
}

void player::upload_render_data() const {

	render_data data = render_data();

	data.rect.x = _position.x;
	data.rect.y = _position.y;
	data.rect.w = 50.f;
	data.rect.h = 50.f;
	data.color = SDL_Color(0, 255, 0, 255);
	data.texture = _texture;

	renderer::submit_render_data(data);
}

float player::get_x() const {
	return _position.x;
}

float player::get_y() const {
	return _position.y;
}
