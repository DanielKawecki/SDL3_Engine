#include "wall.h"
#include "../Core/asset_manager.h"

Wall::Wall(vec2 position) {
	
	_transform.position = position;
	_transform.rotation = 0.f;

	_collision.active = true;
	_collision.hitbox = { position.x, position.y, 32.f, 32.f };

	_sprite.flip = SDL_FLIP_NONE;
	_sprite.sizeX = 32.f;
	_sprite.sizeY = 96.f;
	_sprite.srcRect = { 0.f, 0.f, _sprite.sizeX, _sprite.sizeY };
	_sprite.dstRect = { position.x, position.y - 64.f, 32.f, 96.f };
	_sprite.texture = AssetManager::GetTextureByName("wall.png");
}

Wall::~Wall() {}

RenderData Wall::CreateRenderData() const {
	
	RenderData data;

	data.srcRect = _sprite.srcRect;
	data.dstRect = _sprite.dstRect;
	data.texture = _sprite.texture;
	data.layer = _collision.hitbox.y;

	return data;
}

SDL_FRect Wall::GetHitbox() const {
	return _collision.hitbox;
}

bool Wall::IsActive() const {
	return _collision.active;
}
