#pragma once

#include "render_data.h"

#include <SDL3/SDL.h>

namespace renderer {

	void init();
	void clear_render_queue();
	void submit_render_data(render_data data);
	void render_frame();
	void clean_up();
	SDL_Renderer* get_renderer_pointer();

}