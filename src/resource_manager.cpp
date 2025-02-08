#include "resource_manager.h"
#include "renderer.h"

#include <unordered_map>
#include <iostream>
#include <filesystem>

namespace resource_manager {

	SDL_Renderer* _renderer = nullptr;

	std::unordered_map<int, texture_data> _textures;
	std::unordered_map<std::string, int> _texture_ids;

	void init() {
		_renderer = renderer::get_renderer_pointer();
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
			get_texture_by_id(id);
		}		

		return nullptr;
	}

}