#pragma once

#include "../vec2.h"

namespace Input {

	void Update();
	bool IsKeyDown(int sdl_scancode);
	bool IsKeyPressed(int sdl_scancode);
	int GetMouseX();
	int GetMouseY();
	vec2 GetMousePos();
	bool MouseLeftDown();
	bool MouseMiddleDown();
	bool MouseRightDown();
	bool MouseLeftPressed();
	bool MouseMiddlePressed();
	bool MouseRightPressed();

}