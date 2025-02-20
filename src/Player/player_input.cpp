#include "player.h"
#include "../Core/input.h"

void Player::UpdateInput() {

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

	if (Input::IsKeyPressed(SDL_SCANCODE_R)) ReloadWeapon();

	if (Input::IsKeyPressed(SDL_SCANCODE_Q)) ChangeWeapon();
}

void Player::UpdateWeapon(float deltaTime) {
	_equipedWeapon->Update(deltaTime);
}

void Player::UpdateMouse() {

	int mouseX = Input::GetMouseX();
	int mouseY = Input::GetMouseY();

	float diffX = (float)mouseX - _transform.position.x;
	float diffY = (float)mouseY - _transform.position.y;

	_transform.rotation = atan2f(diffY, diffX) * (180.f / M_PI);

	if (_equipedWeapon) {

		vec2 mouseDirection = vec2(diffX, diffY);

		if (Input::MouseLeftDown() && GetCurrentWeaponInfo()->automatic) {
			_equipedWeapon->Shoot(_transform.position, mouseDirection, _transform.rotation);
		}
		else if (Input::MouseLeftPressed() && !GetCurrentWeaponInfo()->automatic) {
			_equipedWeapon->Shoot(_transform.position, mouseDirection, _transform.rotation);
		}
	}
}