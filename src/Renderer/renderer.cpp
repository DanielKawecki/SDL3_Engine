#include "renderer.h"
#include "../Core/backend.h"
//#include "game.h"
//#include "scene.h"
#include "../Core/asset_manager.h"

#include <SDL3/SDL_ttf.h>

#include <vector>
#include <iostream>
#include <algorithm>

namespace Renderer {

	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

	std::vector<RenderData> _renderQueue;
	//std::vector<RenderData> _debugQueue;
	std::vector<Line> _lines;

	void Initialize() {

		_window = BackEnd::GetWindowPointer();
		_renderer = SDL_CreateRenderer(_window, NULL);
	}

	void ClearRenderQueue() {
		_renderQueue.clear();
		//_debugQueue.clear();
		_lines.clear();
	}

	void SubmitRenderData(RenderData data) {
		_renderQueue.push_back(std::move(data));
	}

	void RenderFrame() {

		std::sort(_renderQueue.begin(), _renderQueue.end(), [](RenderData a, RenderData b) { return a.layer < b.layer; });

		SDL_SetRenderDrawColor(_renderer, 92, 86, 69, 255);
		SDL_RenderClear(_renderer);

		for (const RenderData& obj : _renderQueue) {

			SDL_FRect src_rect = obj.srcRect;
			SDL_FRect dst_rect = obj.dstRect;
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

			if (obj.isText) SDL_DestroyTexture(obj.texture);
		}

		for (const Line& line : _lines) {

			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			SDL_RenderLine(_renderer, line.x1, line.y1, line.x2, line.y2);
		}

		SDL_RenderPresent(_renderer);
	}

	void CleanUp() {
		SDL_DestroyRenderer(_renderer);
	}

	SDL_Renderer* GetRendererPointer() {
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

	void BlitText(std::string text, int size, vec2 location, SDL_Color color, bool backgroud) {

		TTF_Font* font = AssetManager::GetFont(size);
		SDL_Surface* surface = nullptr;

		if (backgroud) {
			SDL_Color backColor = { 255, 255, 255, 50 };
			surface = TTF_RenderText_Shaded_Wrapped(font, text.c_str(), text.size(), color, backColor, 800);
		}
		else {
			surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), text.size(), color, 800);
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_DestroySurface(surface);

		if (!texture) std::cout << "failed to render font\n";

		else {
			RenderData data = RenderData();
	
			data.srcRect = { 0.f, 0.f, (float)texture->w, (float)texture->h };
			data.dstRect = { location.x, location.y, (float)texture->w, (float)texture->h };
			data.isText = true;
			data.texture = texture;
			data.layer = 100;

			SubmitRenderData(data);
		}
	}

	void DrawLine(float x1, float y1, float x2, float y2) {

		Line line = Line();

		line.x1 = x1;
		line.y1 = y1;
		line.x2 = x2;
		line.y2 = y2;
		
		_lines.push_back(line);
	}

	void DrawLine(vec2 p1, vec2 p2) {

		Line line = Line();

		line.x1 = p1.x;
		line.y1 = p1.y;
		line.x2 = p2.x;
		line.y2 = p2.y;

		_lines.push_back(line);
	}

	void DrawRect(float x, float y, float w, float h, bool fill) {

		RenderData data;

		data.dstRect = { x, y, w, h };
		data.filled = fill;

		_renderQueue.push_back(data);
	}

	void DrawRect(SDL_FRect rect, bool fill) {

		RenderData data;

		data.dstRect = rect;
		data.filled = fill;
		data.layer = 9999;

		_renderQueue.push_back(data);
	}

	void DrawPoint(float x, float y) {

		RenderData data;

		data.dstRect = { x, y, 2.f, 2.f };
		data.filled = true;

		_renderQueue.push_back(data);
	}

	void DrawPoint(vec2 point) {

		RenderData data;

		data.dstRect = { point.x, point.y, 2.f, 2.f };
		data.filled = true;
		data.color = { 255, 0, 0, 255 };

		_renderQueue.push_back(data);
	}

}