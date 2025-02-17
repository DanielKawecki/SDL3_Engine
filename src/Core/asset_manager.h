#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

#include <string>

struct TextureData {
	
	int id;
	std::string name;
	SDL_Texture* texture;

	//texture_data() = default;
};

namespace AssetManager {

	void Initialize();
	void LoadFont(std::string name, int size);
	void LoadAllTextures();
	SDL_Texture* LoadTexture(std::string path, SDL_Surface* surface);
	SDL_Texture* GetTextureById(int id);
	SDL_Texture* GetTextureByName(std::string name);
	TTF_Font* GetFont(int size);
	void CleanUp();
	//void render_glyphs(int size);
	//SDL_Texture* get_font_atlas();
	//SDL_Texture* get_glyph(char c);

}