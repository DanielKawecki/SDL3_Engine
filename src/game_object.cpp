#include "game_object.h"

#include <iostream>

bullet::bullet(mth::vec2 position, mth::vec2 direction) {

	_position = position;
	_displacement = direction * _speed;
}

void bullet::update(float delta_time) {

	_position.x += _displacement.x * delta_time;
	_position.y += _displacement.y * delta_time;
}

render_data bullet::create_render_data() const {

	render_data data = render_data();
	
	data.dst_rect = { _position.x, _position.y, 100.f, 100.f };
	data.color = { 255, 255, 255, 255 };
	
	return data;
}

void game_object::update(float delta_time) {

}

render_data game_object::create_render_data() const {
	return render_data();
}
