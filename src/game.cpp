#include "game.h"
#include "player.h"
#include "scene.h"

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

namespace game {

	std::vector<player> _players;
	int _player_count;
	bool _is_loaded = false;
	bool _first_frame = true;

	Uint64 _last_time = SDL_GetPerformanceCounter();
	float _frequency = (float)SDL_GetPerformanceFrequency();
	float _time = 0.0;

	void create() {
		
		_is_loaded = true;
		_player_count = 1;
		create_players(1);

		/*for (int i = 0; i < 5; ++i) {
			scene::create_object(10.f + i * 100.f, 10.f);
		}*/
	}

	void create_players(int count) {
		
		_players.clear();

		for (int i = 0; i < count; ++i)
			_players.emplace_back(i);
	}

	player* get_player_by_id(int id) {
		return &_players[id];
	}

	void update() {

		// Delta time calculation
		Uint64 current_time = SDL_GetPerformanceCounter();
		float delta_time = (current_time - _last_time) / _frequency;
		_last_time = current_time;
		_time += delta_time;

		for (int i = 0; i < _player_count; ++i) 
			_players[i].update(delta_time);

		scene::update(delta_time);
		scene::upload_render_data();
	}

	bool is_loaded() {
		return _is_loaded;
	}

}