#include "projectile.h"
#include "../Core/asset_manager.h"

Projectile::Projectile(vec2 position, vec2 direction, float angle) {

	_transform.position = position;
	_transform.rotation = angle;

	_motion.speed = 800.f;
	_motion.direction = direction;
	_motion.velocity = direction.normalize() * _motion.speed;

	_collision.active = true;
	_collision.hitbox = { position.x, position.y, 10.f, 10.f };

	_sprite.texture = AssetManager::GetTextureByName("bullet.png");
	_sprite.sizeX = 32.f;
	_sprite.sizeY = 16.f;
	_sprite.srcRect = { 0.f, 0.f, _sprite.sizeX, _sprite.sizeY };
	_sprite.dstRect = { position.x - 32.f, position.y - 8.f, 64.f, 32.f };
	_sprite.flip = SDL_FLIP_NONE;
	
	_exploded = false;
	_remove = false;
	_lifeTime = 0.75f;
	//_speed = 800.f;
	//_accumulator = 0.f;
	//_velocity = direction.normalize() * _speed;
	//_position = position;
	//
	//_active = true;
	//
	//_hitbox = { _position.x, _position.y, 10.f, 10.f };
	//_dstRect = { _position.x, _position.y, 10.f, 10.f };
}

void Projectile::Update(float deltaTime) {

	_transform.position.x += _motion.velocity.x * deltaTime;
	_transform.position.y += _motion.velocity.y * deltaTime;

	_sprite.dstRect.x = _transform.position.x;
	_sprite.dstRect.y = _transform.position.y;

	_lifeTime -= deltaTime;
	if (_lifeTime <= 0.f) {
		_remove = true;
	}

}

RenderData Projectile::CreateRenderData() const {

	RenderData data;

	data.texture = _sprite.texture;
	data.srcRect = _sprite.srcRect;
	data.dstRect = _sprite.dstRect;
	data.rotation = _transform.rotation;

	return data;
}

bool Projectile::GetRemove() const {
	return _remove;
}
