#include "player.h"
#include "../Core/input.h"
#include "../Renderer/renderer.h"
#include "../Renderer/render_data.h"
#include "../Core/asset_manager.h"
#include "scene.h"

#include <iostream>
#include <cmath>

Player::Player() {}

Player::~Player() {}

void Player::Update(float deltaTime) {

	UpdateMovement(deltaTime);
	UpdateFrame(deltaTime);
	UpdateMouse();
	UploadRenderData();
}

void Player::UpdateMovement(float deltaTime) {

	vec2 direction(0.f);

	if (Input::IsKeyDown(SDL_SCANCODE_W)) {
		direction.y -= 1.f;
	}
	if (Input::IsKeyDown(SDL_SCANCODE_S)) {
		direction.y += 1.f;
	}
	if (Input::IsKeyDown(SDL_SCANCODE_A)) {
		direction.x -= 1.f;
	}
	if (Input::IsKeyDown(SDL_SCANCODE_D)) {
		direction.x += 1.f;
	}

	vec2 displacement = direction.normalize() * _speed;

	_position.x += displacement.x * deltaTime;
	_position.y += displacement.y * deltaTime;

	if (displacement.length() == 0.f) _state = PlayerState::idle;
	else _state = PlayerState::walk;

	if (displacement.x > 0.f && !_busy) _direction = PlayerFacing::right;
	else if (displacement.x < 0.f && !_busy) _direction = PlayerFacing::left;
}

void Player::UpdateFrame(float deltaTime) {

	_accumulator += deltaTime;

	if (_accumulator >= _frameTime) {

		_accumulator = 0.f;
		_frameIndex = (_frameIndex + 1) % _frameCount;

		if (_state == PlayerState::attack && _frameIndex == 4) {

			_state = PlayerState::idle;
			_frameIndex = 0;
			_busy = false;
		}
	}

	if (_state == PlayerState::idle) {
		_texture = AssetManager::GetTextureByName("_Idle.png");
		//if (_texture == nullptr) std::cout << "nullptr\n";
	}
	else if (_state == PlayerState::walk) {
		_texture = AssetManager::GetTextureByName("_Run.png");
	}
	else if (_state == PlayerState::attack) {
		_texture = AssetManager::GetTextureByName("_Attack.png");
	}

	_hitbox = { _position.x - 32.f, _position.y - 20.f, 64.f, 128.f };
}

void Player::UpdateMouse() {

	int mouseX = Input::GetMouseX();
	int mouseY = Input::GetMouseY();

	float diffX = (float)mouseX - _position.x;
	float diffY = (float)mouseY - _position.y;

	_angle = atan2f(diffY, diffX) * (180.f / M_PI);

	if (Input::MouseLeftPressed()) {

		vec2 mouseDirection = vec2(diffX, diffY);
		Scene::AddProjectile(_position, mouseDirection, _angle);
	}
}

void Player::UploadRenderData() const {

	RenderData data = RenderData();

	data.srcRect = { 120.f * _frameIndex, 0.f, 120.f, 80.f };
	data.dstRect = { _position.x - 180.f, _position.y - 140.f, 120.f * 3.f, 80.f * 3.f };
	data.texture = _texture;

	if (_direction == PlayerFacing::left) data.flip = SDL_FLIP_HORIZONTAL;

	Renderer::SubmitRenderData(data);
}

float Player::GetX() const {
	return _position.x;
}

float Player::GetY() const {
	return _position.y;
}

float Player::GetAngle() const {
	return _angle;
}

const SDL_FRect& Player::GetHitbox() const {
	return _hitbox;
}
