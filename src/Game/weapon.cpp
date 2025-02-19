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

void Pistol::ResetAccumulator() {

	_reloading = false;
	_accumulator = 0.f;
}

// ------------------ Machine Gun ------------------

MachineGun::MachineGun() {

	_magCapacity = 24;
	_magBullets = _magCapacity;
	_automatic = true;
	_ready = false;
	_fireRate = 10.f; // Shots per second
	_fireInterval = 1.f / _fireRate;

	_reloading = false;
	_accumulator = 0.f;
	_reloadTime = 2.4f;
}

MachineGun::~MachineGun() {}

bool MachineGun::IsAutomatic() const {
	return _automatic;
}

void MachineGun::Update(float deltaTime) {

	_accumulator += deltaTime;
	if (_accumulator >= _fireInterval) {

		_ready = true;
		_accumulator;
	}

	if (_reloading) {

		_accumulator += deltaTime;
		if (_accumulator >= _reloadTime) {

			_reloading = false;
			_magBullets = _magCapacity;
			_accumulator = 0.f;
		}
	}
}

void MachineGun::Shoot(vec2 location, vec2 direction, float angle) {

	if (_ready && _magBullets > 0 &&!_reloading) {

		_magBullets -= 1;
		Scene::AddProjectile(location, direction, angle);
	}
}

void MachineGun::Reload() {

	_reloading = true;
	_accumulator = 0.f;
}

void MachineGun::ResetAccumulator() {

	_reloading = false;
	_accumulator = 0.f;
}
