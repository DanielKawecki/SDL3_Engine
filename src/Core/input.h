#pragma once

namespace Input {

	void Update();
	bool IsKeyDown(int sdl_scancode);
	bool IsKeyPressed(int sdl_scancode);
	int GetMouseX();
	int GetMouseY();
	bool MouseLeftDown();
	bool MouseMiddleDown();
	bool MouseRightDown();
	bool MouseLeftPressed();
	bool MouseMiddlePressed();
	bool MouseRightPressed();

}