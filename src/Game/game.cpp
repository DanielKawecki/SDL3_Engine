#include "game.h"
#include "scene.h"
#include "../vec2.h"
#include "../Renderer/renderer.h"
#include "../Core/asset_manager.h"
#include "../Core/input.h"
#include "../util.h"
#include "../Player/player.h"
#include "../UI/ui_backend.h"
#include "../Editor/editor.h"

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

namespace Game {

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
	bool _editMode = false;

	void Create() {
		
		_isLoaded = true;
		Scene::CreatePlayer();
		//Scene::CreateMap();
	}

	void Update() {

		UpdateDeltaTime();
		UpdateEvents();

		Scene::Update(_deltaTime);
	
		if (_debugMode) DisplayDebugText();
		if (_editMode) Editor::Update();
	}

	void UpdateEvents() {

		if (Input::IsKeyPressed(SDL_SCANCODE_F3)) _debugMode = !_debugMode;
		if (Input::IsKeyPressed(SDL_SCANCODE_F4)) _editMode = !_editMode;
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

		//std::string text = std::to_string(_fps) + "fps\n";
		//UIBackEnd::BlitText(text, 10.f, 10.f);
	}

	//void DisplayDebugLines() {

	//	// Grid
	//	/*float gridSize = 32.f;
	//	vec2 position = Input::GetMousePos();
	//	float posX = floor(position.x / gridSize) * gridSize;
	//	float posY = floor(position.y / gridSize) * gridSize;

	//	RenderData data;
	//	data.texture = AssetManager::GetTextureByName("grid.png");
	//	data.dstRect = { posX - 80.f, posY - 80.f, 160.f, 160.f };
	//	data.srcRect = { 0.f, 0.f, 160.f, 160.f };
	//	Renderer::SubmitRenderData(data);*/

	//	// Hitboxes and stuff
	//	Scene::DisplayDebug();
	//}

	bool IsLoaded() {
		return _isLoaded;
	}

	bool IsDebugVisible() {
		return _debugMode;
	}

	bool IsEditorOpen() {
		return _editMode;
	}

}
