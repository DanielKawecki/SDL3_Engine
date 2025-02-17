#include "resource_manager.h"
#include "../Renderer/renderer.h"

#include <SDL3/SDL_ttf.h>

#include <unordered_map>
#include <iostream>
#include <filesystem>

namespace resource_manager {

	SDL_Renderer* _renderer = nullptr;

	std::unordered_map<int, texture_data> _textures;
	std::unordered_map<std::string, int> _texture_ids;

	std::unordered_map<int, TTF_Font*> _fonts;
	//std::unordered_map<char, SDL_Texture*> _glyphs;
	SDL_Texture* _font_atlas = nullptr;

	void init() {

		_renderer = renderer::get_renderer_pointer();
		render_glyphs(22);
	}

	void load_font(std::string name, int size) {

		std::string path = "res/fonts/" + name;
		TTF_Font* font = TTF_OpenFont(path.c_str(), (float)size);

		if (!font) {
			std::cout << "failed to load font\n";
			return;
		}

		_fonts[size] = font;
	}

	void render_glyphs(int size) {

		TTF_Font* font = get_font(size);
		SDL_Surface* surface = nullptr;
		SDL_Color color = { 255, 255, 255, 255 };
		
		std::string symbols = "!@#$%^&*()_+-=[]{}|;:'\",.<>/? ";

		for (char c = 'a'; c <= 'z'; ++c) {
			symbols += c;
		}

		for (char c = 'A'; c <= 'Z'; ++c) {
			symbols += c;
		}

		for (char c = '0'; c <= '9'; ++c) {
			symbols += c;
		}

		surface = TTF_RenderText_Blended(font, symbols.c_str(), symbols.size(), color);
		_font_atlas = SDL_CreateTextureFromSurface(_renderer, surface);

		SDL_DestroySurface(surface);
	}

	void load_all_textures() {

		int id = 0;
		SDL_Surface* surface = nullptr;

		const std::filesystem::path base{ "res/textures/" };

		for (auto const& file : std::filesystem::directory_iterator{ base }) {

			std::string path = file.path().string();
			std::string name = file.path().filename().string();

			SDL_Texture* texture = load_texture(path, surface);
			
			_textures[id] = { id, name, texture };
			_texture_ids[name] = id++;
		}

		SDL_DestroySurface(surface);
	}

	SDL_Texture* load_texture(std::string path, SDL_Surface* surface) {
		
		surface = IMG_Load(path.c_str());

		if (!surface) {
			std::cout << "failed to load " << path << "\n";
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

		return texture;
	}

	SDL_Texture* get_texture_by_id(int id) {

		if (_textures.find(id) != _textures.end())
			return _textures[id].texture;

		return nullptr;
	}

	SDL_Texture* get_texture_by_name(std::string name) {

		if (_texture_ids.find(name) != _texture_ids.end()) {
			
			int id = _texture_ids[name];
			return get_texture_by_id(id);
		}		

		return nullptr;
	}

	SDL_Texture* get_font_atlas() {
		return _font_atlas;
	}

	//SDL_Texture* get_glyph(char c) {

	//	if (_glyphs.find(c) == _glyphs.end()) return nullptr;//load_font("times_roman.ttf", size);
	//	return _glyphs[c];
	//}

	TTF_Font* get_font(int size) {

		if (_fonts.find(size) == _fonts.end()) load_font("times_roman.ttf", size);
		return _fonts[size];
	}

}