#pragma once

#include <SDL3/SDL.h>
#include "mth.h"

enum class player_state {
	idle,
	walk
};

class player {
private:
	int				_id;
	float			_speed = 200.f;
	mth::vec2		_position = mth::vec2(100.f, 100.f);
	player_state	_state = player_state::idle;
	SDL_Texture*	_texture = nullptr;

public:

	player(int id);

	void update(float delta_time);
	void update_movement(float delta_time);
	void update_frame();
	void upload_render_data() const;

	float get_x() const;
	float get_y() const;
};