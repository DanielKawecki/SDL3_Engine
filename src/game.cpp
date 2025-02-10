#include "game.h"
#include "player.h"
#include "scene.h"
#include "renderer.h"
#include "input.h"

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
	float _delta_time = 0.f;
	float _time = 0.f;

	float _accumulator = 0.f;
	int _fps = 0;

	void create() {
		
		_is_loaded = true;
		_player_count = 1;
		create_players(1);
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
		_delta_time = (current_time - _last_time) / _frequency;
		_last_time = current_time;
		_time += _delta_time;

		_accumulator += _delta_time;
		if (_accumulator >= 1.f) {
			_fps = (int)(1.f / _delta_time);
			_accumulator = 0.f;
		}

		// Tidy it up --------

		SDL_Color color = { 255, 255, 255, 255 };

		std::string text = "Mouse Pos: " 
			+ std::to_string(input::get_mouse_x()) + ", " 
			+ std::to_string(input::get_mouse_y());

		renderer::blit_text(text, 22, mth::vec2(10.f, 35.f), color);
		renderer::blit_text(std::to_string(_fps) + "fps", 22, mth::vec2(10.f, 10.f), color);
		renderer::blit_text("Angle: " + std::to_string(_players[0].get_angle()), 22, mth::vec2(10.f, 60.f), color);

		// -------------------

		for (int i = 0; i < _player_count; ++i) 
			_players[i].update(_delta_time);

		scene::update(_delta_time);
		scene::upload_render_data();
	}

	bool is_loaded() {
		return _is_loaded;
	}

}