#include "engine.h"
#include "backend.h"
#include "input.h"
#include "asset_manager.h"
#include "../Renderer/renderer.h"
#include "../Game/game.h"
#include "../Game/scene.h"

#include <iostream>
#include <string>

namespace Engine {

	void Initialize() {

		std::cout << "Initilizing Systems...\n";
		BackEnd::Initialize();
		Renderer::Initialize();
		AssetManager::Initialize();

		if (!Game::IsLoaded()) {
			Game::Create();
		}
	}

	void Update() {

		Input::Update();
		Game::Update();
	}

	void Run() {

		Initialize();

		while (BackEnd::IsWindowOpen()) {

			Renderer::ClearRenderQueue();

			Update();

			Renderer::RenderFrame();
		}

		CleanUp();
	}

	void CleanUp() {
		
		std::cout << "Shutting Down Systems...\n";
		BackEnd::CleanUp();
		Renderer::CleanUp();
		AssetManager::CleanUp();
	}

}