#include "wall.h"
#include "../Core/asset_manager.h"
#include "../Game/game.h"

void Wall::Setup() {

	if (_type == WallType::FRONT) {
		_sprite.srcRect.x = 0.f;
		_collision.hitbox.h = 12.f;
		_collision.hitbox.y += 52.f;
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
	else if (_type == WallType::MIDDLE_TOP) {
		_sprite.srcRect.x = 160.f;
		_sprite.dstRect.x -= 26.f;
		_collision.hitbox.w = 12.f;
		//_collision.hitbox.x += 26.f;
		_collision.hitbox.y += 52.f;
	}
	else if (_type == WallType::MIDDLE_FRONT)
		_sprite.srcRect.x = 192.f;
}

Wall::Wall(vec2 position, vec2 size, WallType type) {
	
	_type = type;
	_transform.position = position;
	_transform.rotation = 0.f;

	_collision.active = true;
	_collision.hitbox = { position.x, position.y, size.x, size.y };

	_sprite.flip = SDL_FLIP_NONE;
	_sprite.sizeX = 32.f;
	_sprite.sizeY = 32.f;
	_sprite.srcRect = { 0.f, 0.f, _sprite.sizeX, _sprite.sizeY };
	_sprite.dstRect = { position.x, position.y, size.x, size.y };
	_sprite.texture = AssetManager::GetTextureByName("debug_wall.png");

	Setup();
}

Wall::~Wall() {}

void Wall::Update() {

	_collision.hitbox.x = _transform.position.x - Game::GetViewport().x;
	_collision.hitbox.y = _transform.position.y - Game::GetViewport().y;
}

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
