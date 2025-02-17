#include "asset_manager.h"
#include "../Renderer/renderer.h"

#include <SDL3/SDL_ttf.h>

#include <unordered_map>
#include <iostream>
#include <filesystem>

namespace AssetManager {

	SDL_Renderer* _renderer = nullptr;

	std::unordered_map<int, TextureData> _textures;
	std::unordered_map<std::string, int> _textureIDs;
	std::unordered_map<int, TTF_Font*> _fonts;

	void Initialize() {

		_renderer = Renderer::GetRendererPointer();
		LoadAllTextures();
	}

	void LoadFont(std::string name, int size) {

		std::string path = "res/fonts/" + name;
		TTF_Font* font = TTF_OpenFont(path.c_str(), (float)size);

		if (!font) {
			std::cout << "failed to load font\n";
			return;
		}

		_fonts[size] = font;
	}

	void LoadAllTextures() {

		int id = 0;
		SDL_Surface* surface = nullptr;

		const std::filesystem::path base{ "res/textures/" };

		for (auto const& file : std::filesystem::directory_iterator{ base }) {

			std::string path = file.path().string();
			std::string name = file.path().filename().string();

			SDL_Texture* texture = LoadTexture(path, surface);
			
			_textures[id] = { id, name, texture };
			_textureIDs[name] = id++;
		}

		SDL_DestroySurface(surface);
	}

	SDL_Texture* LoadTexture(std::string path, SDL_Surface* surface) {
		
		surface = IMG_Load(path.c_str());

		if (!surface) {
			std::cout << "failed to load " << path << "\n";
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

		return texture;
	}

	SDL_Texture* GetTextureById(int id) {

		if (_textures.find(id) != _textures.end())
			return _textures[id].texture;

		return nullptr;
	}

	SDL_Texture* GetTextureByName(std::string name) {

		if (_textureIDs.find(name) != _textureIDs.end()) {
			
			int id = _textureIDs[name];
			return GetTextureById(id);
		}		

		return nullptr;
	}

	TTF_Font* GetFont(int size) {

		if (_fonts.find(size) == _fonts.end()) LoadFont("times_roman.ttf", size);
		return _fonts[size];
	}

	void CleanUp() {
		// Destroy textures and fonts?
	}

}