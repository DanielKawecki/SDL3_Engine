#pragma once

#include "player.h"

namespace game {

	void create();
	void create_players(int count);
	player* get_player_by_id(int id);
	void update();

	bool is_loaded();
}