#include "weapon.h"
#include "scene.h"

#include <iostream>

Weapon::~Weapon() {}

// ------------------ Pistol ------------------


Pistol::Pistol() {

	_magCapacity = 7;
	_magBullets = _magCapacity;
	_automatic = false;

	_reloading = false;
	_accumulator = 0.f;
	_reloadTime = 2.f;
}

Pistol::~Pistol() {

}

bool Pistol::IsAutomatic() const {
	return _automatic;
}

void Pistol::Update(float deltaTime) {

	if (_reloading) {

		_accumulator += deltaTime;
		if (_accumulator >= _reloadTime) {

			_reloading = false;
			_magBullets = _magCapacity;
		}
	}
}

void Pistol::Shoot(vec2 location, vec2 direction, float angle) {

	if (_magBullets > 0 && !_reloading) {

		_magBullets -= 1;
		Scene::AddProjectile(location, direction, angle);
	}
}

void Pistol::Reload() {

	_reloading = true;
	_accumulator = 0.f;
}
