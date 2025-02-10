#include "player.h"
#include "input.h"
#include "renderer.h"
#include "render_data.h"
#include "resource_manager.h"
#include "scene.h"

#include <iostream>
#include <cmath>

player::player(int id) : _id(id) {}

void player::update(float delta_time) {
	
	update_movement(delta_time);
	update_frame(delta_time);
	update_mouse();
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

	if (displacement.x > 0.f && !_busy) _direction = player_facing::right;
	else if (displacement.x < 0.f && !_busy) _direction = player_facing::left;
}

void player::update_frame(float delta_time) {

	_accumulator += delta_time;

	if (_accumulator >= _frame_time) {
		
		_accumulator = 0.f;
		_frame_index = (_frame_index + 1) % _frame_count;

		if (_state == player_state::attack && _frame_index == 4) {
			
			_state = player_state::idle;
			_frame_index = 0;
			_busy = false;
		}
	}

	if (_state == player_state::idle) {
		_texture = resource_manager::get_texture_by_name("_Idle.png");
	}
	else if (_state == player_state::walk) {
		_texture = resource_manager::get_texture_by_name("_Run.png");
	}
	else if (_state == player_state::attack) {
		_texture = resource_manager::get_texture_by_name("_Attack.png");
	}
}

void player::update_mouse() {

	int mouse_x = input::get_mouse_x();
	int mouse_y = input::get_mouse_y();

	float diff_x = (float)mouse_x - _position.x;
	float diff_y = (float)mouse_y - _position.y;

	_angle = atan2f(diff_y, diff_x) * (180.f / M_PI);

	renderer::draw_line(_position.x, _position.y, mouse_x, mouse_y);

	if (input::is_key_pressed(SDL_SCANCODE_L)) {

		mth::vec2 mouse_direction = mth::normalize(mth::vec2(diff_x, diff_y));
		scene::create_bullet(_position, mouse_direction);
	}
}

void player::upload_render_data() const {

	render_data data = render_data();
	
	data.src_rect = { 120.f * _frame_index, 0.f, 120.f, 80.f };
	data.dst_rect = { _position.x - 180.f, _position.y - 140.f, 120.f * 3.f, 80.f * 3.f };
	data.texture = _texture;

	if (_direction == player_facing::left) data.flip = SDL_FLIP_HORIZONTAL;

	renderer::submit_render_data(data);
}

float player::get_x() const {
	return _position.x;
}

float player::get_y() const {
	return _position.y;
}

float player::get_angle() const {
	return _angle;
}
