#include "wall.h"
#include "../Core/asset_manager.h"

void Wall::Setup() {

	if (_type == WallType::FRONT) {
		_sprite.srcRect.x = 0.f;
		_collision.hitbox = { _transform.position.x, _transform.position.y + 52.f, 64.f, 12.f };
	}
	else if (_type == WallType::CORNER_LEFT) {
		_sprite.srcRect.x = 32.f;

	}
	else if (_type == WallType::HALF_LEFT)
		_sprite.srcRect.x = 64.f;
	else if (_type == WallType::CORNER_RIGHT)
		_sprite.srcRect.x = 96.f;
	else if (_type == WallType::HALF_RIGHT)
		_sprite.srcRect.x = 128.f;
	else if (_type == WallType::MIDDLE_TOP)
		_sprite.srcRect.x = 160.f;
	else if (_type == WallType::MIDDLE_FRONT)
		_sprite.srcRect.x = 192.f;
}

Wall::Wall(vec2 position, WallType type) {
	
	_type = type;
	_transform.position = position;
	_transform.rotation = 0.f;

	_collision.active = true;
	_collision.hitbox = { position.x, position.y, 64.f, 64.f };

	_sprite.flip = SDL_FLIP_NONE;
	_sprite.sizeX = 32.f;
	_sprite.sizeY = 32.f;
	_sprite.srcRect = { 0.f, 0.f, _sprite.sizeX, _sprite.sizeY };
	_sprite.dstRect = { position.x, position.y, 64.f, 64.f };
	_sprite.texture = AssetManager::GetTextureByName("debug_wall.png");

	Setup();
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
