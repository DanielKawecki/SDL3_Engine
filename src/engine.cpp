#include "engine.h"
#include "backend.h"
#include "input.h"
#include "game.h"
#include "renderer.h"

#include <SDL3/SDL.h>
#include <iostream>

void engine::run() {

	backend::init();

	if (!game::is_loaded()) 
		game::create();

	while (backend::is_window_open()) {
		
		renderer::clear_render_queue();

		input::update();

		game::update();

		renderer::render_frame();

	}

	backend::clean_up();
}
