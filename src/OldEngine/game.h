#pragma once

#include "player.h"

namespace game {

	void create();
	void create_players(int count);
	player* get_player_by_id(int id);
	void update();
	void update_events();
	void update_delta_time();
	void display_debug_text();
	void display_debug_lines();
	bool is_loaded();
}