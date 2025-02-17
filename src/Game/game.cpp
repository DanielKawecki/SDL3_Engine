#include "game.h"
//#include "player.h"
//#include "scene.h"
#include "../vec2.h"
#include "../Renderer/renderer.h"
#include "../Core/input.h"
#include "scene.h"
//#include "utils.h"

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

namespace Game {

	//std::vector<player> _players;
	//int _player_count;
	bool _isLoaded = false;
	bool _firstFrame = true;

	Uint64 _lastTime = SDL_GetPerformanceCounter();
	float _frequency = (float)SDL_GetPerformanceFrequency();
	float _targetFps = 180.f;
	float _frameTime = 1.f / _targetFps;
	float _deltaTime = 0.f;
	float _time = 0.f;

	float _accumulator = 0.f;
	int _fps = 0;

	bool _debugMode = false;
	bool _console = false;
	std::string _command = "";

	void Create() {
		
		_isLoaded = true;
		//_player_count = 1;
		//create_players(1);

		//scene::create_wall(mth::vec2(800.f, 350.f));
		//scene::create_enemy(mth::vec2(700.f, 200.f));
		Scene::CreatePlayer();
		Scene::AddProjectile(vec2(100.f, 400.f), vec2(1.f, 0.f), 0.f);
	}

	/*void create_players(int count) {
		
		_players.clear();

		for (int i = 0; i < count; ++i)
			_players.emplace_back(i);
	}*/

	/*player* get_player_by_id(int id) {
		return &_players[id];
	}*/

	void Update() {

		UpdateDeltaTime();
		UpdateEvents();

		/*for (int i = 0; i < _player_count; ++i) 
			_players[i].update(_deltaTime);*/

		Scene::Update(_deltaTime);

		if (_debugMode) {

			DisplayDebugText();
			DisplayDebugLines();
		}

		if (_console) {

			UpdateConsole();
			DisplayConsole();
		}
	}

	void UpdateEvents() {

		if (Input::IsKeyPressed(SDL_SCANCODE_F3)) _debugMode = !_debugMode;
		if (Input::IsKeyPressed(SDL_SCANCODE_SLASH)) {
			_console = true;
			_command = "/";
		}
	}

	void UpdateDeltaTime() {

		// Delta time calculation
		Uint64 current_time = SDL_GetPerformanceCounter();
		_deltaTime = (current_time - _lastTime) / _frequency;
		_lastTime = current_time;
		_time += _deltaTime;

		// Fps calculation
		_accumulator += _deltaTime;
		if (_accumulator >= 1.f) {
			_fps = (int)(1.f / _deltaTime);
			//std::cout << _fps << "fps\n";
			_accumulator = 0.f;
		}

		// Frame rate limit
		if (_frameTime > _deltaTime) {
			SDL_Delay((_frameTime - _deltaTime) * 1000.f);
		}
	}

	void DisplayDebugText() {

		SDL_Color color = { 255, 255, 255, 255 };

		std::string text = "";
		text += std::to_string(_fps) + "fps\n";
		text += "Mouse Pos: " + std::to_string(Input::GetMouseX()) + ", " + std::to_string(Input::GetMouseY()) + "\n";
		//text += "Angle: " + std::to_string(_players[0].get_angle()) + "\n";
		//text += "Objects: " + std::to_string(scene::get_game_object_count()) + "\n";

		Renderer::BlitText(text, 22, mth::vec2(10.f, 10.f), color, false);
	}

	void DisplayDebugLines() {

		//float mouse_x = (float)input::get_mouse_x();
		//float mouse_y = (float)input::get_mouse_y();

		//float player_x = _players[0].get_x();
		//float player_y = _players[0].get_y();

		//renderer::draw_line(player_x, player_y, mouse_x, mouse_y);

		//Player* player = Scene::GetPlayer();

		//RenderData data = RenderData();

		////data.dstRect = player;
		//data.filled = false;
		//data.layer = 100;

		//Renderer::SubmitRenderData(data);

		Scene::DisplayDebug();
	}

	void DisplayConsole() {

		SDL_Color color = { 255, 255, 255, 255 };

		Renderer::BlitText(_command, 22, mth::vec2(10.f, 680.f), color, true);
	}

	void UpdateConsole() {

		if (Input::IsKeyPressed(SDL_SCANCODE_Q)) _console = !_console;

		if (Input::IsKeyPressed(SDL_SCANCODE_A)) _command += "a";
		if (Input::IsKeyPressed(SDL_SCANCODE_B)) _command += "b";
		if (Input::IsKeyPressed(SDL_SCANCODE_C)) _command += "c";
		if (Input::IsKeyPressed(SDL_SCANCODE_D)) _command += "d";

		if (Input::IsKeyPressed(SDL_SCANCODE_KP_ENTER)) {
			_console = false;
		}
	}

	bool IsLoaded() {
		return _isLoaded;
	}

}
