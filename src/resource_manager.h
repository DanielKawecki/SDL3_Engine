#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

#include <string>

struct texture_data {
	int id;
	std::string name;
	SDL_Texture* texture;
};

namespace resource_manager {

	void init();
	void load_font(std::string name, int size);
	void load_all_textures();
	SDL_Texture* load_texture(std::string path, SDL_Surface* surface);
	SDL_Texture* get_texture_by_id(int id);
	SDL_Texture* get_texture_by_name(std::string name);
	TTF_Font* get_font(int size);

}