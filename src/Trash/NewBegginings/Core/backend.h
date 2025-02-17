#pragma once

#include <SDL3/SDL.h>

namespace backend {

	void init();
	void create_window();
	bool is_window_open();
	void force_close_window();
	SDL_Window* get_window_pointer();
	void clean_up();
	int get_screen_width();
	int get_screen_height();

}