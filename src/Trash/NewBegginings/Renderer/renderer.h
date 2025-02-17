#pragma once

#include "render_data.h"
#include "../Utils/mth.h"

#include <SDL3/SDL.h>
#include <string>

namespace renderer {

	void init();
	void clear_render_queue();
	void submit_render_data(render_data data);
	void render_frame();
	void clean_up();
	SDL_Renderer* get_renderer_pointer();
	//void test_textures();
	void blit_text(std::string text, int size, mth::vec2 loaction, SDL_Color color);
	void draw_line(float x1, float y1, float x2, float y2);

}