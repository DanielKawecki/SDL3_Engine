#include "renderer.h"
#include "backend.h"
#include "game.h"
#include "scene.h"
#include "resource_manager.h"

#include <SDL3/SDL_ttf.h>

#include <vector>
#include <iostream>
#include <algorithm>

namespace renderer {

	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

	std::vector<render_data> _render_queue;
	std::vector<line_struct> _lines;

	void init() {

		_window = backend::get_window_pointer();
		_renderer = SDL_CreateRenderer(_window, NULL);
	}

	void clear_render_queue() {
		_render_queue.clear();
		_lines.clear();
	}

	void submit_render_data(render_data data) {
		_render_queue.push_back(std::move(data));
	}

	void render_frame() {

		//std::sort(_render_queue.begin(), _render_queue.end(), [](const render_data& a, const render_data& b) { a.layer > b.layer; });

		SDL_SetRenderDrawColor(_renderer, 92, 86, 69, 255);
		SDL_RenderClear(_renderer);

		for (const render_data& obj : _render_queue) {

			SDL_FRect src_rect = obj.src_rect;
			SDL_FRect dst_rect = obj.dst_rect;
			SDL_Color color = obj.color;

			if (obj.texture) {
				SDL_RenderTextureRotated(_renderer, obj.texture, &src_rect, &dst_rect, (double)obj.rotation, nullptr, obj.flip);
			}
			else if (obj.texture && obj.rotation == 0.f) {
				SDL_RenderTexture(_renderer, obj.texture, &src_rect, &dst_rect);
			}
			else {
				SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);

				if (obj.filled) SDL_RenderFillRect(_renderer, &dst_rect);
				else SDL_RenderRect(_renderer, &dst_rect);
			}

			if (obj.is_text) SDL_DestroyTexture(obj.texture);
		}

		for (const line_struct& line : _lines) {

			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			SDL_RenderLine(_renderer, line.x1, line.y1, line.x2, line.y2);
		}

		SDL_RenderPresent(_renderer);
	}

	void clean_up() {
		SDL_DestroyRenderer(_renderer);
	}

	SDL_Renderer* get_renderer_pointer() {
		return _renderer;
	}

	/*void test_textures() {

		for (int i = 0; i < 10; ++i) {

			SDL_FRect rect = { 50.f + i * 100.f, 50.f, 50.f, 50.f };
			SDL_Texture* texture = resource_manager::get_texture_by_id(i);

			if (texture) {
				SDL_RenderTexture(_renderer, texture, NULL, &rect);
			}
		}
	
		SDL_RenderPresent(_renderer);
	}*/

	void blit_text(std::string text, int size, mth::vec2 location, SDL_Color color) {

		TTF_Font* font = resource_manager::get_font(size);
		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), text.size(), color, 800);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_DestroySurface(surface);

		if (!texture) std::cout << "failed to render font\n";

		else {
			render_data data = render_data();
	
			data.src_rect = { 0.f, 0.f, (float)texture->w, (float)texture->h };
			data.dst_rect = { location.x, location.y, (float)texture->w, (float)texture->h };
			data.is_text = true;
			data.texture = texture;
			data.layer = 100;

			submit_render_data(data);
		}
	}

	void draw_line(float x1, float y1, float x2, float y2) {

		line_struct line = line_struct();

		line.x1 = x1;
		line.y1 = y1;
		line.x2 = x2;
		line.y2 = y2;
		
		_lines.push_back(line);
	}

}