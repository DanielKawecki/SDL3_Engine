#pragma once

#include <SDL3/SDL.h>
#include "mth.h"

enum class player_state {
	idle,
	walk,
	attack
};

enum class player_facing {
	left,
	right
};

class player {
private:
	int				_id;
	int				_frame_index = 0;
	float			_speed = 250.f;
	float			_accumulator = 0.f;
	float			_frame_time = 0.08f;
	int				_frame_count = 10;
	bool			_busy = false;
	float			_angle = 0.f;
	mth::vec2		_position = mth::vec2(100.f, 100.f);
	mth::vec2		_mouse_direction = mth::vec2(0.f, 0.f);
	player_state	_state = player_state::idle;
	player_facing   _direction = player_facing::right;
	SDL_Texture*	_texture = nullptr;
	SDL_FRect		_hitbox = { 0.f, 0.f, 0.f, 0.f };

public:

	player(int id);

	void update(float delta_time);
	void update_movement(float delta_time);
	void update_frame(float delta_time);
	void update_mouse();
	void upload_render_data() const;
	//void shoot() const;

	float get_x() const;
	float get_y() const;
	float get_angle() const;
	const SDL_FRect& get_hitbox() const;
};