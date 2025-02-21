#include "player.h"
#include "../Core/input.h"
#include "../Renderer/renderer.h"
#include "../Renderer/render_data.h"
#include "../Core/asset_manager.h"
#include "../Game/scene.h"
#include "../Game/game.h"

#include <iostream>

Player::Player() {

	_transform.position = vec2(100.f);
	_transform.rotation = 0.f;

	_motion.velocity = vec2(0.f);
	_motion.direction = vec2(0.f);
	_motion.speed = 250.f;

	_sprite.sizeX = 120.f;
	_sprite.sizeY = 80.f;
	_sprite.srcRect = { 0.f, 0.f, _sprite.sizeX, _sprite.sizeY };
	_sprite.dstRect = { 100.f, 100.f, 360.f, 240.f };
	_sprite.flip = SDL_FLIP_NONE;
	_sprite.texture = nullptr;

	_animation.frameIndex = 0;
	_animation.frameCount = 10;
	_animation.frameTime = 0.08f;
	_animation.accumulator = 0.f;

	_collision.active = true;
	_collision.hitbox = { 0.f, 0.f, 64.f, 128.f };
	_wallHitbox = { 0.f, 0.f, 30.f, 10.f };

	_weapons.push_back(new Pistol());
	_weapons.push_back(new MachineGun());
	_weapons.push_back(new Shotgun());
	_weaponIndex = 0;
	_equipedWeapon = _weapons[_weaponIndex];

}

Player::~Player() {}

void Player::Update(float deltaTime) {

	if (!Game::IsEditorOpen()) {
		UpdateInput();
		UpdateMouse();
	}

	UpdateUI();
	UpdateMovement(deltaTime);
	UpdateFrame(deltaTime);
	UpdateWeapon(deltaTime);
	UploadRenderData();
}

void Player::UpdateMovement(float deltaTime) {

	_motion.velocity = _motion.direction.normalize() * _motion.speed;

	float newX = _wallHitbox.x + _motion.velocity.x * deltaTime;
	float newY = _wallHitbox.y + _motion.velocity.y * deltaTime;
	SDL_FRect xAxis = { newX, _wallHitbox.y, _wallHitbox.w, _wallHitbox.h };
	SDL_FRect yAxis = { _wallHitbox.x, newY, _wallHitbox.w, _wallHitbox.h };

	vec2 reply = Scene::MoveController(xAxis, yAxis);

	if (reply.x) {

		_transform.position.x += _motion.velocity.x * deltaTime;
		_collision.hitbox.x = _transform.position.x - 32.f;// -Game::GetViewport().x;
		_wallHitbox.x = _transform.position.x - 20.f;// -Game::GetViewport().x;
	}

	if (reply.y) {

		_transform.position.y += _motion.velocity.y * deltaTime;
		_collision.hitbox.y = _transform.position.y - 20.f;// -Game::GetViewport().y;
		_wallHitbox.y = _transform.position.y + 90.f;// - Game::GetViewport().y;
	}

	if (_motion.velocity.length() == 0.f) _state = PlayerState::IDLE;
	else _state = PlayerState::WALK;

	if (_motion.velocity.x > 0.f && !_busy) _direction = PlayerFacing::RIGHT;
	else if (_motion.velocity.x < 0.f && !_busy) _direction = PlayerFacing::LEFT;
}

void Player::UpdateFrame(float deltaTime) {

	_animation.accumulator += deltaTime;

	if (_animation.accumulator >= _animation.frameTime) {

		_animation.accumulator = 0.f;
		_animation.frameIndex = (_animation.frameIndex + 1) % _animation.frameCount;
		_sprite.srcRect.x = _sprite.sizeX * _animation.frameIndex;

		if (_state == PlayerState::ATTACK && _animation.frameIndex == 4) {

			_state = PlayerState::IDLE;
			_animation.frameIndex = 0;
			_busy = false;
		}
	}

	if (_state == PlayerState::IDLE) {
		_sprite.texture = AssetManager::GetTextureByName("_Idle.png");
		//if (_texture == nullptr) std::cout << "nullptr\n";
	}
	else if (_state == PlayerState::WALK) {
		_sprite.texture = AssetManager::GetTextureByName("_Run.png");
	}
	else if (_state == PlayerState::ATTACK) {
		_sprite.texture = AssetManager::GetTextureByName("_Attack.png");
	}

	_sprite.dstRect.x = _transform.position.x - 180.f;
	_sprite.dstRect.y = _transform.position.y - 140.f;
}

void Player::UploadRenderData() const {

	RenderData data = RenderData();

	data.srcRect = _sprite.srcRect;
	data.dstRect = _sprite.dstRect;
	data.texture = _sprite.texture;
	data.layer = _wallHitbox.y;

	if (_direction == PlayerFacing::LEFT) data.flip = SDL_FLIP_HORIZONTAL;

	Renderer::SubmitRenderData(data);
}

void Player::ReloadWeapon() {
	_equipedWeapon->Reload();
}

void Player::ChangeWeapon() {

	_equipedWeapon->ResetAccumulator();
	_weaponIndex = (_weaponIndex + 1) % (_weapons.size());
	_equipedWeapon = _weapons[_weaponIndex];
}

float Player::GetX() const {
	return _transform.position.x;
}

float Player::GetY() const {
	return _transform.position.y;
}

vec2 Player::GetPosition() const {
	return _transform.position;
}

float Player::GetAngle() const {
	return _transform.rotation;
}

SDL_FRect Player::GetHitbox() const {
	return _collision.hitbox;
}

SDL_FRect Player::GetWallHitbox() const {
	return _wallHitbox;
}

WeaponInfo* Player::GetCurrentWeaponInfo() const {
	return _equipedWeapon->GetWeaponInfo();
}
