#include "game.h"
#include "../vec2.h"
#include "../Renderer/renderer.h"
#include "../Core/asset_manager.h"
#include "../Core/input.h"
#include "../util.h"
#include "scene.h"

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
		Scene::CreatePlayer();
	}

	void Update() {

		UpdateDeltaTime();
		UpdateEvents();

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
		if (Input::IsKeyPressed(SDL_SCANCODE_SPACE)) {
			Scene::AddWall(Input::GetMousePos());
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
		//text += "Mouse Pos: " + std::to_string(Input::GetMouseX()) + ", " + std::to_string(Input::GetMouseY()) + "\n";

		Renderer::BlitText(text, 22, vec2(10.f), color, false);
	}

	void DisplayDebugLines() {

		// Grid
		/*float gridSize = 32.f;
		vec2 position = Input::GetMousePos();
		float posX = floor(position.x / gridSize) * gridSize;
		float posY = floor(position.y / gridSize) * gridSize;

		RenderData data;
		data.texture = AssetManager::GetTextureByName("grid.png");
		data.dstRect = { posX - 80.f, posY - 80.f, 160.f, 160.f };
		data.srcRect = { 0.f, 0.f, 160.f, 160.f };
		Renderer::SubmitRenderData(data);*/

		// Hitboxes and stuff
		Scene::DisplayDebug();
	}

	void DisplayConsole() {

		SDL_Color color = { 255, 255, 255, 255 };

		Renderer::BlitText(_command, 22, vec2(10.f, 680.f), color, true);
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
