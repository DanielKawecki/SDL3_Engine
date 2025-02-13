#pragma once

#include "game_object.h"

#include <vector>
#include <memory>

namespace scene {

	void update(float delta_time);
	void update_collision();
	void upload_render_data();

	void create_bullet(mth::vec2 position, mth::vec2 direction, float angle);
	void create_wall(mth::vec2 position);
	void create_enemy(mth::vec2 position);
	void remove_expired();
	void display_debug();
	size_t get_game_object_count();
}