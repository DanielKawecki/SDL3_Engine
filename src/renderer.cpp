#include "renderer.h"
#include "backend.h"
#include "game.h"
#include "scene.h"

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

namespace renderer {

	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

	std::vector<render_data> _render_queue;

	void init() {

		_window = backend::get_window_pointer();
		_renderer = SDL_CreateRenderer(_window, NULL);
	}

	void clear_render_queue() {
		_render_queue.clear();
	}

	void submit_render_data(render_data data) {
		_render_queue.push_back(std::move(data));
	}

	void render_frame() {

		SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
		SDL_RenderClear(_renderer);

		for (const render_data& obj : _render_queue) {

			SDL_FRect rect = { obj.x, obj.y, obj.w, obj.h };
			color_type c = obj.color;

			SDL_SetRenderDrawColor(_renderer, c.red, c.green, c.blue, c.alpha);
			SDL_RenderFillRect(_renderer, &rect);
			SDL_RenderRect(_renderer, &rect);
		}

		SDL_RenderPresent(_renderer);
	}

	void clean_up() {
		SDL_DestroyRenderer(_renderer);
	}

}