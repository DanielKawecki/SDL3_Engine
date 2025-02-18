#include "projectile.h"
#include "../Core/asset_manager.h"
#include <iostream>

Projectile::Projectile(vec2 position, vec2 direction, float angle) {

	_transform.position = position;
	_transform.rotation = angle;

	_motion.speed = 800.f;
	_motion.direction = direction;
	_motion.velocity = direction.normalize() * _motion.speed;

	_collision.active = true;
	_collision.hitbox = { position.x - 5.f, position.y - 5.f, 10.f, 10.f };

	_sprite.texture = AssetManager::GetTextureByName("bullet.png");
	_sprite.sizeX = 32.f;
	_sprite.sizeY = 16.f;
	_sprite.srcRect = { 0.f, 0.f, _sprite.sizeX, _sprite.sizeY };
	_sprite.dstRect = { position.x - 32.f, position.y - 16.f, 64.f, 32.f };
	_sprite.flip = SDL_FLIP_NONE;
	
	_animation.frameCount = 4;
	_animation.frameIndex = 0;
	_animation.accumulator = 0.f;
	_animation.frameTime = 0.032f;

	_exploded = false;
	_prevExploded = false;
	_remove = false;
	_lifeTime = 0.75f;
}

void Projectile::Update(float deltaTime) {

	UpdateAnimation(deltaTime);

	if (!_exploded) {

		_transform.position.x += _motion.velocity.x * deltaTime;
		_transform.position.y += _motion.velocity.y * deltaTime;

		_collision.hitbox.x = _transform.position.x - 5.f;
		_collision.hitbox.y = _transform.position.y - 5.f;

		_sprite.dstRect.x = _transform.position.x - _sprite.dstRect.w / 2.f;
		_sprite.dstRect.y = _transform.position.y - _sprite.dstRect.h / 2.f;
	}

	_lifeTime -= deltaTime;
	if (_lifeTime <= 0.f) _exploded = true;

	if (_exploded != _prevExploded) {
		_collision.active = false;
		_sprite.texture = AssetManager::GetTextureByName("smoke.png");
		_sprite.sizeX = 64.f;
		_sprite.sizeY = 64.f;
		_sprite.dstRect = { _transform.position.x - 32.f, _transform.position.y - 32.f, 64.f, 64.f };
		_sprite.srcRect = { 0.f, 0.f, _sprite.sizeX, _sprite.sizeY };
		_animation.frameIndex = 0;
		_animation.frameCount = 10;
		_animation.frameTime = 0.04f;
		_animation.accumulator = 0.f;
	}

	if (_exploded && _animation.frameIndex == _animation.frameCount - 1) _remove = true;

	_prevExploded = _exploded;
}

void Projectile::UpdateAnimation(float deltaTime) {

	_animation.accumulator += deltaTime;
	if (_animation.accumulator >= _animation.frameTime) {

		_animation.frameIndex = (_animation.frameIndex + 1) % _animation.frameCount;
		_sprite.srcRect.x = _sprite.sizeX * _animation.frameIndex;
		_animation.accumulator = 0.f;
	}
}

RenderData Projectile::CreateRenderData() const {

	RenderData data;

	data.texture = _sprite.texture;
	data.srcRect = _sprite.srcRect;
	data.dstRect = _sprite.dstRect;
	data.rotation = _transform.rotation;
	data.layer = _collision.hitbox.y;

	return data;
}

void Projectile::Explode() {

	_collision.active = false;
	_exploded = true;
}

bool Projectile::GetRemove() const {
	return _remove;
}

SDL_FRect Projectile::GetHitbox() const {
	return _collision.hitbox;
}
