#include "weapon.h"
#include "scene.h"

#include <iostream>

// ------------------ Weapon ------------------

Weapon::Weapon() {

	_type = WeaponType::NONE;

	_magCapacity = 0;
	_magBullets = 0;
	_automatic = false;

	_reloading = false;
	_accumulator = 0.f;
	_reloadTime = 0.f;
}

Weapon::~Weapon() {}

bool Weapon::IsAutomatic() const {
	return _automatic;
}

void Weapon::Reload() {

	_accumulator = 0.f;
	_reloading = true;
}

void Weapon::ResetAccumulator() {
	
	_accumulator = 0.f;
	_reloading = false;
}

WeaponType Weapon::GetType() const {
	return _type;
}

// ------------------ Pistol ------------------


Pistol::Pistol() {

	_type = WeaponType::PISTOL;
	_magCapacity = 7;
	_magBullets = _magCapacity;
	_automatic = false;

	_reloading = false;
	_accumulator = 0.f;
	_reloadTime = 2.f;
}

Pistol::~Pistol() {

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

// ------------------ Machine Gun ------------------

MachineGun::MachineGun() {

	_type = WeaponType::MACHINE_GUN;
	_magCapacity = 24;
	_magBullets = _magCapacity;
	_automatic = true;
	_ready = false;
	_fireRate = 7.f; // Shots per second
	_fireInterval = 1.f / _fireRate;

	_reloading = false;
	_accumulator = 0.f;
	_reloadTime = 2.4f;
}

MachineGun::~MachineGun() {}

void MachineGun::Update(float deltaTime) {

	if (!_reloading) {

		_accumulator += deltaTime;
		if (_accumulator >= _fireInterval) {

			_ready = true;
			_accumulator = 0.f;
		}
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

	if (_ready && _magBullets > 0 && !_reloading) {

		_magBullets -= 1;
		_ready = false;
		Scene::AddProjectile(location, direction, angle);
	}
}
