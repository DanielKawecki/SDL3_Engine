#include "editor.h"
#include "../Core/input.h"
#include "../Game/scene.h"
#include "../Game/game.h"
#include "../UI/ui_backend.h"
#include <SDL3/SDL.h>

enum class Tool {
	WALL,
	ERASER
};

namespace Editor {

	Tool _tool = Tool::WALL;
	WallType _wallType = WallType::FRONT;

	void Update() {
		UpdateInupt();
		UpdateUI();
	}

	void UpdateInupt() {

		if (Input::IsKeyPressed(SDL_SCANCODE_Q)) _tool = Tool::WALL;
		if (Input::IsKeyPressed(SDL_SCANCODE_W)) _tool = Tool::ERASER;

		if (Input::MouseLeftPressed() && _tool == Tool::WALL) {
			Scene::AddWall(Input::GetMousePos(), _wallType);
		}
	}

	void UpdateUI() {
		
		std::string text = "Editor Mode";
		UIBackEnd::BlitText(text, 10.f, 10.f);

		if (_tool == Tool::WALL) {
			vec2 mousePos = Input::GetMousePos();
			UIBackEnd::BlitTexture("floor.png", mousePos.x, mousePos.y, 32.f, 32.f);
		}
	}

}

