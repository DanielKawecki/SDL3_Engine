#include "game_object.h"
#include "resource_manager.h"

#include <iostream>

bullet::bullet(mth::vec2 position, mth::vec2 direction, float angle) {

	_remove = false;
	_position = position;
	_displacement = direction * _speed;
	_texture = resource_manager::get_texture_by_name("bullet.png");
	_angle = angle;
	_animation.frame_count = 4;
	_animation.frame_size_x = 32.f;
	_animation.frame_size_y = 16.f;
}

void bullet::update(float delta_time) {

	if (_life_time > 0.f) {

		_position.x += _displacement.x * delta_time;
		_position.y += _displacement.y * delta_time;

		_dst_rect = { _position.x - 32.f, _position.y - 16.f, 64.f, 32.f };
		_life_time -= delta_time;

		_accumulator += delta_time;
		if (_accumulator >= _animation.frame_time) {
			_animation.frame_index = (_animation.frame_index + 1) % _animation.frame_count;
			_accumulator = 0.f;
		}
	}

	else if (_explode || _life_time <= 0.f && _animation.frame_index < _animation.frame_count) {

		// This repeats every frame: Deal with that
		_animation.frame_size_x = 64.f;
		_animation.frame_size_y = 64.f;
		_animation.frame_count = 10.f;

		_texture = resource_manager::get_texture_by_name("smoke.png");
		_dst_rect = { _position.x - 40.f, _position.y - 40.f, 80.f, 80.f };

		_accumulator += delta_time;
		if (_accumulator >= _animation.frame_time) {
			++_animation.frame_index;
			_accumulator = 0.f;
		}
	}

	else _remove = true;
}

render_data bullet::create_render_data() const {

	render_data data = render_data();
	
	data.src_rect = { _animation.frame_size_x * _animation.frame_index, 0.f, _animation.frame_size_x, _animation.frame_size_y };
	data.rotation = _angle;
	data.dst_rect = _dst_rect;
	data.texture = _texture;
	data.filled = false;
	
	return data;
}

void game_object::update(float delta_time) {

}

render_data game_object::create_render_data() const {
	return render_data();
}

bool game_object::get_remove() const {
	return _remove;
}
