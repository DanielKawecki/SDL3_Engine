#pragma once

namespace input {

	void update();
	bool is_key_down(int sdl_scancode);
	bool is_key_pressed(int sdl_scancode);
	int get_mouse_x();
	int get_mouse_y();
	bool mouse_left_down();
	bool mouse_middle_down();
	bool mouse_right_down();
	bool mouse_left_pressed();
	bool mouse_middle_pressed();
	bool mouse_right_pressed();

}