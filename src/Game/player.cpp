#include "player.h"
#include "../Core/input.h"
#include "../Renderer/renderer.h"
#include "../Renderer/render_data.h"
#include "../Core/asset_manager.h"
#include "scene.h"

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
	_weaponIndex = 0;
	_equipedWeapon = _weapons[_weaponIndex];

}

Player::~Player() {}

void Player::Update(float deltaTime) {

	UpdateMovement(deltaTime);
	UpdateFrame(deltaTime);
	UpdateWeapons(deltaTime);
	UpdateMouse();
	UploadRenderData();
}

void Player::UpdateMovement(float deltaTime) {

	_motion.direction = vec2(0.f);

	if (Input::IsKeyDown(SDL_SCANCODE_W)) {
		_motion.direction.y -= 1.f;
	}
	if (Input::IsKeyDown(SDL_SCANCODE_S)) {
		_motion.direction.y += 1.f;
	}
	if (Input::IsKeyDown(SDL_SCANCODE_A)) {
		_motion.direction.x -= 1.f;
	}
	if (Input::IsKeyDown(SDL_SCANCODE_D)) {
		_motion.direction.x += 1.f;
	}

	_motion.velocity = _motion.direction.normalize() * _motion.speed;

	float newX = _wallHitbox.x + _motion.velocity.x * deltaTime;
	float newY = _wallHitbox.y + _motion.velocity.y * deltaTime;
	SDL_FRect xAxis = { newX, _wallHitbox.y, _wallHitbox.w, _wallHitbox.h };
	SDL_FRect yAxis = { _wallHitbox.x, newY, _wallHitbox.w, _wallHitbox.h };

	vec2 reply = Scene::MoveController(xAxis, yAxis);

	if (reply.x) {

		_transform.position.x += _motion.velocity.x * deltaTime;
		_collision.hitbox.x = _transform.position.x - 32.f;
		_wallHitbox.x = _transform.position.x - 20.f;
	}

	if (reply.y) {

		_transform.position.y += _motion.velocity.y * deltaTime;
		_collision.hitbox.y = _transform.position.y - 20.f;
		_wallHitbox.y = _transform.position.y + 90.f;
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

void Player::UpdateWeapons(float deltaTime) {

	if (Input::IsKeyPressed(SDL_SCANCODE_R)) _equipedWeapon->Reload();

	if (Input::IsKeyPressed(SDL_SCANCODE_Q)) {

		_equipedWeapon->ResetAccumulator();
		_weaponIndex = (_weaponIndex + 1) % (_weapons.size());
		_equipedWeapon = _weapons[_weaponIndex];
		//std::cout << _weaponIndex  << " " << _weapons.size() << "\n";
	}

	_equipedWeapon->Update(deltaTime);
	// Do I need to update weapons that I am not using at the time?
	//for (int i = 0; i < _weapons.size(); ++i) {
	//	_weapons[i]->Update(deltaTime);
	//}
}

void Player::UpdateMouse() {

	int mouseX = Input::GetMouseX();
	int mouseY = Input::GetMouseY();

	float diffX = (float)mouseX - _transform.position.x;
	float diffY = (float)mouseY - _transform.position.y;

	_transform.rotation = atan2f(diffY, diffX) * (180.f / M_PI);

	if (_equipedWeapon) {

		vec2 mouseDirection = vec2(diffX, diffY);

		if (Input::MouseLeftDown() && _equipedWeapon->IsAutomatic()) {
			_equipedWeapon->Shoot(_transform.position, mouseDirection, _transform.rotation);	
		}
		else if (Input::MouseLeftPressed() && !_equipedWeapon->IsAutomatic()) {
			_equipedWeapon->Shoot(_transform.position, mouseDirection, _transform.rotation);
		}
	}
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

WeaponType Player::GetWeaponType() const {
	return _equipedWeapon->GetType();
}
