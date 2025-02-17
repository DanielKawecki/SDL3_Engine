#include "game.h"
#include "player.h"
#include "scene.h"
#include "../Renderer/renderer.h"
#include "../Core/input.h"
#include "../Utils/utils.h"

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
	float _target_fps = 180.f;
	float _frame_time = 1.f / _target_fps;
	float _delta_time = 0.f;
	float _time = 0.f;

	float _accumulator = 0.f;
	int _fps = 0;

	float _debug_mode = false;

	void create() {
		
		_is_loaded = true;
		_player_count = 1;
		create_players(1);

		scene::create_wall(mth::vec2(800.f, 350.f));
		scene::create_enemy(mth::vec2(700.f, 200.f));
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

		update_delta_time();
		update_events();

		for (int i = 0; i < _player_count; ++i) 
			_players[i].update(_delta_time);

		scene::update(_delta_time);

		if (_debug_mode) {

			display_debug_text();
			display_debug_lines();
		}
	}

	void update_events() {

		if (input::is_key_pressed(SDL_SCANCODE_F3)) _debug_mode = !_debug_mode;
	}

	void update_delta_time() {

		// Delta time calculation
		Uint64 current_time = SDL_GetPerformanceCounter();
		_delta_time = (current_time - _last_time) / _frequency;
		_last_time = current_time;
		_time += _delta_time;

		// Fps calculation
		_accumulator += _delta_time;
		if (_accumulator >= 1.f) {
			_fps = (int)(1.f / _delta_time);
			std::cout << _fps << "fps\n";
			_accumulator = 0.f;
		}

		// Frame rate limit
		if (_frame_time > _delta_time) {
			SDL_Delay((_frame_time - _delta_time) * 1000.f);
		}
	}

	void display_debug_text() {

		SDL_Color color = { 255, 255, 255, 255 };

		std::string text = "";
		text += std::to_string(_fps) + "fps\n";
		text += "Mouse Pos: " + std::to_string(input::get_mouse_x()) + ", " + std::to_string(input::get_mouse_y()) + "\n";
		text += "Angle: " + std::to_string(_players[0].get_angle()) + "\n";
		text += "Objects: " + std::to_string(scene::get_game_object_count()) + "\n";

		renderer::blit_text(text, 22, mth::vec2(10.f, 10.f), color);
	}

	void display_debug_lines() {

		float mouse_x = (float)input::get_mouse_x();
		float mouse_y = (float)input::get_mouse_y();

		float player_x = _players[0].get_x();
		float player_y = _players[0].get_y();

		renderer::draw_line(player_x, player_y, mouse_x, mouse_y);

		render_data data = render_data();

		data.dst_rect = _players[0].get_hitbox();
		data.filled = false;
		data.layer = 100;

		renderer::submit_render_data(data);

		scene::display_debug();
	}

	bool is_loaded() {
		return _is_loaded;
	}

}