#include "ui_backend.h"
#include "../Renderer/renderer.h"
#include "../Core/asset_manager.h"

void UIBackEnd::BlitText(std::string text, float posX, float posY) {

	SDL_Color color = { 255, 255, 255, 255 };
	Renderer::BlitText(text, 22, vec2(posX, posY), color, false);
}

void UIBackEnd::BlitTexture(std::string name, float posX, float posY, float sizeX, float sizeY) {

	RenderData data;
	data.texture = AssetManager::GetTextureByName(name);
	data.srcRect = { 0.f, 0.f, (float)data.texture->w, (float)data.texture->h };
	data.dstRect = { posX, posY, sizeX, sizeY };
	data.layer = 9999;
	Renderer::SubmitRenderData(data);
}
