#include "renderer.h"
#include "backend.h"
#include "game.h"
#include "scene.h"
#include "resource_manager.h"

#include <SDL3/SDL_ttf.h>

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
			SDL_Color color = obj.color;

			if (obj.texture) {
				SDL_RenderTexture(_renderer, obj.texture, NULL, &rect);
			}
			else {
				SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
				SDL_RenderFillRect(_renderer, &rect);
				SDL_RenderRect(_renderer, &rect);
			}
		}

		SDL_RenderPresent(_renderer);
	}

	void clean_up() {
		SDL_DestroyRenderer(_renderer);
	}

	SDL_Renderer* get_renderer_pointer() {
		return _renderer;
	}

	void test_textures() {

		for (int i = 0; i < 10; ++i) {

			SDL_FRect rect = { 50.f + i * 100.f, 50.f, 50.f, 50.f };
			SDL_Texture* texture = resource_manager::get_texture_by_id(i);

			if (texture) {
				SDL_RenderTexture(_renderer, texture, NULL, &rect);
			}
		}
	
		//SDL_RenderPresent(_renderer);
	}

	void blit_text(std::string text, int size, mth::vec2 location, SDL_Color color) {

		TTF_Font* font = resource_manager::get_font(size);
		SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text.size(), color);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_DestroySurface(surface);

		if (!texture) std::cout << "failed to render font\n";

		else {
			render_data data = render_data();
	
			data.x = location.x;
			data.y = location.y;
			data.w = texture->w;
			data.h = texture->h;
			data.texture = texture;

			submit_render_data(data);
		}
	}

}