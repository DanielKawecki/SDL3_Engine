#include "game_object.h"
#include "../Core/resource_manager.h"
#include "../Core/physics.h"
#include "../Core/backend.h"

#include <iostream>

// ------------------------------------------
//				Wall
// ------------------------------------------

wall::wall(mth::vec2 position) {

	_angle = 0.f;
	_remove = false;
	_position = position;
	_src_rect = { 16.f, 208.f, 16.f, 16.f };
	_hitbox = { _position.x, _position.y, 64.f, 64.f };
	_dst_rect = _hitbox;
	_texture = resource_manager::get_texture_by_name("walls.png");
}

void wall::update(float delta_time) {

}

bool wall::is_wall() const {
	return true;
}

// ------------------------------------------
//				Projectile
// ------------------------------------------

projectile::projectile(mth::vec2 position, mth::vec2 direction, float angle) {

	_remove = false;
	_active = true;
	_position = position;
	_displacement = direction * _speed;
	_texture = resource_manager::get_texture_by_name("bullet.png");
	_angle = angle;
	_animation.frame_count = 4;
	_animation.frame_size_x = 32.f;
	_animation.frame_size_y = 16.f;
	_hitbox = { _position.x - 8.f, _position.y - 8.f, 16.f, 16.f };
	_dst_rect = { 10.f, 10.f, 10.f, 10.f };
	_src_rect = { 0.f, 0.f, _animation.frame_size_x, _animation.frame_size_y };
}

void projectile::update(float delta_time) {

	if (
		_position.x >= backend::get_screen_width() ||
		_position.x <= 0.f ||
		_position.y >= backend::get_screen_height() ||
		_position.y <= 0.f 
		) 
		_explode = true;

	if (_life_time <= 0.f) _explode = true;

	update_animation(delta_time);

	if (_explode != _prev_explode) {

		_animation.frame_size_x = 64.f;
		_animation.frame_size_y = 64.f;
		_animation.frame_count = 10;
		_animation.frame_index = 0;

		_texture = resource_manager::get_texture_by_name("smoke.png");
		_dst_rect = { _position.x - 40.f, _position.y - 40.f, 80.f, 80.f };
	} 

	if (!_explode) {

		_position.x += _displacement.x * delta_time;
		_position.y += _displacement.y * delta_time;

		_dst_rect = { _position.x - 32.f, _position.y - 16.f, 64.f, 32.f };
		_hitbox = { _position.x - 8.f, _position.y - 8.f, 16.f, 16.f };
		_life_time -= delta_time;
	}

	else if (_explode && _animation.frame_index == _animation.frame_count - 1) {
		
		_remove = true;
	}

	_prev_explode = _explode;
}

void projectile::collision() {
	_explode = true;
}

bool projectile::is_projectile() const {
	return true;
}

// ------------------------------------------
//				Enemy
// ------------------------------------------

enemy::enemy(mth::vec2 position) {

	_angle = 0.f;
	_remove = false;
	_texture = resource_manager::get_texture_by_name("enemy_walk.png");
	_position = position;
	_animation.frame_count = 4;
	_animation.frame_size_x = 150.f;
	_animation.frame_size_y = 150.f;
	_animation.frame_time = 0.15f;
	_src_rect = { 0.f, 0.f, _animation.frame_size_x, _animation.frame_size_y };
	_hitbox = { _position.x, _position.y, 50.f, 80.f };
	_dst_rect = { _position.x - 120.f, _position.y - 80.f, 256.f, 256.f };
	_flip = SDL_FLIP_HORIZONTAL;
}

void enemy::update(float delta_time) {

	mth::vec2 displacement = mth::vec2(-1.f, 0.3f);
	displacement = mth::normalize(displacement) * 100.f;

	_position.x += displacement.x * delta_time;
	_position.y += displacement.y * delta_time;

	_hitbox.x = _position.x;
	_hitbox.y = _position.y;

	_dst_rect.x = _position.x - 120.f;
	_dst_rect.y = _position.y - 80.f;

	if (_health > 0) {
	
		update_animation(delta_time);
	}
	else _remove = true;
}

void enemy::collision() {

}

void enemy::damage() {
	_health -= 50;
}

bool enemy::is_enemy() const {
	return true;
}

// ------------------------------------------
//				Game Object
// ------------------------------------------

game_object::game_object() {
	
	_position = mth::vec2(0.f, 0.f);
	_hitbox = { 0.f, 0.f, 0.f, 0.f };
	_src_rect = { 0.f, 0.f, 0.f, 0.f };
	_dst_rect = { 0.f, 0.f, 0.f, 0.f };
	_texture = nullptr;
	_angle = 0.f;
	_remove = false;
	_active = true;
	_animation = animation_info();
	_accumulator = 0.f;
	_flip = SDL_FLIP_NONE;
}

void game_object::update(float delta_time) {

}

void game_object::collision() {

}

void game_object::damage() {

}

void game_object::update_animation(float delta_time) {

	_src_rect.x = _animation.frame_size_x * _animation.frame_index;
	_src_rect.w = _animation.frame_size_x;
	_src_rect.h = _animation.frame_size_y;

	_accumulator += delta_time;
	if (_accumulator >= _animation.frame_time) {
		_animation.frame_index = (_animation.frame_index + 1) % _animation.frame_count;
		_accumulator = 0.f;
	}
}

render_data game_object::create_render_data() const {
	
	render_data data = render_data();

	data.texture = _texture;
	data.src_rect = _src_rect;
	data.rotation = _angle;
	data.dst_rect = _dst_rect;
	data.flip = _flip;

	return data;
}

bool game_object::get_remove() const {
	return _remove;
}

bool game_object::is_wall() const {
	return false;
}

bool game_object::is_projectile() const {
	return false;
}

bool game_object::is_enemy() const {
	return false;
}
